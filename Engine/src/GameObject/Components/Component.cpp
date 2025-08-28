//
// Created by Максим Процик on 30.07.2023.
//

#include "Component.h"
#include <cxxabi.h>

void Component::SetGameObject(GameObject* obj)
{
    m_GameObject = obj;
}

GameObject* Component::GetGameObject() const
{
    return m_GameObject;
}

void Component::OnStart()
{

}

void Component::OnUpdate()
{

}

void Component::OnFinish()
{

}

std::string Component::ComponentName()
{
    return abi::__cxa_demangle(typeid(*this).name(), nullptr, nullptr, nullptr);
}
