//
// Created by Максим Процик on 18.08.2023.
//

#include "Serialization/ComponentFactory.h"
#include "RigidBody.h"

REGISTER(RigidBody)

void RigidBody::ApplyForce(const Vector2D& force, float time, const Vector2D& point)
{
    ApplyImpulse(time * force, point);
}

void RigidBody::ApplyLinearForce(const Vector2D& force, float time)
{
    ApplyLinearImpulse(time * force);
}

void RigidBody::ApplyAngularForce(const Vector2D& force, float time, const Vector2D& point)
{
    ApplyAngularImpulse(time * force, point);
}

void RigidBody::ApplyImpulse(const Vector2D& impulse, const Vector2D& point)
{
    ApplyLinearImpulse(impulse);
    ApplyAngularImpulse(impulse, point);
}

void RigidBody::ApplyLinearImpulse(const Vector2D& impulse)
{
    if (Static)
    {
        return;
    }
    Velocity += 1.0f/Mass * impulse;
}

void RigidBody::ApplyAngularImpulse(const Vector2D& impulse, const Vector2D& point)
{
    if (Static)
    {
        return;
    }
    Vector2D radiusVector = m_GameObject->transform.Position - point;
    float angularImpulse = radiusVector.CrossProduct(impulse);
    AngularVelocity = 1.0f/Inertia() * angularImpulse;
}


void RigidBody::ApplyAcceleration(const Vector2D& force, const Vector2D& point)
{
    ApplyLinearAcceleration(force);
    ApplyAngularAcceleration(force, point);
}

void RigidBody::ApplyLinearAcceleration(const Vector2D& force)
{
    if (Static)
    {
        return;
    }
    Acceleration += force;
}
void RigidBody::ApplyAngularAcceleration(const Vector2D& force, const Vector2D& point)
{
    if (Static)
    {
        return;
    }
    Vector2D radiusVector = m_GameObject->transform.Position - point;
    float angularImpulse = radiusVector.CrossProduct(force);
    Torque += angularImpulse;
}
