//
// Created by Максим Процик on 01.08.2023.
//

#ifndef GAMEENGINE_GAME_H
#define GAMEENGINE_GAME_H

#include <vector>
#include <unordered_map>

#include "Modules/Renderer.h"
#include "Scene.h"

class Game
{
public:
    std::unordered_map<std::string, std::string> Scenes;
    static Game* GetInstance();
    void ChangeScene(const std::string& name);
    void Run();
    [[nodiscard]] bool HasQueuedScene() const;
    [[nodiscard]] Scene* CurrentScene() const;
    void ConfigureFromFile(const std::string& path);

    SERIALIZABLE(PROPERTY(Game, Scenes))

private:
    static Game* m_game;

    Scene* m_currentScene = nullptr;
    std::string m_queuedScene = "";
    bool m_sceneHasChanged = false;

    Game() = default;

    void CheckEvents(bool& exited);


};


#endif //GAMEENGINE_GAME_H
