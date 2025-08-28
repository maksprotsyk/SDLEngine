//
// Created by Максим Процик on 24.08.2023.
//

#ifndef GAMETEST_RECTANGLECOLLIDER_H
#define GAMETEST_RECTANGLECOLLIDER_H

#include "Collider.h"

class RectangleCollider: public Collider
{
public:
    float Width = 0.1;
    float Height = 0.1;
    [[nodiscard]] std::pair<Vector2D, Vector2D> GetBorders() const override;
    [[nodiscard]] Vector2D GetClosestPoint(const Vector2D& point) const override;
    [[nodiscard]] std::vector<Vector2D> GetCollisionAxes(const Collider* collider) const override;
    [[nodiscard]] std::pair<std::pair<Vector2D, float>, std::pair<Vector2D, float>> GetMinAndMaxPoints(const Vector2D& axis) const override;
    [[nodiscard]]  std::pair<Vector2D, Vector2D> GetSignificantFace(const Vector2D& point, const Vector2D& axis) const override;

    SERIALIZABLE(PROPERTY(RectangleCollider, Width),
                 PROPERTY(RectangleCollider, Height));
};


#endif //GAMETEST_RECTANGLECOLLIDER_H
