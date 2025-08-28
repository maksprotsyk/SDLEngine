//
// Created by Максим Процик on 04.08.2023.
//

#ifndef GAMETEST_COMPONENTFACTORY_H
#define GAMETEST_COMPONENTFACTORY_H

#include <unordered_map>

#include "GameObject/GameObject.h"

using ParserMethod = std::function<void(Component*, const nlohmann::json& data)>;
using CreatorMethod = std::function<Component*(GameObject*)>;
using CloningMethod = std::function<void (Component*, Component*)>;

struct ComponentMethods
{
    CreatorMethod Creator;
    ParserMethod Parser;
    CloningMethod Cloner;
};

class ComponentFactory
{
public:
    static ComponentFactory* GetInstance();
    void Register(const std::string& name, const ComponentMethods& methods);
    Component* CreateComponent(GameObject* obj, const std::string& name);
    void ParseComponent(Component* comp, const nlohmann::json& data, const std::string& name);
    void CloneComponent(Component* to, Component* from, const std::string& name);
private:
    ComponentFactory() = default;
    static ComponentFactory* m_componentFactory;
    std::unordered_map<std::string, ComponentMethods> m_componentsCreators{};
};

template <class T>
class Registerer
{
public:
    explicit Registerer();
};

template <class T>
Registerer<T>::Registerer()
{
    T comp;
    std::string name = comp.ComponentName();
    ComponentMethods methods;
    methods.Creator = &GameObject::AddComponent<T>;
    methods.Parser = [](Component* comp, const nlohmann::json& data){FromJson((T*) comp, data);};
    methods.Cloner = [](Component* to, Component* from){Clone((T*) to, (T*) from);};
    auto ptr = ComponentFactory::GetInstance();
    ptr->Register(name, methods);
}


#define REGISTER(T) \
static const Registerer<T> reg = Registerer<T>();
#endif //GAMETEST_COMPONENTFACTORY_H
