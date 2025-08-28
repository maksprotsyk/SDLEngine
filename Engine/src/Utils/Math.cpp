//
// Created by Максим Процик on 08.09.2023.
//

#include "Math.h"

Vector2D Math::RotatePoint(const Vector2D& point, float angle, const Vector2D& center)
{
    Vector2D diff = point - center;
    float radians = AngleToRadian(angle);
    float cos = std::cosf(radians);
    float sin = std::sinf(radians);
    Vector2D rotated = Vector2D(cos * diff.X - sin * diff.Y, sin * diff.X + cos * diff.Y);
    return center + rotated;
}

float Math::AngleToRadian(float radians)
{
    return radians / 180.0f * (float)M_PI;
}

std::vector<Vector2D> Math::RotatePoints(const std::vector<Vector2D>& points, float angle, const Vector2D& center)
{
    float radians = AngleToRadian(angle);
    float cos = std::cosf(radians);
    float sin = std::sinf(radians);
    std::vector<Vector2D> rotatedPoints;
    rotatedPoints.reserve(points.size());
    for (const auto& point: points)
    {
        Vector2D diff = point - center;
        Vector2D rotated = Vector2D(cos * diff.X - sin * diff.Y, sin * diff.X + cos * diff.Y);
        rotatedPoints.push_back(center + rotated);
    }
    return rotatedPoints;
}

bool Math::Equal(float first, float second)
{
    const float epsilon = 0.000001;
    return std::abs(first - second) < epsilon;
}