//
// Created by Максим Процик on 29.07.2023.
//

#ifndef GAMEENGINE_RENDERABLECIRCLE_H
#define GAMEENGINE_RENDERABLECIRCLE_H

#include <cmath>

#include "Game/Scene.h"
#include "Renderable.h"

class RenderableCircle: public Renderable
{
public:
    void SetRadius(float radius);
    [[nodiscard]] const float& GetRadius() const;
    void SetColor(const Color& color);
    [[nodiscard]] const Color& GetColor() const;
protected:
    void OnRender(const SDL_Rect& rect) override;
    void InitTexture() override;
    SDL_Rect GetRect() const override;
private:
    Color m_color;
    float m_radius = 0.25f;
public:
    SERIALIZABLE(NAMED_PROPERTY(RenderableCircle, m_radius, "Radius"),
                 PROPERTY(RenderableCircle, Layer),
                 NAMED_PROPERTY(RenderableCircle, m_color, "Color"))
};


#endif //GAMEENGINE_RENDERABLECIRCLE_H
