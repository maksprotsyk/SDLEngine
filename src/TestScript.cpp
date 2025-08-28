//
// Created by Максим Процик on 01.08.2023.
//

#include "TestScript.h"
#include "Modules/Time.h"
#include "Modules/Input.h"
#include "GameObject/Components/RigidBody.h"
#include "GameObject/Components/Rendering/RenderableCircle.h"
#include "GameObject/Components/Colliding/CircleCollider.h"
#include "Game/Game.h"

REGISTER(TestScript)

void TestScript::OnUpdate()
{
    /*
    RigidBody* myRigidBody = m_GameObject->FindComponent<RigidBody>();

    auto input = Input::GetInstance();
    auto time = Time::GetInstance();
    if (input->KeyPressed(Input::KeyCode::Down))
    {
        myRigidBody->ApplyLinearForce(Vector2D(0, 0.25), time->TimeDelta);
    }
    if (input->KeyPressed(Input::KeyCode::Up))
    {
        myRigidBody->ApplyLinearForce(Vector2D(0, -0.25), time->TimeDelta);
    }
    if (input->KeyPressed(Input::KeyCode::Left))
    {
        myRigidBody->ApplyLinearForce(Vector2D(-0.25, 0.0), time->TimeDelta);
    }
    if (input->KeyPressed(Input::KeyCode::Right))
    {
        myRigidBody->ApplyLinearForce(Vector2D(0.25, 0.0), time->TimeDelta);
    }

    */
}

void TestScript::OnStart()
{
    auto prefabs = Game::GetInstance()->CurrentScene()->Prefabs();
    int particleIndex = -1;
    for (int i = 0; i < prefabs.size(); i++)
    {
        if (prefabs[i]->Name == "particle")
        {
            particleIndex = i;
            break;
        }
    }
    if (particleIndex == -1)
    {
        return;
    }
    std::vector<Vector2D> velocities = {Vector2D(-0.0, 0.1), Vector2D(0.0, -0.0), Vector2D(-0.0, -0.0)};
    std::vector<Vector2D> positions = {Vector2D(-0.0, -0.20), Vector2D(-0.0, -0.08), Vector2D(-0.0, -0.3)};
    for (size_t i = 0; i < 2; i++)
    {
        auto obj = Game::GetInstance()->CurrentScene()->Instantiate(prefabs[particleIndex]);
        RigidBody* rigidBody = obj->FindComponent<RigidBody>();
        rigidBody->Velocity = velocities[i];
        obj->transform.Position = positions[i];
        if (i == 0)
        {
            rigidBody->Mass *= 2;
        }
    }
}
