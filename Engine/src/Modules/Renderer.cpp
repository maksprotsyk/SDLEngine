//
// Created by Максим Процик on 29.07.2023.
//

#include "Renderer.h"

#include "SDL_ttf.h"
#include "SDL2/SDL_blendmode.h"

Renderer* Renderer::m_rendererInstance = nullptr;

bool Renderer::Init(int width, int height, float gamma)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return false;
    }

    if (TTF_Init() != 0)
    {
        return false;
    }

    m_window = SDL_CreateWindow(
            "Game Engine",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_SHOWN
    );

    m_width = width;
    m_height = height;

    if (!m_window)
    {
        return false;
    }

    ChangeGamma(gamma);

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderPresent(m_renderer);
    return true;
}

void Renderer::Clear(const Color& color)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(m_renderer);
}

void Renderer::CheckEvents(const std::function<void(SDL_Event&)>& callback)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        callback(event);
    }
}

void Renderer::DeInit()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    TTF_Quit();
}

void Renderer::Update()
{
    SDL_RenderPresent(m_renderer);
}

int Renderer::GetWidth() const
{
    return m_width;
}

int Renderer::GetHeight() const
{
    return m_height;
}

SDL_Renderer* Renderer::GetRenderer() const
{
    return m_renderer;
}

void Renderer::Delay(int ms)
{
    SDL_Delay(ms);
}

Renderer *Renderer::GetInstance()
{
    if (!m_rendererInstance)
    {
        m_rendererInstance = new Renderer;
    }
    return m_rendererInstance;
}

void Renderer::ChangeGamma(float gamma)
{
    m_gamma = gamma;
    uint16_t ramp[256];
    SDL_CalculateGammaRamp(gamma, ramp);
    SDL_SetWindowGammaRamp(m_window, ramp, ramp, ramp);
}
