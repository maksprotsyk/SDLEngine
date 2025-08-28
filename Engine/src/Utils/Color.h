//
// Created by Максим Процик on 29.07.2023.
//

#ifndef GAMEENGINE_COLOR_H
#define GAMEENGINE_COLOR_H

#include <cstdlib>

#include "Serialization/Parsing.h"

class Color
{
public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    Color();

    SERIALIZABLE(NAMED_PROPERTY(Color, r, "R"),
                 NAMED_PROPERTY(Color, g, "G"),
                 NAMED_PROPERTY(Color, b, "B"),
                 NAMED_PROPERTY(Color, a, "A"))

};

#endif //GAMEENGINE_COLOR_H
