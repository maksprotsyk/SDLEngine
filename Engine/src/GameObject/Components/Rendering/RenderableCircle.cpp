//
// Created by Максим Процик on 29.07.2023.
//
#include "RenderableCircle.h"
#include "Modules/Renderer.h"
#include "Serialization/ComponentFactory.h"
#include "Game/Game.h"

REGISTER(RenderableCircle)

void RenderableCircle::OnRender(const SDL_Rect &rect)
{
    Renderer* renderer = Renderer::GetInstance();
    SDL_RenderCopy(
            renderer->GetRenderer(),
            m_texture,
            nullptr,
            &rect
    );
}

void RenderableCircle::InitTexture()
{
    Renderer* renderer = Renderer::GetInstance();
    SDL_Renderer* rendererSDL = renderer->GetRenderer();
    float floatRadius = m_radius * (float)renderer->GetWidth();
    int pixelRadius = (int)floatRadius;
    int size = 2 * pixelRadius + 1;
    m_texture = SDL_CreateTexture(
            rendererSDL,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            size,
            size
            );

    SDL_SetRenderTarget(rendererSDL, m_texture);

    SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(rendererSDL, 0, 0, 0, 0);
    SDL_RenderClear(rendererSDL);
    SDL_SetRenderDrawColor(rendererSDL, m_color.r, m_color.g, m_color.b, m_color.a);

    float radiusSqr = floatRadius * floatRadius;
    for (int x = 0; x <= pixelRadius; x++)
    {
        int y = (int)std::sqrt(radiusSqr - (float)(x*x));

        std::vector<SDL_Point> points = {
            SDL_Point{pixelRadius - x, pixelRadius - y},
            SDL_Point{pixelRadius + x, pixelRadius - y},
            SDL_Point{pixelRadius + x, pixelRadius + y},
            SDL_Point{pixelRadius - x, pixelRadius + y},
            SDL_Point{pixelRadius - x, pixelRadius - y},
        };

        SDL_RenderDrawLines(rendererSDL,
                            &points[0],
                            (int)points.size());
    }

    SDL_SetRenderTarget(rendererSDL, nullptr);
}

SDL_Rect RenderableCircle::GetRect() const
{
    Renderer* renderer = Renderer::GetInstance();
    Transform cameraTransform = Game::GetInstance()->CurrentScene()->cameraTransform;
    Transform objTransform = m_GameObject->transform;

    auto pixelWidth = (float) renderer->GetWidth();
    Vector2D pos = pixelWidth * (objTransform.Position - cameraTransform.Position);

    float pixelRadius = pixelWidth * m_radius * m_GameObject->transform.Scale.X;

    SDL_Rect rectangle;
    rectangle.x = (int)(pos.X - pixelRadius + pixelWidth / 2);
    rectangle.y = (int)(pos.Y - pixelRadius + pixelWidth / 2);
    rectangle.h = (int) (2 * pixelRadius);
    rectangle.w = (int) (2 * pixelRadius);

    return rectangle;
}

void RenderableCircle::SetRadius(float radius)
{
    m_shouldInit = true;
    m_radius = radius;
}

const float& RenderableCircle::GetRadius() const
{
    return m_radius;
}

void RenderableCircle::SetColor(const Color& color)
{
    m_shouldInit = true;
    m_color = color;
}

const Color& RenderableCircle::GetColor() const
{
    return m_color;
}
