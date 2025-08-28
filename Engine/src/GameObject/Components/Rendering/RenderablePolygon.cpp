//
// Created by Максим Процик on 19.08.2023.
//

#include "Serialization/ComponentFactory.h"
#include "Modules/Renderer.h"
#include "Game/Game.h"
#include "RenderablePolygon.h"

REGISTER(RenderablePolygon)

void RenderablePolygon::InitTexture()
{
    Renderer* renderer = Renderer::GetInstance();
    float floatWidth = m_width * (float)renderer->GetWidth();
    int pixelWidth = (int)floatWidth;
    float floatHeight = m_height * (float) renderer->GetWidth();
    int pixelHeight = (int)floatHeight;

    m_texture = SDL_CreateTexture(
            renderer->GetRenderer(),
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            pixelWidth,
            pixelHeight
    );

    using line_t = std::pair<Vector2D, Vector2D>;

    std::vector<line_t> lines;
    lines.reserve(m_points.size());

    float epsilon = 0.00001;
    for (size_t i = 1; i <= m_points.size(); i++)
    {
        size_t second = i % m_points.size();
        size_t first = i - 1;
        Vector2D pixelPoint1 = ((float)pixelWidth) * m_points[first];
        Vector2D pixelPoint2 = ((float)pixelWidth) * m_points[second];
        if (std::abs(pixelPoint1.Y - pixelPoint2.Y) < epsilon)
        {
            continue;
        }
        lines.emplace_back(pixelPoint1, pixelPoint2);
    }

    std::sort(lines.begin(), lines.end(), [](const line_t& line1, const line_t& line2){
       return std::min(line1.first.Y, line1.second.Y) < std::min(line2.first.Y, line2.second.Y);
    });

    std::vector<std::pair<float, float>> coefficients;
    coefficients.reserve(lines.size());
    for (const line_t& line: lines)
    {
        float a = line.first.Y - line.second.Y;
        float b = line.second.X - line.first.X;
        float c = line.first.CrossProduct(line.second);
        coefficients.emplace_back(-b/a, -c/a);
    }

    auto itr = std::max_element(lines.begin(), lines.end(), [](const line_t& line1, const line_t& line2){
        return std::max(line1.first.Y, line1.second.Y) < std::max(line2.first.Y, line2.second.Y);
    });
    int maxY = (int)std::max(itr->first.Y, itr->second.Y);
    int minY = (int)std::min(lines[0].first.Y, lines[0].second.Y);

    SDL_Renderer* rendererSDL = renderer->GetRenderer();
    SDL_SetRenderTarget(rendererSDL, m_texture);

    SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(rendererSDL, 0, 0, 0, 0);
    SDL_RenderClear(rendererSDL);
    SDL_SetRenderDrawColor(rendererSDL, m_color.r, m_color.g, m_color.b, m_color.a);

    std::vector<int> currentLines;
    int currentIndex = 0;
    for (int y = minY; y < maxY; y++)
    {
        float floatY = (float)y;

        while (!currentLines.empty())
        {
            const line_t& last = lines[currentLines.back()];
            float lineMaxY = std::max(last.first.Y, last.second.Y);
            if (lineMaxY < floatY)
            {
                currentLines.pop_back();
            }
            else
            {
                break;
            }
        }

        while (currentIndex < lines.size())
        {
            const line_t& currentLine = lines[currentIndex];
            float lineMinY = std::min(currentLine.first.Y, currentLine.second.Y);
            if (lineMinY <= floatY)
            {
                currentLines.push_back(currentIndex);
                currentIndex++;
            }
            else
            {
                break;
            }
        }

        std::sort(currentLines.begin(), currentLines.end(), [&lines](int index1, int index2){
            const auto& line1 = lines[index1];
            const auto& line2 = lines[index2];
            return std::max(line1.first.Y, line1.second.Y) < std::max(line2.first.Y, line2.second.Y);
        });

        std::vector<float> intersections;
        intersections.reserve(currentLines.size());
        for (int index: currentLines)
        {
            const auto& coef = coefficients[index];
            intersections.push_back(coef.first * floatY + coef.second);
        }

        std::sort(intersections.begin(), intersections.end());
        for (int i = 1; i < intersections.size(); i += 2)
        {
            SDL_RenderDrawLine(rendererSDL, intersections[i], floatY, intersections[i-1], floatY);
        }

    }

    SDL_SetRenderTarget(rendererSDL, nullptr);
}

SDL_Rect RenderablePolygon::GetRect() const
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

void RenderablePolygon::SetColor(const Color &color)
{
    m_shouldInit = true;
    m_color = color;
}

const Color &RenderablePolygon::GetColor() const
{
    return m_color;
}

void RenderablePolygon::SetPoints(const std::vector<Vector2D> &points)
{
    m_shouldInit = true;
    m_points = points;
}

const std::vector<Vector2D> &RenderablePolygon::GetPoints() const
{
    return m_points;
}

void RenderablePolygon::SetHeight(float height)
{
    m_shouldInit = true;
    m_height = height;
}

[[nodiscard]] float RenderablePolygon::GetHeight() const
{
    return m_height;
}

void RenderablePolygon::SetWidth(float width)
{
    m_shouldInit = true;
    m_width = width;
}

[[nodiscard]] float RenderablePolygon::GetWidth() const
{
    return m_width;
}
