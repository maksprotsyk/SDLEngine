//
// Created by Максим Процик on 29.07.2023.
//

#ifndef GAMEENGINE_WINDOW_H
#define GAMEENGINE_WINDOW_H

#include <functional>

#include <SDL2/SDL.h>

#include "Utils/Color.h"

class Renderer
{
public:
    static Renderer* GetInstance();
    bool Init(int width, int height, float gamma);
    void Clear(const Color& color);
    void CheckEvents(const std::function<void(SDL_Event&)>& callback);
    void Update();
    void Delay(int ms);
    [[nodiscard]] SDL_Renderer* GetRenderer() const;
    void DeInit();
    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetHeight() const;
    void ChangeGamma(float gamma);

private:
    static Renderer* m_rendererInstance;

    SDL_Renderer* m_renderer = nullptr;
    SDL_Window* m_window = nullptr;
    int m_width = 0;
    int m_height = 0;
    float m_gamma = 1.0;

    Renderer() = default;

};

#endif //GAMEENGINE_WINDOW_H
