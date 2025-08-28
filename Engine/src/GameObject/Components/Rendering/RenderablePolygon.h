//
// Created by Максим Процик on 19.08.2023.
//

#ifndef GAMETEST_RENDERABLEPOLYGON_H
#define GAMETEST_RENDERABLEPOLYGON_H

#include <vector>

#include "SDL2/SDL.h"

#include "Utils/Color.h"
#include "Utils/Vector2D.h"
#include "Renderable.h"

class RenderablePolygon: public Renderable
{
public:
    void SetColor(const Color& color);
    [[nodiscard]] const Color& GetColor() const;

    void SetHeight(float height);
    [[nodiscard]] float GetHeight() const;

    void SetWidth(float width);
    [[nodiscard]] float GetWidth() const;

    void SetPoints(const std::vector<Vector2D>& points);
    [[nodiscard]] const std::vector<Vector2D>& GetPoints() const;
protected:
    void InitTexture() override;
    SDL_Rect GetRect() const override;
private:
    Color m_color;
    float m_height = 0.2;
    float m_width = 0.1;
    std::vector<Vector2D> m_points;
public:
    SERIALIZABLE(NAMED_PROPERTY(RenderablePolygon, m_points, "Points"),
                 NAMED_PROPERTY(RenderablePolygon, m_height, "Height"),
                 NAMED_PROPERTY(RenderablePolygon, m_width, "Width"),
                 PROPERTY(RenderablePolygon, Layer),
                 NAMED_PROPERTY(RenderablePolygon, m_color, "Color"))
};


#endif //GAMETEST_RENDERABLEPOLYGON_H
