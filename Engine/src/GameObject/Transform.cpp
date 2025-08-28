//
// Created by Максим Процик on 01.08.2023.
//

#include "Transform.h"

Transform::Transform(): Scale(1.0f, 1.0f)
{

}

void Transform::Rotate(float angle, const Vector2D& center)
{
    Vector2D diff = Position - center;
    float radians = M_PI * angle / 180.0f;
    float cos = std::cos(radians);
    float sin = std::sin(radians);
    Position = Vector2D(center.X + cos * diff.X - sin * diff.Y, center.Y + cos * diff.Y + sin * diff.X);
    RotationAngle += angle;

}