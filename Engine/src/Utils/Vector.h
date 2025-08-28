//
// Created by Максим Процик on 24.08.2023.
//

#ifndef GAMETEST_VECTOR_H
#define GAMETEST_VECTOR_H

#include <ostream>
#include <type_traits>
#include <array>

#include "Serialization/Parsing.h"


template<class T, size_t N>
class Vector
{
public:
    Vector();
    Vector(std::initializer_list<T> coordinates);
    Vector<T, N>& operator=(const Vector<T, N>& other) = default;
    Vector<T, N> operator+(const Vector<T, N>& other) const;
    Vector<T, N>& operator+=(const Vector<T, N>& other);
    Vector<T, N> operator-(const Vector<T, N>& other) const;
    Vector<T, N>& operator-=(const Vector<T, N>& other);
    T CrossProduct(const Vector<T, N>& other) const;
    Vector<T, N>& operator*=(T k);
    Vector<T, N> operator*(T k) const;
    Vector<T, N>& operator/=(T k);
    Vector<T, N> operator/(T k) const;
    Vector<T, N> operator/(const Vector<T, N>& other) const;
    Vector<T, N>& operator/=(const Vector<T, N>& other);
    Vector<T, N> operator*(const Vector<T, N>& other) const;
    Vector<T, N>& operator*=(const Vector<T, N>& other);
    T& operator[](size_t i);
    const T& operator[](size_t i) const;
    T Length() const;
    Vector<T, N> Normalized() const;
private:
    std::array<T, N> m_coordinates;

};

template<class T, size_t N>
Vector<T, N> operator*(T k, const Vector<T, N>& vec);

template<class T, size_t N>
std::ostream& operator<<(std::ostream& os, const Vector<T, N>& vec);


template<class T, size_t N>
Vector<T, N>::Vector(): Vector({})
{
}

template<class T, size_t N>
Vector<T, N> Vector<T, N>::operator+(const Vector<T, N> &other) const
{
    Vector<T, N> sumVector;
    for (size_t i = 0; i < N; i++)
    {
        sumVector[i] = m_coordinates[i] + other.m_coordinates[i];
    }
    return sumVector;
}

template<class T, size_t N>
Vector<T, N> Vector<T, N>::operator-(const Vector<T, N> &other) const
{
    Vector<T, N> diffVector;
    for (size_t i = 0; i < N; i++)
    {
        diffVector[i] = m_coordinates[i] - other.m_coordinates[i];
    }
    return diffVector;
}

template<class T, size_t N>
Vector<T, N> &Vector<T, N>::operator+=(const Vector<T, N> &other)
{
    for (size_t i = 0; i < N; i++)
    {
        m_coordinates[i] += other[i];
    }
    return *this;
}

template<class T, size_t N>
Vector<T, N> &Vector<T, N>::operator-=(const Vector<T, N> &other)
{
    for (size_t i = 0; i < N; i++)
    {
        m_coordinates[i] -= other[i];
    }
    return *this;
}

template<class T, size_t N>
T Vector<T, N>::CrossProduct(const Vector<T, N> &other) const
{
    float dotProduct = 0;
    for (size_t i = 0; i < N; i++)
    {
        dotProduct += m_coordinates[i] * other.m_coordinates[i];
    }
    return dotProduct;
}

template<class T, size_t N>
Vector<T, N> &Vector<T, N>::operator*=(T k)
{
    for (size_t i = 0; i < N; i++)
    {
        m_coordinates[i] *= k;
    }
    return *this;
}

template<class T, size_t N>
T &Vector<T, N>::operator[](size_t i)
{
    return m_coordinates[i];
}

template<class T, size_t N>
const T &Vector<T, N>::operator[](size_t i) const
{
    return m_coordinates[i];
}

template<class T, size_t N>
T Vector<T, N>::Length() const
{
    float lengthSqr = 0;
    for (size_t i = 0; i < N; i++)
    {
        lengthSqr += m_coordinates[i] * m_coordinates[i];
    }
    return std::sqrt(lengthSqr);
}

template<class T, size_t N>
Vector<T, N> Vector<T, N>::Normalized() const
{
    return this->operator/(Length());
}

template<class T, size_t N>
Vector<T, N> Vector<T, N>::operator*(T k) const
{
    Vector<T, N> prodVector;
    for (size_t i = 0; i < N; i++)
    {
        prodVector.m_coordinates[i] = m_coordinates[i] * k;
    }
    return prodVector;
}

template<class T, size_t N>
Vector<T, N> &Vector<T, N>::operator/=(T k)
{
    for (size_t i = 0; i < N; i++)
    {
        m_coordinates[i] /= k;
    }
    return *this;

}

template<class T, size_t N>
Vector<T, N> Vector<T, N>::operator/(T k) const
{
    Vector<T, N> divVector;
    for (size_t i = 0; i < N; i++)
    {
        divVector.m_coordinates[i] = m_coordinates[i] / k;
    }
    return divVector;
}

template<class T, size_t N>
Vector<T, N>::Vector(std::initializer_list<T> coordinates)
{
    size_t index = 0;
    for (auto itr = coordinates.begin(); itr != coordinates.end(); itr++)
    {
        m_coordinates[index] = *itr;
        index++;
    }
    for (; index < N; index++)
    {
        m_coordinates[index] = 0;
    }

}

template<class T, size_t N>
Vector<T, N> Vector<T, N>::operator/(const Vector<T, N> &other) const
{
    Vector<T, N> divVector;
    for (size_t i = 0; i < N; i++)
    {
        divVector.m_coordinates[i] = m_coordinates[i] / other[i];
    }
    return divVector;
}

template<class T, size_t N>
Vector<T, N> &Vector<T, N>::operator/=(const Vector<T, N> &other)
{
    for (size_t i = 0; i < N; i++)
    {
        m_coordinates[i] /= other[i];
    }
    return *this;
}

template<class T, size_t N>
Vector<T, N> Vector<T, N>::operator*(const Vector<T, N> &other) const
{
    Vector<T, N> prodVector;
    for (size_t i = 0; i < N; i++)
    {
        prodVector.m_coordinates[i] = m_coordinates[i] * other[i];
    }
    return prodVector;
}

template<class T, size_t N>
Vector<T, N> &Vector<T, N>::operator*=(const Vector<T, N> &other)
{
    for (size_t i = 0; i < N; i++)
    {
        m_coordinates[i] *= other[i];
    }
    return *this;
}

template<class T, size_t N>
Vector<T, N> operator*(T k, const Vector<T, N>& vec)
{
    return vec * k;
}

template<class T, size_t N>
std::ostream& operator<<(std::ostream& os, const Vector<T, N>& vec)
{
    os << "Vector2D(";
    for (size_t i = 0; i < N; i++)
    {
        os << vec[i] << ", ";
    }
    os << ")";
    return os;
}


#endif //GAMETEST_VECTOR_H
