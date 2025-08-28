//
// Created by Максим Процик on 19.08.2023.
//
#ifndef GAMETEST_RENDERABLE_H
#define GAMETEST_RENDERABLE_H

#include "SDL2/SDL.h"

#include "GameObject/Components/Component.h"

class Renderable: public Component
{
public:
    int Layer = 0;
    void OnRender();
    void OnStart() override;
    ~Renderable();
protected:
    virtual SDL_Rect GetRect() const = 0;
    virtual void OnRender(const SDL_Rect& rect);
    virtual void InitTexture() = 0;
    bool m_shouldInit = true;
    SDL_Texture* m_texture = nullptr;
};

#endif //GAMETEST_RENDERABLE_H
