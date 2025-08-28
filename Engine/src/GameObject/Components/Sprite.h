//
// Created by Максим Процик on 04.08.2023.
//

#ifndef GAMETEST_SPRITE_H
#define GAMETEST_SPRITE_H


#include <SDL_image.h>

#include "Serialization/ComponentFactory.h"
#include "GameObject/Components/Rendering/Renderable.h"

class Sprite: public Renderable
{
public:
    float Height = 0.2;
    float Width = 0.2;
    void SetImagePath(const std::string& imagePath);
    const std::string& GetImagePath() const;

protected:
    void InitTexture() override;
    SDL_Rect GetRect() const override;
private:
    std::string m_imagePath;
public:
    SERIALIZABLE(NAMED_PROPERTY(Sprite, m_imagePath, "ImagePath"),
                 PROPERTY(Sprite, Layer),
                 PROPERTY(Sprite, Width),
                 PROPERTY(Sprite, Height))
};


#endif //GAMETEST_SPRITE_H
