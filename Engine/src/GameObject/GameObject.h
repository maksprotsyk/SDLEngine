//
// Created by Максим Процик on 30.07.2023.
//

#ifndef GAMEENGINE_GAMEOBJECT_H
#define GAMEENGINE_GAMEOBJECT_H

#include <utility>
#include <vector>

#include "Components/Component.h"
#include "Serialization/Cloning.h"
#include "Transform.h"

class Scene;

class GameObject
{
public:
    const std::vector<Component*>& Components();

    std::string Tag;
    std::string Name;

    Transform transform;

    GameObject() = default;

    template<class T>
    T* AddComponent();

    template<class T>
    T* FindComponent();

    ~GameObject();

private:
    std::vector<Component*> m_components;
public:
    SERIALIZABLE(PROPERTY(GameObject, Tag),
                 PROPERTY(GameObject, Name),
                 NAMED_PROPERTY(GameObject, transform, "Transform"))

};

template<>
void FromJson<GameObject>(GameObject* obj, const nlohmann::json& data);

template<class T>
T* GameObject::FindComponent()
{
    for (auto* comp: m_components)
    {
        auto newPtr = dynamic_cast<T*>(comp);
        if (!newPtr)
        {
            continue;
        }
        return newPtr;
    }

    return nullptr;


}

template<class T>
T* GameObject::AddComponent()
{
    T* originalPtr = new T;
    auto basePtr = (Component*)originalPtr;
    basePtr->SetGameObject(this);
    m_components.push_back(basePtr);
    return originalPtr;
}


#endif //GAMEENGINE_GAMEOBJECT_H
