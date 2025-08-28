//
// Created by Максим Процик on 15.08.2023.
//

#ifndef GAMETEST_CLONING_H
#define GAMETEST_CLONING_H

#include "Parsing.h"

template<class T>
void Clone(T* to, T* from);

template<class T>
void Clone(T* to, T* from)
{
    if constexpr(std::is_pointer_v<T>)
    {
        using ObjType = typename std::remove_reference<decltype(**from)>::type;
        *to = new ObjType;
        FromJson(*to, *from);
    }
    else if constexpr (std::is_scalar_v<T> || std::is_same_v<T, std::string>)
    {
        *to = *from;
    }
    else if constexpr (is_vector<T>::value)
    {
        using Type = typename T::value_type;
        for (auto& item: *from)
        {
            Type element;
            Clone(&element, &item);
            to->push_back(element);
        }
        return;
    }
    else
    {
        constexpr auto nbProperties = std::tuple_size<decltype(T::properties)>::value;

        for_sequence(std::make_index_sequence<nbProperties>{}, [&](auto i) {
            constexpr auto prop = std::get<i>(T::properties);
            using Type = typename decltype(prop)::Type;

            auto fromPtr = &(from->*(prop.member));
            auto toPtr = &(to->*(prop.member));
            Clone(toPtr, fromPtr);
        });
    }

}

#endif //GAMETEST_CLONING_H
