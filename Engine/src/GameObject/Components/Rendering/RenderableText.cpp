//
// Created by Максим Процик on 06.08.2023.
//

#include "RenderableText.h"
#include "Modules/Renderer.h"
#include "GameObject/GameObject.h"
#include "Game/Game.h"

#include "SDL2/SDL_ttf.h"

REGISTER(RenderableText)

void RenderableText::InitTexture()
{
    Renderer* renderer = Renderer::GetInstance();
    TTF_Font* font = TTF_OpenFont(m_fontName.c_str(), m_fontSize);
    SDL_Color color = {m_fontColor.r, m_fontColor.g, m_fontColor.b, m_fontColor.a};

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, m_text.c_str(), color);

    m_texture = SDL_CreateTextureFromSurface(renderer->GetRenderer(), surfaceMessage);

    SDL_FreeSurface(surfaceMessage);
}

SDL_Rect RenderableText::GetRect() const
{
    Renderer* renderer = Renderer::GetInstance();

    Transform currentTransform = m_GameObject->transform;
    Transform cameraTransform = Game::GetInstance()->CurrentScene()->cameraTransform;

    Vector2D abstractPosition = currentTransform.Position - cameraTransform.Position;

    auto floatWidth = (float)renderer->GetWidth();
    int posX = (int) (abstractPosition.X * floatWidth + floatWidth / 2);
    int posY = (int) (abstractPosition.Y * floatWidth + floatWidth / 2);

    int newWidth = (int) (currentTransform.Scale.X * Width * (float)renderer->GetWidth());
    int newHeight = (int) (currentTransform.Scale.Y * Height * (float)renderer->GetWidth());

    SDL_Rect rectangle;
    rectangle.x = posX - newWidth/2;
    rectangle.y = posY - newHeight/2;
    rectangle.w = newWidth;
    rectangle.h = newHeight;

    return rectangle;

}

void RenderableText::SetFontName(const std::string& fontName)
{
    m_shouldInit = true;
    m_fontName = fontName;
}

const std::string &RenderableText::GetFontName() const
{
    return m_fontName;
}

void RenderableText::SetFontColor(const Color& color)
{
    m_shouldInit = true;
    m_fontColor = color;
}

const Color &RenderableText::GetFontColor() const
{
    return m_fontColor;
}

void RenderableText::SetFontSize(int fontSize)
{
    m_shouldInit = true;
    m_fontSize = fontSize;
}

int RenderableText::GetFontSize() const
{
    return m_fontSize;
}

void RenderableText::SetText(const std::string& text)
{
    m_shouldInit = true;
    m_text = text;
}

const std::string &RenderableText::GetText() const
{
    return m_text;
}
