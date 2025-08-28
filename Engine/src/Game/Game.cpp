//
// Created by Максим Процик on 01.08.2023.
//

#include <fstream>

#include "Modules/Time.h"
#include "Modules/Input.h"
#include "Serialization/Parsing.h"
#include "Game.h"

Game* Game::m_game = nullptr;

void Game::Run()
{

    Renderer* renderer = Renderer::GetInstance();
    Time* time = Time::GetInstance();

    time->Init();

    bool exited = false;
    while (!exited)
    {
        if (!m_sceneHasChanged)
        {
            return;
        }

        auto itr = Scenes.find(m_queuedScene);
        if (itr == Scenes.end())
        {
            break;
        }

        delete m_currentScene;
        m_sceneHasChanged = false;
        m_currentScene = new Scene(itr->first);
        m_currentScene->ConfigureFromFile(itr->second);
        m_queuedScene = "";

        m_currentScene->OnStart();

        while (!exited && !m_sceneHasChanged)
        {
            CheckEvents(exited);

            m_currentScene->CreateQueuedObjects();
            m_currentScene->DestroyQueuedObjects();

            time->OnUpdate();
            m_currentScene->OnUpdate();

            renderer->Clear(m_currentScene->BackgroundColor);
            m_currentScene->OnRender();

            renderer->Update();

        }
        m_currentScene->OnFinish();
    }
    delete m_currentScene;
}

Game* Game::GetInstance()
{
    if (!m_game)
    {
        m_game = new Game();
    }

    return m_game;
}

void Game::ChangeScene(const std::string& name)
{
    m_queuedScene = name;
    m_sceneHasChanged = true;
}

bool Game::HasQueuedScene() const
{
    return m_sceneHasChanged;
}

Scene *Game::CurrentScene() const
{
    return m_currentScene;
}

void Game::ConfigureFromFile(const std::string &path)
{
    std::ifstream file(path);
    nlohmann::json json;
    file >> json;
    FromJson(this, json);
}

void Game::CheckEvents(bool& exited)
{
    Renderer* renderer = Renderer::GetInstance();
    Input* input = Input::GetInstance();
    renderer->CheckEvents([&exited, &input](SDL_Event& event){
        switch (event.type)
        {
            case SDL_QUIT:
                exited = true;
                break;
            case SDL_KEYDOWN:
                input->KeyDown((SDL_KeyCode)(event.key.keysym.sym));
                break;
            case SDL_KEYUP:
                input->KeyUp((SDL_KeyCode)(event.key.keysym.sym));
                break;
        }
    });
}
