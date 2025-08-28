//
// Created by Максим Процик on 30.07.2023.
//

#include "Serialization/ComponentFactory.h"
#include "Game/Game.h"
#include "GameObject.h"

const std::vector<Component *> &GameObject::Components()
{
    return m_components;
}

GameObject::~GameObject()
{
    for (Component* comp: m_components)
    {
        delete comp;
    }
    m_components.clear();
}

template<>
void Clone<GameObject>(GameObject* to, GameObject* from)
{
    constexpr auto nbProperties = std::tuple_size<decltype(GameObject::properties)>::value;

    for_sequence(std::make_index_sequence<nbProperties>{}, [&](auto i) {
        constexpr auto prop = std::get<i>(GameObject::properties);
        using Type = typename decltype(prop)::Type;

        auto fromPtr = &(from->*(prop.member));
        auto toPtr = &(to->*(prop.member));
        Clone(toPtr, fromPtr);
    });

    auto factory = ComponentFactory::GetInstance();
    for (auto* comp: from->Components())
    {
        std::string name = comp->ComponentName();
        auto newComp = factory->CreateComponent(to, name);
        factory->CloneComponent(newComp, comp, name);
    }

}

template<>
void FromJson<GameObject>(GameObject* obj, const nlohmann::json& data)
{
    if (data.contains("Prefab"))
    {
        std::string name = data["Prefab"].get<std::string>();
        const auto& prefabs = Game::GetInstance()->CurrentScene()->Prefabs();
        auto itr = std::find_if(prefabs.begin(), prefabs.end(), [&name](GameObject* ptr){return ptr->Name == name;});
        if (itr != prefabs.end())
        {
            Clone(obj, *itr);
        }
    }
    constexpr auto nbProperties = std::tuple_size<decltype(GameObject::properties)>::value;

    for_sequence(std::make_index_sequence<nbProperties>{}, [&](auto i) {
        constexpr auto prop = std::get<i>(GameObject::properties);
        if (!data.contains(prop.name))
        {
            return;
        }
        using Type = typename decltype(prop)::Type;

        auto propertyPtr = &(obj->*(prop.member));
        FromJson(propertyPtr, data[prop.name]);
    });

    if (!data.contains("Components"))
    {
        return;
    }
    auto factory = ComponentFactory::GetInstance();
    for (auto& comp: data["Components"])
    {
        if (!comp.contains("Name"))
        {
            continue;
        }
        Component* component = factory->CreateComponent(obj, comp["Name"]);
        factory->ParseComponent(component, comp, comp["Name"]);
    }

}