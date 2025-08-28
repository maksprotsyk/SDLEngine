//
// Created by Максим Процик on 07.08.2023.
//

#include "Color.h"

Color::Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a): r(_r), g(_g), b(_b), a(_a)
{

}

Color::Color(): Color(0, 0, 0, 255)
{

}