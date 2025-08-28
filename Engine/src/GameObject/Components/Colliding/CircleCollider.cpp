//
// Created by Максим Процик on 20.08.2023.
//

#include "GameObject/GameObject.h"
#include "Serialization/ComponentFactory.h"
#include "CircleCollider.h"

REGISTER(CircleCollider)

std::pair<Vector2D, Vector2D> CircleCollider::GetBorders() const
{
    Vector2D minPos = m_GameObject->transform.Position;
    minPos.X -= Radius;
    minPos.Y -= Radius;
    Vector2D maxPos = m_GameObject->transform.Position;
    maxPos.X += Radius;
    maxPos.Y += Radius;

    return {minPos, maxPos};
}

Vector2D CircleCollider::GetClosestPoint(const Vector2D &point) const
{
    Vector2D direction = (point - m_GameObject->transform.Position).Normalized();
    return m_GameObject->transform.Position + Radius * direction;
}

std::vector<Vector2D> CircleCollider::GetCollisionAxes(const Collider *collider) const
{
    Vector2D closestPoint = collider->GetClosestPoint(m_GameObject->transform.Position);
    return {(closestPoint - m_GameObject->transform.Position).Normalized()};
}

std::pair<std::pair<Vector2D, float>, std::pair<Vector2D, float>> CircleCollider::GetMinAndMaxPoints(const Vector2D& axis) const
{
    Vector2D radiusVector = Radius * axis;
    Vector2D center = m_GameObject->transform.Position;
    Vector2D minPoint = center - radiusVector;
    Vector2D maxPoint = center + radiusVector;
    return {{minPoint, minPoint * axis}, {maxPoint, maxPoint * axis}};
}

std::pair<Vector2D, Vector2D> CircleCollider::GetSignificantFace(const Vector2D &point, const Vector2D &axis) const
{
    return {point, point};
}

