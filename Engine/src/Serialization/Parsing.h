//
// Created by Максим Процик on 04.08.2023.
//

#ifndef GAMETEST_PARSING_H
#define GAMETEST_PARSING_H

#include <nlohmann/json.hpp>

#include <string>

#include "Utils/Templates.h"

template<typename Class, typename T>
struct PropertyImpl {
    constexpr PropertyImpl(T Class::*aMember, const char* aName) : member{aMember}, name{aName} {}

    using Type = T;

    T Class::*member;
    const char* name;
};

template<typename Class, typename T>
constexpr auto property(T Class::*member, const char* name) {
    return PropertyImpl<Class, T>{member, name};
}

template<class T>
void FromJson(T* obj, const nlohmann::json& data);

template<class T>
void FromJson(T* obj, const nlohmann::json& data)
{
    if constexpr(std::is_pointer_v<T>)
    {
        using ObjType = typename std::remove_reference<decltype(**obj)>::type;
        *obj = new ObjType;
        T dynamicPtr = *obj;
        FromJson(dynamicPtr, data);
    }
    else if constexpr (std::is_scalar_v<T> || std::is_same_v<T, std::string>)
    {
        *obj = data.get<T>();
        return;
    }
    else if constexpr (is_vector<T>::value)
    {
        using Type = typename T::value_type;
        for (const auto& item: data)
        {
            Type element;
            FromJson(&element, item);
            obj->push_back(element);
        }
        return;
    }
    else if constexpr(is_unordered_map<T>::value)
    {
        using Type = typename T::value_type;
        using KeyType = typename std::remove_const<decltype(Type().first)>::type;
        using ValueType = typename std::remove_const<decltype(Type().second)>::type;
        for (auto itr = data.begin(); itr != data.end(); itr++)
        {
            KeyType key;
            ValueType value;
            FromJson(&key, itr.key());
            FromJson(&value, itr.value());
            obj->operator[](key) = value;
        }
        return;
    }
    else
    {
        constexpr auto nbProperties = std::tuple_size<decltype(T::properties)>::value;

        for_sequence(std::make_index_sequence<nbProperties>{}, [&](auto i) {
            constexpr auto prop = std::get<i>(T::properties);
            if (!data.contains(prop.name))
            {
                return;
            }
            using Type = typename decltype(prop)::Type;

            auto propertyPtr = &(obj->*(prop.member));
            FromJson(propertyPtr, data[prop.name]);
        });
    }

}


#define PROPERTY(CLASS, MEMBER) property(&CLASS::MEMBER, #MEMBER)

#define NAMED_PROPERTY(CLASS, MEMBER, NAME) property(&CLASS::MEMBER, NAME)

#define SERIALIZABLE(...) constexpr static auto properties = std::make_tuple(__VA_ARGS__);


#endif //GAMETEST_PARSING_H
