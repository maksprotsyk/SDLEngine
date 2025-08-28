//
// Created by Максим Процик on 30.07.2023.
//

#include <fstream>
#include <utility>

#include "Modules/Physics.h"
#include "Modules/CollisionHandler.h"
#include "Modules/Time.h"

#include "GameObject/Components/Rendering/Renderable.h"

#include "Scene.h"


Scene::Scene(std::string  name): Name(std::move(name))
{

}

GameObject *Scene::Instantiate()
{
    auto obj = new GameObject();
    m_createdObjects.push_back(obj);
    return obj;
}

GameObject *Scene::Instantiate(GameObject* prefab)
{
    auto obj = new GameObject();
    Clone(obj, prefab);
    m_createdObjects.push_back(obj);
    return obj;
}

void Scene::Destroy(GameObject *obj) {
    m_destroyedObjects.push_back(obj);
}

void Scene::CreateQueuedObjects()
{
    size_t createdCount = m_createdObjects.size();
    for (size_t i = 0; i < createdCount; i++)
    {
        m_objects.push_back(m_createdObjects[i]);
        for (auto* comp : m_createdObjects[i]->Components())
        {
            comp->OnStart();
        }
    }
    Physics::GetInstance()->CreateObjects(m_createdObjects);
    m_createdObjects.erase(m_createdObjects.begin(), m_createdObjects.begin() + (int)createdCount);
}

void Scene::DestroyQueuedObjects()
{
    CollisionHandler::GetInstance()->DestroyObjects(m_destroyedObjects);
    size_t destroyedCount = m_destroyedObjects.size();
    for (size_t i = 0; i < destroyedCount; i++)
    {
        auto itr = std::find(m_objects.begin(), m_objects.end(), m_destroyedObjects[i]);
        if (itr == m_objects.end())
        {
            continue;
        }

        for (auto* comp : m_destroyedObjects[i]->Components())
        {
            comp->OnFinish();
        }

        delete m_destroyedObjects[i];

    }
    m_destroyedObjects.erase(m_destroyedObjects.begin(), m_destroyedObjects.begin() + (int)destroyedCount);
}

void Scene::PerformAction(const std::function<void(Component*)>& action)
{
    for (GameObject* obj: m_objects)
    {
        for (Component* comp: obj->Components())
        {
            action(comp);
        }
    }
}

Scene::~Scene()
{
    for (auto* obj: m_objects)
    {
        delete obj;
    }

    for (auto* prefab: m_prefabs)
    {
        delete prefab;
    }

    for (auto* obj: m_createdObjects)
    {
        delete obj;
    }

}

void Scene::ConfigureFromFile(const std::string &name)
{
    std::ifstream file(name);
    nlohmann::json json;
    file >> json;
    FromJson(this, json);

}

const std::vector<GameObject *> &Scene::Prefabs() const
{
    return m_prefabs;
}

const std::vector<GameObject *> &Scene::Objects() const
{
    return m_objects;
}

void Scene::OnStart()
{
    Physics::GetInstance()->CreateObjects(m_objects);
    PerformAction([](Component* comp){comp->OnStart();});
}

void Scene::OnUpdate()
{

    PerformAction([](Component* comp){
        if (comp->Enabled)
        {
            comp->OnUpdate();
        }
    });
    float deltaTime = Time::GetInstance()->TimeDelta;
    float simulationDelta = 0.0166;
    m_simulationTimeLeft += deltaTime;
    while (m_simulationTimeLeft >= simulationDelta)
    {
        CollisionHandler::GetInstance()->OnUpdate(m_objects);
        Physics::GetInstance()->OnUpdate(simulationDelta, m_objects);
        m_simulationTimeLeft -= deltaTime;
    }
}

void Scene::OnRender()
{
    std::vector<Renderable*> renderables;
    for (auto* obj: m_objects)
    {
        auto renderable = obj->FindComponent<Renderable>();
        if (renderable)
        {
            renderables.push_back(renderable);
        }
    }
    std::sort(renderables.begin(), renderables.end(), [](const Renderable* rend1, const Renderable* rend2){
        return rend1->Layer > rend2->Layer;
    });

    for (auto* rend: renderables)
    {
        rend->OnRender();
    }
}

void Scene::OnFinish()
{
    CollisionHandler::GetInstance()->OnFinish();
    PerformAction([](Component* comp){comp->OnFinish();});
}
