//
// Created by Максим Процик on 04.08.2023.
//

#include "Sprite.h"
#include "Modules/Renderer.h"
#include "Game/Scene.h"
#include "Game/Game.h"

REGISTER(Sprite)

void Sprite::InitTexture()
{
    Renderer* renderer = Renderer::GetInstance();
    m_texture = IMG_LoadTexture(renderer->GetRenderer(), m_imagePath.c_str());
}

SDL_Rect Sprite::GetRect() const
{
    Renderer* renderer = Renderer::GetInstance();
    SDL_Rect rectangle;
    Transform currentTransform = m_GameObject->transform;
    Transform cameraTransform = Game::GetInstance()->CurrentScene()->cameraTransform;

    Vector2D abstractPosition = currentTransform.Position - cameraTransform.Position;

    auto floatWidth = (float)renderer->GetWidth();
    int posX = (int) (abstractPosition.X * floatWidth + floatWidth / 2);
    int posY = (int) (abstractPosition.Y * floatWidth + floatWidth / 2);

    int newWidth = (int) (currentTransform.Scale.X * floatWidth * Width);
    int newHeight = (int) (currentTransform.Scale.Y * floatWidth * Height);

    rectangle.x = posX - newWidth/2;
    rectangle.y = posY - newHeight/2;
    rectangle.w = newWidth;
    rectangle.h = newHeight;

    return rectangle;
}

const std::string &Sprite::GetImagePath() const
{
    return m_imagePath;
}

void Sprite::SetImagePath(const std::string& imagePath)
{
    m_shouldInit = true;
    m_imagePath = imagePath;
}

