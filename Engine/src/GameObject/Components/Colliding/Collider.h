//
// Created by Максим Процик on 20.08.2023.
//

#ifndef GAMETEST_COLLIDER_H
#define GAMETEST_COLLIDER_H

#include "Utils/Event.h"
#include "Utils/Vector2D.h"
#include "GameObject/Components/Component.h"


class Collider: public Component
{
public:
    enum ColliderType
    {
        Circle,
        Rectangle
    };
    struct Collision
    {
        Vector2D point;
        Vector2D normal;
        float penetration;
    };
    Event<std::function<void(Collider*, const Collision&)>> OnCollisionEnter;
    Event<std::function<void(Collider*)>> OnCollisionEnd;
    virtual std::pair<Vector2D, Vector2D> GetBorders() const = 0;
    virtual Vector2D GetClosestPoint(const Vector2D& point) const = 0;
    virtual std::vector<Vector2D> GetCollisionAxes(const Collider* collider) const = 0;
    virtual std::pair<std::pair<Vector2D, float>, std::pair<Vector2D, float>> GetMinAndMaxPoints(const Vector2D& axis) const = 0;
    virtual std::pair<Vector2D, Vector2D> GetSignificantFace(const Vector2D& point, const Vector2D& axis) const = 0;

};


#endif //GAMETEST_COLLIDER_H
