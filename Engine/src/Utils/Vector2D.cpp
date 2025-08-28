//
// Created by Максим Процик on 29.07.2023.
//

#include "Vector2D.h"

Vector2D::Vector2D(float x, float y): X(x), Y(y)
{

}

Vector2D::Vector2D(): Vector2D(0.0, 0.0)
{

}

Vector2D Vector2D::operator+(const Vector2D &other) const
{
    return {X + other.X, Y + other.Y};
}

Vector2D Vector2D::operator-(const Vector2D &other) const
{
    return {X - other.X, Y - other.Y};
}

float Vector2D::operator*(const Vector2D &other) const
{
    return X * other.X + Y*other.Y;
}

Vector2D& Vector2D::operator+=(const Vector2D &other)
{
    X += other.X;
    Y += other.Y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D &other)
{
    X -= other.X;
    Y -= other.Y;
    return *this;
}

Vector2D& Vector2D::operator*=(float k)
{
    X *= k;
    Y *= k;
    return *this;
}

Vector2D operator*(float k, const Vector2D& vec)
{
    return {k * vec.X, k * vec.Y};
}

std::ostream& operator<<(std::ostream& os, const Vector2D& vec)
{
    os << "Vector2D(" << vec.X << ", " << vec.Y << ")";
    return os;
}

float Vector2D::CrossProduct(const Vector2D& other) const
{
    return X * other.Y - Y * other.X;
}

float Vector2D::Length() const
{
    return std::sqrt(X * X + Y * Y);
}
Vector2D Vector2D::Normalized() const
{
    return 1/Length() * *this;
}