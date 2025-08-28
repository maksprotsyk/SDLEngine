//
// Created by Максим Процик on 19.08.2023.
//
#include "Modules/Renderer.h"
#include "Game/Game.h"
#include "Serialization/ComponentFactory.h"

#include "RenderableRectangle.h"

REGISTER(RenderableRectangle)

SDL_Rect RenderableRectangle::GetRect() const
{
    Renderer* renderer = Renderer::GetInstance();
    Transform cameraTransform = Game::GetInstance()->CurrentScene()->cameraTransform;
    Transform objTransform = m_GameObject->transform;

    auto pixelWidth = (float) renderer->GetWidth();
    Vector2D pos = pixelWidth * (objTransform.Position
                                 - cameraTransform.Position
                                 - 0.5 * Vector2D(m_width, m_height));

    SDL_Rect rectangle;
    rectangle.x = (int)(pos.X + pixelWidth / 2);
    rectangle.y = (int)(pos.Y + pixelWidth / 2);
    rectangle.h = (int) (m_height * pixelWidth);
    rectangle.w = (int) (m_width * pixelWidth);

    return rectangle;
}

void RenderableRectangle::InitTexture()
{
    Renderer* renderer = Renderer::GetInstance();
    SDL_Renderer* rendererSDL = renderer->GetRenderer();
    auto pixelWidth = (float) renderer->GetWidth();
    m_texture = SDL_CreateTexture(
            rendererSDL,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            (int)(pixelWidth * m_width),
            (int)(pixelWidth * m_height)
            );

    SDL_SetRenderTarget(rendererSDL, m_texture);

    SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(rendererSDL, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderClear(rendererSDL);

    SDL_SetRenderTarget(rendererSDL, nullptr);
}

void RenderableRectangle::SetWidth(float width)
{
    m_shouldInit = true;
    m_width = width;
}

float RenderableRectangle::GetWidth() const
{
    return m_width;
}

void RenderableRectangle::SetHeight(float height)
{
    m_shouldInit = true;
    m_height = height;
}

float RenderableRectangle::GetHeight() const
{
    return m_height;
}

void RenderableRectangle::SetColor(const Color& color)
{
    m_shouldInit = true;
    m_color = color;
}

const Color& RenderableRectangle::GetColor() const
{
    return m_color;
}
