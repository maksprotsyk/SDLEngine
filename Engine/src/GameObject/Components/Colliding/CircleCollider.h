//
// Created by Максим Процик on 20.08.2023.
//

#ifndef GAMETEST_CIRCLECOLLIDER_H
#define GAMETEST_CIRCLECOLLIDER_H

#include "Collider.h"

class CircleCollider: public Collider
{
public:
    float Radius = 0;
    [[nodiscard]] std::pair<Vector2D, Vector2D> GetBorders() const override;
    [[nodiscard]] Vector2D GetClosestPoint(const Vector2D& point) const override;
    [[nodiscard]] std::vector<Vector2D> GetCollisionAxes(const Collider* collider) const override;
    [[nodiscard]] std::pair<std::pair<Vector2D, float>, std::pair<Vector2D, float>> GetMinAndMaxPoints(const Vector2D& axis) const override;
    [[nodiscard]]  std::pair<Vector2D, Vector2D> GetSignificantFace(const Vector2D& point, const Vector2D& axis) const override;

    SERIALIZABLE(PROPERTY(CircleCollider, Radius));
};


#endif //GAMETEST_CIRCLECOLLIDER_H
