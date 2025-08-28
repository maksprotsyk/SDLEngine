//
// Created by Максим Процик on 29.07.2023.
//

#ifndef GAMEENGINE_VECTOR2D_H
#define GAMEENGINE_VECTOR2D_H

#include <ostream>

#include "Serialization/Parsing.h"


class Vector2D
{
public:
    float X;
    float Y;
    Vector2D(float x, float y);
    Vector2D();
    Vector2D& operator=(const Vector2D& other) = default;
    Vector2D operator+(const Vector2D& other) const;
    Vector2D& operator+=(const Vector2D& other);
    Vector2D operator-(const Vector2D& other) const;
    Vector2D& operator-=(const Vector2D& other);
    float operator*(const Vector2D& other) const;
    Vector2D& operator*=(float k);
    float CrossProduct(const Vector2D& other) const;
    float Length() const;
    Vector2D Normalized() const;

    SERIALIZABLE(PROPERTY(Vector2D, X),
                 PROPERTY(Vector2D, Y))
};

Vector2D operator*(float k, const Vector2D& vec);

std::ostream& operator<<(std::ostream& os, const Vector2D& vec);


#endif //GAMEENGINE_VECTOR2D_H
