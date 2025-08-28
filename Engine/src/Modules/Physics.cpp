#include "Physics.h"
#include "CollisionHandler.h"
#include "GameObject/Components/RigidBody.h"
#include "Utils/Math.h"

Physics* Physics::m_physics = nullptr;

Physics* Physics::GetInstance()
{
    if (!m_physics)
    {
        m_physics = new Physics;
    }
    return m_physics;
}

void Physics::CreateObjects(const std::vector<GameObject*>& objects)
{
    Vector2D gravityDirection = Vector2D(0.0, 1.0);
    for (auto* obj: objects)
    {
        RigidBody* rigidBody = obj->FindComponent<RigidBody>();
        if (!rigidBody)
        {
            continue;
        }

        rigidBody->ApplyLinearAcceleration(G * gravityDirection);
    }
}
#include "iostream"
void Physics::OnUpdate(float timeDelta, const std::vector<GameObject*>& objects)
{
    for (auto* obj: objects)
    {
        RigidBody* rigidBody = obj->FindComponent<RigidBody>();
        if (!rigidBody || rigidBody->Static)
        {
            continue;
        }

        rigidBody->Velocity += 0.5f * timeDelta * rigidBody->Acceleration;
        rigidBody->AngularVelocity += 0.5f * timeDelta * rigidBody->Torque;
    }
    const int maxIterations = 10;
    for (size_t i = 0; i < maxIterations; i++)
    {
        Vector2D momentTotalDiff;
        for (auto* obj: objects)
        {
            RigidBody* rigidBody = obj->FindComponent<RigidBody>();
            if (!rigidBody || rigidBody->Static)
            {
                continue;
            }
            Collider* collider = obj->FindComponent<Collider>();
            if (!collider)
            {
                continue;
            }
            momentTotalDiff += HandleBorders(collider, rigidBody);
        }
        if (Math::Equal(momentTotalDiff.Length(), 0))
        {
            break;
        }

    }

    for (auto* obj: objects)
    {
        RigidBody* rigidBody = obj->FindComponent<RigidBody>();
        if (!rigidBody || rigidBody->Static)
        {
            continue;
        }

        obj->transform.Position += timeDelta * rigidBody->Velocity;
        obj->transform.Rotate(
                timeDelta * rigidBody->AngularVelocity,
                obj->transform.Position
                );
        rigidBody->Velocity += 0.5f * timeDelta * rigidBody->Acceleration;
        rigidBody->AngularVelocity += 0.5f * timeDelta * rigidBody->Torque;

    }
}

Vector2D Physics::HandleBorders(Collider *collider, RigidBody* rb)
{
    Vector2D totalDiff;
    if (rb->Static)
    {
        return totalDiff;
    }
    CollisionHandler* collisionHandler = CollisionHandler::GetInstance();
    auto collisions = collisionHandler->GetActiveCollisions(collider);
    for (auto& [colliderOther, collision]: collisions)
    {
        Vector2D normal = collision.normal;
        auto* rbOther = colliderOther->GetGameObject()->FindComponent<RigidBody>();
        if (!rbOther)
        {
            continue;
        }

        float projection1 = rb->Velocity * normal;
        float projection2 = rbOther->Velocity * normal;
        if (projection2 >= projection1)
        {
            continue;
        }
        if (rbOther->Static)
        {
            Vector2D speedDelta = rb->Velocity - rbOther->Velocity;
            float impulse = -2.0f * rb->Mass * speedDelta * normal;
            Vector2D diff = impulse / rb->Mass * normal;
            rb->Velocity += diff;
            totalDiff += diff;
            continue;
        }

        if (rb <= rbOther)
        {
            continue;
        }

        Vector2D speedDelta = rb->Velocity - rbOther->Velocity;
        float impulse = (-2.0f * speedDelta * normal) / (1.0f / rb->Mass + 1.0f / rbOther->Mass);

        Vector2D diff1 = impulse / rb->Mass * normal;
        Vector2D diff2 = -impulse / rbOther->Mass * normal;
        rb->Velocity += diff1;
        rbOther->Velocity += diff2;

        totalDiff += diff1 + diff2;

    }

    return totalDiff;
}

float Physics::CalculateImpulse(RigidBody *rb1, RigidBody *rb2, const Collider::Collision& collision)
{
    Vector2D speedDelta = rb1->Velocity - rb2->Velocity;
    float epsilon = 2.0f / (1.0f/rb1->PreservedEnergy + 1.0f/rb2->PreservedEnergy);
    Vector2D r1 = collision.point - rb1->GetGameObject()->transform.Position;
    Vector2D r2 = collision.point - rb2->GetGameObject()->transform.Position;
    Vector2D normal = collision.normal;
    float massCoefficient = 1.0f/rb1->Mass + 1.0f/rb2->Mass;
    float numerator = -(1.0f + epsilon) * speedDelta * normal;
    float denominatorLinear = massCoefficient * normal * normal;
    float denominatorAngular1 = (1.0f/rb1->MomentOfInertia * (r1.CrossProduct(normal)));
    return 0;
}
