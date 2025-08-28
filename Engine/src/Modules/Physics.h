
#ifndef GAMETEST_PHYSICS_H
#define GAMETEST_PHYSICS_H

#include "GameObject/Components/Colliding/Collider.h"
#include "GameObject/Components/RigidBody.h"

class Physics
{
public:
    float G = 0.2;

    static Physics* GetInstance();
    void CreateObjects(const std::vector<GameObject*>& objects);
    void OnUpdate(float timeDelta, const std::vector<GameObject*>& objects);
private:
    static Vector2D HandleBorders(Collider* collider, RigidBody* rb);
    static float CalculateImpulse(RigidBody* rb1, RigidBody* rb2, const Collider::Collision& collision);

private:

    static Physics* m_physics;
    Physics() = default;

};

#endif