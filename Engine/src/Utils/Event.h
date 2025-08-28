//
// Created by Максим Процик on 20.08.2023.
//

#ifndef GAMETEST_EVENT_H
#define GAMETEST_EVENT_H

#include <vector>

template<class T>
class Event
{
public:
    Event<T>& operator+=(const T& callback);
    Event<T>& operator-=(const T& callback);

    template<class... Args>
    void Invoke(Args... args);
private:
    std::vector<T> m_callbacks;
};

template<class T>
Event<T> &Event<T>::operator+=(const T &callback)
{
    m_callbacks.push_back(callback);
    return *this;
}

template<class T>
Event<T> &Event<T>::operator-=(const T &callback)
{
    auto itr = std::find(m_callbacks.begin(), m_callbacks.end(), callback);
    if (itr != m_callbacks.end())
    {
        m_callbacks.erase(itr);
    }
    return *this;
}

template<class T>
template<class... Args>
void Event<T>::Invoke(Args... args)
{
    for (auto& callback: m_callbacks)
    {
        callback(args...);
    }
}

#endif //GAMETEST_EVENT_H
