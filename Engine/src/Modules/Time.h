//
// Created by Максим Процик on 06.08.2023.
//

#ifndef GAMETEST_TIME_H
#define GAMETEST_TIME_H

class Time
{
public:
    float TimeDelta = 0.0f;
    float TotalTime = 0.0f;
    static Time* GetInstance();
    void Init();
    void OnUpdate();

private:
    static Time* m_time;
    uint32_t m_startTime;
    uint32_t m_currentTime;
    Time() = default;
};


#endif //GAMETEST_TIME_H
