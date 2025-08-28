//
// Created by Максим Процик on 30.07.2023.
//

#ifndef GAMEENGINE_WORLD_H
#define GAMEENGINE_WORLD_H

#include "GameObject/GameObject.h"
#include "GameObject/Transform.h"
#include "GameObject/Components/Script.h"
#include "Serialization/Parsing.h"
#include "Utils/Color.h"

class Scene
{
public:
    Transform cameraTransform;
    const std::string Name;
    Color BackgroundColor{0, 0, 0, 255};

    Scene(std::string  name);

    [[nodiscard]] const std::vector<GameObject*>& Prefabs() const;
    [[nodiscard]] const std::vector<GameObject*>& Objects() const;

    void OnStart();
    void OnRender();
    void OnUpdate();
    void OnFinish();

    GameObject* Instantiate();
    GameObject* Instantiate(GameObject* prefab);
    void Destroy(GameObject* obj);

    void DestroyQueuedObjects();
    void CreateQueuedObjects();

    void ConfigureFromFile(const std::string& name);

    ~Scene();

private:
    std::vector<GameObject*> m_objects;
    std::vector<GameObject*> m_prefabs;
    std::vector<GameObject*> m_createdObjects;
    std::vector<GameObject*> m_destroyedObjects;
    float m_simulationTimeLeft = 0;


    void PerformAction(const std::function<void(Component*)>& action);
public:
    SERIALIZABLE(NAMED_PROPERTY(Scene, cameraTransform, "CameraTransform"),
                 PROPERTY(Scene, BackgroundColor),
                 NAMED_PROPERTY(Scene, m_prefabs, "Prefabs"),
                 NAMED_PROPERTY(Scene, m_objects, "Objects"))
};


#endif //GAMEENGINE_WORLD_H
