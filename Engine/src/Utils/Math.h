//
// Created by Максим Процик on 08.09.2023.
//

#ifndef GAMETEST_MATH_H
#define GAMETEST_MATH_H

#include "Vector2D.h"

namespace Math
{
    Vector2D RotatePoint(const Vector2D& point, float angle, const Vector2D& center);
    inline float AngleToRadian(float radians);
    std::vector<Vector2D> RotatePoints(const std::vector<Vector2D>& points, float angle, const Vector2D& center);
    bool Equal(float first, float second);
}


#endif //GAMETEST_MATH_H
