//
// Created by Максим Процик on 20.08.2023.
//

#include "GameObject/Components/Colliding/CircleCollider.h"
#include "GameObject/Components/Colliding/RectangleCollider.h"
#include "CollisionHandler.h"
#include "Utils/Math.h"

CollisionHandler *CollisionHandler::m_collidingHandler = nullptr;

CollisionHandler *CollisionHandler::GetInstance()
{
    if (!m_collidingHandler)
    {
        m_collidingHandler = new CollisionHandler;
    }
    return m_collidingHandler;
}

void CollisionHandler::OnUpdate(const std::vector<GameObject*>& objects)
{
    std::vector<border_info_t> borders;

    for (GameObject* obj: objects)
    {
        Collider* collider = obj->FindComponent<Collider>();
        if (!collider)
        {
            continue;
        }
        borders.emplace_back(collider, collider->GetBorders());
    }
    std::function<float(const Vector2D&)> measureHorizontal = [](const Vector2D& vec)
    {
        return vec.X;
    };
    std::unordered_map<Collider*, std::set<Collider*>> possibleCollisionsHorizontal = GetPossibleCollisions(
            borders,
            measureHorizontal
            );

    std::function<float(const Vector2D&)> measureVertical = [](const Vector2D& vec)
    {
        return vec.Y;
    };
    std::unordered_map<Collider*, std::set<Collider*>> possibleCollisionsVertical = GetPossibleCollisions(
            borders,
            measureVertical
    );
    std::unordered_map<Collider*, std::set<Collider*>> possibleCollisions;
    for (const auto& border: borders)
    {
        std::set<Collider*> colliders;
        for (const auto& item: possibleCollisionsHorizontal[border.first])
        {
            if (possibleCollisionsVertical[border.first].contains(item))
            {
                colliders.insert(item);
            }
        }
        possibleCollisions[border.first] = colliders;
    }


    std::unordered_map<Collider*, std::set<Collider*>> handledCollisions;
    std::unordered_map<Collider*, std::unordered_map<Collider*, Collider::Collision>> newCollision;
    for (const auto& p: possibleCollisions)
    {
        for (Collider* collider: p.second)
        {
            if (handledCollisions[collider].contains(p.first))
            {
                continue;
            }
            auto res = HandleCollision(p.first, collider);
            if (res.first)
            {
                Collider::Collision collisionFirst = res.second;
                Collider::Collision collisionSecond = res.second;
                collisionSecond.normal = -1.0f * collisionSecond.normal;
                newCollision[p.first][collider] = collisionFirst;
                newCollision[collider][p.first] = collisionSecond;
                if (!m_collisions[collider].contains(p.first))
                {
                    collider->OnCollisionEnter.Invoke(p.first, collisionFirst);
                    p.first->OnCollisionEnter.Invoke(collider, collisionSecond);
                }
            }
            handledCollisions[collider].insert(p.first);
            handledCollisions[p.first].insert(collider);
        }
    }

    for (const auto& p: m_collisions)
    {
        for (auto& [collider, point]: p.second)
        {
            if (!newCollision[p.first].contains(collider))
            {
                p.first->OnCollisionEnd.Invoke(collider);
            }
        }
    }

    m_collisions = std::move(newCollision);
}

void CollisionHandler::DestroyObjects(const std::vector<GameObject*>& objects)
{
    std::vector<Collider*> colliders;
    for (GameObject* obj: objects)
    {
        Collider* collider = obj->FindComponent<Collider>();
        if (!collider)
        {
            continue;
        }
        colliders.push_back(collider);
    }

    for (auto* col: colliders)
    {
        auto& collision = m_collisions[col];
        for (const auto& p: collision)
        {
            m_collisions[p.first].erase(col);
        }
        m_collisions.erase(col);
    }
}

void CollisionHandler::OnFinish()
{
    m_collisions.clear();
}

std::unordered_map<Collider*, std::set<Collider*>> CollisionHandler::GetPossibleCollisions(
        std::vector<border_info_t>& borders,
        std::function<float(const Vector2D&)> measure) const
{
    std::unordered_map<Collider*, std::set<Collider*>> possibleCollisions;
    std::sort(borders.begin(), borders.end(), [&measure](const border_info_t& border1, const border_info_t& border2){
        return measure(border1.second.first) < measure(border2.second.first);
    });

    std::vector<size_t> activeIndex;
    for (size_t i = 0; i < borders.size(); i++)
    {
        std::vector<size_t> toErase;
        for (size_t j = 0; j < activeIndex.size(); j++)
        {
            if (measure(borders[activeIndex[j]].second.second) < measure(borders[i].second.first))
            {
                toErase.push_back(j);
            }
        }

        for (int ind = ((int)toErase.size()) - 1; ind >= 0; ind--)
        {
            activeIndex.erase(activeIndex.begin() + (int)toErase[ind]);
        }

        for (size_t ind: activeIndex)
        {
            possibleCollisions[borders[ind].first].insert(borders[i].first);
            possibleCollisions[borders[i].first].insert(borders[ind].first);
        }
        activeIndex.push_back(i);
    }

    return possibleCollisions;
}

std::pair<bool, Collider::Collision> CollisionHandler::HandleCollision(const Collider* collider1,  const Collider* collider2) const
{
    std::vector<Vector2D> axes = collider1->GetCollisionAxes(collider2);
    std::vector<Vector2D> axes2 = collider2->GetCollisionAxes(collider1);
    axes.reserve(axes.size() + axes2.size());
    std::copy(axes2.begin(), axes2.end(), std::back_inserter(axes));

    Collider::Collision collision;
    collision.penetration = std::numeric_limits<float>::infinity();
    Vector2D closestPoint1;
    Vector2D closestPoint2;
    for (const auto& axis: axes)
    {
        auto [min1, max1] = collider1->GetMinAndMaxPoints(axis);
        auto [min2, max2] = collider2->GetMinAndMaxPoints(axis);
        if (max1.second >= min2.second && min2.second >= min1.second)
        {
            float penetration = max1.second - min2.second;
            if (penetration < collision.penetration)
            {
                collision.penetration = penetration;
                collision.normal = axis;
                closestPoint1 = max1.first;
                closestPoint2 = min2.first;
            }
            continue;
        }
        if (max2.second >= min1.second && min1.second >= min2.second)
        {
            float penetration = max2.second - min1.second;
            if (penetration < collision.penetration)
            {
                collision.penetration = penetration;
                collision.normal = -1.0f * axis;
                closestPoint1 = min1.first;
                closestPoint2 = max2.first;
            }
            continue;
        }

        return {false, collision};
    }

    auto [first1, second1] = collider1->GetSignificantFace(closestPoint1, collision.normal);
    auto [first2, second2] = collider2->GetSignificantFace(closestPoint2, collision.normal);
    if (Math::Equal(first1.X, second1.X) && Math::Equal(first1.Y, second1.Y))
    {
        collision.point = first1;
        return {true, collision};
    }
    if (Math::Equal(first2.X, second2.X) && Math::Equal(first2.Y, second2.Y))
    {
        collision.point = first2;
        return {true, collision};
    }
    Vector2D direction1 = second1 - first1;
    Vector2D direction2 = second2 - first2;
    float coefficient = (first2 - first1) * direction2 / (direction1 * direction2);
    Vector2D point = first1 + coefficient * direction1;
    collision.point = point;
    return {true, collision};
}

std::unordered_map<Collider*, Collider::Collision> CollisionHandler::GetActiveCollisions(Collider* collider) const
{
    auto itr = m_collisions.find(collider);
    if (itr == m_collisions.end())
    {
        return {};
    }
    return itr->second;
}
