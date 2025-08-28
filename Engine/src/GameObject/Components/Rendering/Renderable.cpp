//
// Created by Максим Процик on 19.08.2023.
//

#include "Modules/Renderer.h"
#include "Game/Game.h"
#include "Renderable.h"

void Renderable::OnRender()
{
    if (m_shouldInit)
    {
        if (m_texture)
        {
            SDL_DestroyTexture(m_texture);
        }
        InitTexture();
        m_shouldInit = false;
    }

    Renderer* renderer = Renderer::GetInstance();
    SDL_Rect rect = GetRect();
    if (rect.x + rect.w < 0 ||
        rect.y + rect.h < 0 ||
        rect.x > renderer->GetWidth() ||
        rect.y > renderer->GetHeight())
    {
        return;
    }

    OnRender(rect);
}

Renderable::~Renderable() {
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }
}

void Renderable::OnStart()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }
    InitTexture();
    m_shouldInit = false;
}

void Renderable::OnRender(const SDL_Rect &rect)
{
    Renderer* renderer = Renderer::GetInstance();
    Transform currentTransform = m_GameObject->transform;
    Transform cameraTransform = Game::GetInstance()->CurrentScene()->cameraTransform;

    SDL_Point center;
    center.x = rect.w / 2;
    center.y = rect.h / 2;

    SDL_RenderCopyEx(
            renderer->GetRenderer(),
            m_texture,
            nullptr,
            &rect,
            currentTransform.RotationAngle - cameraTransform.RotationAngle,
            &center,
            SDL_FLIP_NONE);
}
