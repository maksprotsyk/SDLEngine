//
// Created by Максим Процик on 18.08.2023.
//

#ifndef GAMETEST_INPUT_H
#define GAMETEST_INPUT_H

#include "SDL2/SDL.h"

#include <unordered_map>

class Input
{
public:
    enum KeyCode
    {
        Up = 0,
        Down = 1,
        Left = 2,
        Right = 3,
        COUNT = 4
    };

    static Input* GetInstance();
    void KeyDown(SDL_KeyCode keyCode);
    void KeyUp(SDL_KeyCode keyCode);

    [[nodiscard]] bool KeyPressed(KeyCode keyCode) const;

private:
    static Input* m_input;

    std::unordered_map<KeyCode, bool> m_keyStates;

    static std::unordered_map<SDL_KeyCode, KeyCode> m_keysMapping;

    Input();
    void ChangeState(SDL_KeyCode keyCode, bool state);
};


#endif //GAMETEST_INPUT_H
