//
// Created by Максим Процик on 29.07.2023.
//

#ifndef GAMEENGINE_COMPONENT_H
#define GAMEENGINE_COMPONENT_H

#include <string>

#include "Serialization/Parsing.h"

class GameObject;
class Renderer;

class Component
{
public:
    bool Enabled = true;

    void SetGameObject(GameObject* obj);
    GameObject* GetGameObject() const;
    virtual ~Component() = default;

    virtual void OnStart();
    virtual void OnUpdate();
    virtual void OnFinish();

    virtual std::string ComponentName();

protected:
    GameObject* m_GameObject = nullptr;


};

#endif //GAMEENGINE_COMPONENT_H
