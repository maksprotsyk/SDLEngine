//
// Created by Максим Процик on 19.08.2023.
//

#ifndef GAMETEST_RENDERABLERECTANGLE_H
#define GAMETEST_RENDERABLERECTANGLE_H

#include "Utils/Color.h"
#include "Renderable.h"

class RenderableRectangle: public Renderable
{
public:
    void SetWidth(float width);
    float GetWidth() const;
    void SetHeight(float height);
    float GetHeight() const;
    void SetColor(const Color& color);
    const Color& GetColor() const;

protected:
    void InitTexture() override;
    SDL_Rect GetRect() const override;
private:
    Color m_color;
    float m_height = 0.1f;
    float m_width = 0.2f;
public:
    SERIALIZABLE(NAMED_PROPERTY(RenderableRectangle, m_height, "Height"),
                 NAMED_PROPERTY(RenderableRectangle, m_width, "Width"),
                 PROPERTY(RenderableRectangle, Layer),
                 NAMED_PROPERTY(RenderableRectangle, m_color, "Color"))

};


#endif //GAMETEST_RENDERABLERECTANGLE_H
