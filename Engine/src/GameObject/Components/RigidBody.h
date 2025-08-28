//
// Created by Максим Процик on 18.08.2023.
//

#ifndef GAMETEST_RIGIDBODY_H
#define GAMETEST_RIGIDBODY_H

#include "Utils/Vector2D.h"
#include "Component.h"

class RigidBody: public Component
{
public:
    Vector2D Velocity;
    Vector2D Acceleration;
    float AngularVelocity = 0.0f;
    float Torque = 0.0f;
    float Mass = 0.0f;
    float PreservedEnergy = 1.0f;
    float MomentOfInertia = 0.0f;
    bool Static = false;

    void ApplyForce(const Vector2D& force, float time, const Vector2D& point);
    void ApplyAngularForce(const Vector2D& force, float time, const Vector2D& point);
    void ApplyLinearForce(const Vector2D& force, float time);

    void ApplyImpulse(const Vector2D& impulse, const Vector2D& point);
    void ApplyAngularImpulse(const Vector2D& impulse, const Vector2D& point);
    void ApplyLinearImpulse(const Vector2D& impulse);

    void ApplyAcceleration(const Vector2D& force, const Vector2D& point);
    void ApplyLinearAcceleration(const Vector2D& force);
    void ApplyAngularAcceleration(const Vector2D& force, const Vector2D& point);

    SERIALIZABLE(PROPERTY(RigidBody, Velocity),
                 PROPERTY(RigidBody, AngularVelocity),
                 PROPERTY(RigidBody, Acceleration),
                 PROPERTY(RigidBody, Torque),
                 PROPERTY(RigidBody, PreservedEnergy),
                 PROPERTY(RigidBody, Static),
                 PROPERTY(RigidBody, Mass),
                 PROPERTY(RigidBody, MomentOfInertia))
};


#endif //GAMETEST_RIGIDBODY_H
