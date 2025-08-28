//
// Created by Максим Процик on 04.08.2023.
//

#include "ComponentFactory.h"

ComponentFactory* ComponentFactory::m_componentFactory = nullptr;

Component *ComponentFactory::CreateComponent(GameObject* obj, const std::string& name)
{
    auto itr = m_componentsCreators.find(name);
    if (itr != m_componentsCreators.end())
    {
        return itr->second.Creator(obj);
    }
    return obj->AddComponent<Component>();
}

void ComponentFactory::ParseComponent(Component *comp, const nlohmann::json& data, const std::string& name)
{
    auto itr = m_componentsCreators.find(name);
    if (itr != m_componentsCreators.end())
    {
        itr->second.Parser(comp, data);
        return;
    }
}

void ComponentFactory::CloneComponent(Component* to, Component* from, const std::string& name)
{
    auto itr = m_componentsCreators.find(name);
    if (itr != m_componentsCreators.end())
    {
        itr->second.Cloner(to, from);
        return;
    }
}

ComponentFactory *ComponentFactory::GetInstance()
{
    if (!m_componentFactory)
    {
        m_componentFactory = new ComponentFactory;
    }
    return m_componentFactory;
}

void ComponentFactory::Register(const std::string& name, const ComponentMethods& methods)
{
    m_componentsCreators[name] = methods;
}