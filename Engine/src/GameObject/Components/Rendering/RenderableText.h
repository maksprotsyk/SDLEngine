//
// Created by Максим Процик on 06.08.2023.
//

#ifndef GAMETEST_RENDERABLETEXT_H
#define GAMETEST_RENDERABLETEXT_H

#include "Utils/Color.h"
#include "Serialization/ComponentFactory.h"

#include "Renderable.h"

class RenderableText: public Renderable
{
public:
    float Width = 0.2;
    float Height = 0.1;

    void SetText(const std::string& text);
    const std::string& GetText() const;
    void SetFontName(const std::string& fontName);
    const std::string& GetFontName() const;
    void SetFontColor(const Color& color);
    const Color& GetFontColor() const;
    void SetFontSize(int fontSize);
    int GetFontSize() const;

protected:
    void InitTexture() override;
    SDL_Rect GetRect() const override;
private:
    std::string m_text;
    std::string m_fontName;
    Color m_fontColor;
    int m_fontSize = 20;
public:
    SERIALIZABLE(NAMED_PROPERTY(RenderableText, m_text, "Text"),
                 NAMED_PROPERTY(RenderableText, m_fontColor, "FontColor"),
                 NAMED_PROPERTY(RenderableText, m_fontName, "FontName"),
                 NAMED_PROPERTY(RenderableText, m_fontSize, "FontSize"),
                 PROPERTY(RenderableText, Width),
                 PROPERTY(RenderableText, Height),
                 PROPERTY(RenderableText, Layer))

};


#endif //GAMETEST_RENDERABLETEXT_H
