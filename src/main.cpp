//
// Created by Максим Процик on 01.08.2023.
//

#include "Modules/Renderer.h"
#include "Game/Game.h"

int main()
{

    Renderer* renderer = Renderer::GetInstance();
    if (!renderer->Init(1280, 720, 1.0f))
    {
        return -1;
    }
    Game* game = Game::GetInstance();
    game->ConfigureFromFile("Scene/game.json");
    game->ChangeScene("test2");
    game->Run();
    renderer->DeInit();

    return 0;
}