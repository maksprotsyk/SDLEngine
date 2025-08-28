//
// Created by Максим Процик on 29.07.2023.
//

#ifndef GAMEENGINE_TRANSFORM_H
#define GAMEENGINE_TRANSFORM_H

#include "GameObject/Components/Component.h"
#include "Utils/Vector2D.h"
#include "Serialization/Parsing.h"


class Transform
{
public:
    Vector2D Position;
    Vector2D Scale;
    float RotationAngle = 0.0f;

    void Rotate(float angle, const Vector2D& center);

    Transform();

    SERIALIZABLE(PROPERTY(Transform, Position),
                 PROPERTY(Transform, Scale),
                 PROPERTY(Transform, RotationAngle))

};

#endif //GAMEENGINE_TRANSFORM_H
