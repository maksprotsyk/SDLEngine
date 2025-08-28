//
// Created by Максим Процик on 18.08.2023.
//

#include "Input.h"

Input* Input::m_input = nullptr;

std::unordered_map<SDL_KeyCode, Input::KeyCode> Input::m_keysMapping = std::unordered_map<SDL_KeyCode, Input::KeyCode>
{
    {SDLK_UP, Up},
    {SDLK_DOWN, Down},
    {SDLK_LEFT, Left},
    {SDLK_RIGHT, Right}
};

Input* Input::GetInstance() {
    if (!m_input)
    {
        m_input = new Input();
    }
    return m_input;
}

Input::Input()
{
    for (int code = 0; code < KeyCode::COUNT; code++)
    {
        auto keyCode = (KeyCode)(code);
        m_keyStates[keyCode] = false;
    }
}
void Input::KeyDown(SDL_KeyCode keyCode)
{
    ChangeState(keyCode, true);
}
void Input::KeyUp(SDL_KeyCode keyCode)
{
    ChangeState(keyCode, false);
}

bool Input::KeyPressed(KeyCode keyCode) const
{
    return m_keyStates.find(keyCode)->second;
}

void Input::ChangeState(SDL_KeyCode keyCode, bool state)
{
    auto itr = m_keysMapping.find(keyCode);
    if (itr != m_keysMapping.end())
    {
        m_keyStates[itr->second] = state;
    }
}
