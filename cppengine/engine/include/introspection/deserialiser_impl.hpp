//
// Created by Admin on 7/11/2026.
//

#ifndef CPPGAME_DESERIALISER_IMPL_HPP
#define CPPGAME_DESERIALISER_IMPL_HPP

#include "introspection_traits.hpp"
#include "deserialiser.hpp"
#include "reflection/type_descriptor.hpp"

namespace cppengine {

    // todo: concepts to check if the array is dynamic or static

    template<typename Visitor, typename ... T>
    void Deserialiser::deserialiseObjectFields(ArgumentList<T...>, Visitor &&v) {

    }

    template<typename T> requires KeyValuePairType<T>
    void Deserialiser::deserialiseKeyValuePair(std::string_view name, T &value) {
    }

    template<typename T> requires KeyValuePairType<T>
    void Deserialiser::deserialiseKeyValuePair(T &value) {
    }

    template<typename T> requires IterableSerialisableType<T>
    void Deserialiser::deserialiseArray(std::string_view name, T &array) {
    }

    template<typename T>
    void Deserialiser::deserialiseObject(std::string_view name, T &object) {
    }

    template<typename T>
    void Deserialiser::deserialiseObject(T &object) {
    }

    template<typename T>
    void Deserialiser::deserialiseValue(std::string_view name, T &value) {
    }

    template<typename T>
    void Deserialiser::deserialiseValue(T &value) {
    }

    template<typename T> requires IterableSerialisableType<T>
    void Deserialiser::deserialiseArray(T &array) {

    }

    template<typename T>
    void Deserialiser::deserialise(T &dest) {

    }
}

#endif //CPPGAME_DESERIALISER_IMPL_HPP
