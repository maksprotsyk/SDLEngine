//
// Created by Максим Процик on 06.08.2023.
//

#include <algorithm>
#include "SDL2/SDL.h"
#include "Time.h"


Time* Time::m_time = nullptr;

Time *Time::GetInstance()
{
    if (!m_time)
    {
        m_time = new Time;
    }
    return m_time;
}
#include "iostream"
void Time::OnUpdate()
{
    uint32_t newTime = SDL_GetTicks();
    uint32_t ticksPassed = newTime - m_currentTime;

    SDL_Delay(16u - std::min(ticksPassed, 16u));

    newTime = SDL_GetTicks();
    auto millisecondsPassed = (float) (newTime - m_currentTime);
    TimeDelta = millisecondsPassed / 1000.0f;
    auto totalMillisecondsPassed = (float) (newTime - m_startTime);
    TotalTime = totalMillisecondsPassed / 1000.0f;
    m_currentTime = newTime;
}

void Time::Init()
{
    m_startTime = SDL_GetTicks();
    m_currentTime = m_startTime;
}
