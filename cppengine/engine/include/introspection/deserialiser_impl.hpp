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
        beginObject(name);

        using key_type = std::remove_cv_t<std::tuple_element_t<0, T>>;
        using value_type = std::tuple_element_t<1, T>;

        key_type pairKey = getFieldKey();
        value_type pairValue;

        deserialiseValue(pairKey, pairValue);

        std::get<0>(value) = pairKey;
        std::get<1>(value) = pairValue;

        endObject();
    }

    template<typename T> requires KeyValuePairType<T>
    void Deserialiser::deserialiseKeyValuePair(std::size_t i, T &value) {
        beginObject(i);

        using key_type = std::remove_cv_t<std::tuple_element_t<0, T>>;
        using value_type = std::tuple_element_t<1, T>;

        key_type pairKey = getFieldKey();
        value_type pairValue;

        deserialiseValue(pairKey, pairValue);

        std::get<0>(value) = pairKey;
        std::get<1>(value) = pairValue;

        endObject();
    }

    template<typename T> requires KeyValuePairType<T>
    void Deserialiser::deserialiseKeyValuePair(T &value) {
        beginObject();

        using key_type = std::remove_cv_t<std::tuple_element_t<0, T>>;
        using value_type = std::tuple_element_t<1, T>;

        key_type pairKey = getFieldKey();
        value_type pairValue;

        deserialiseValue(pairKey, pairValue);

        std::get<0>(value) = std::move(pairKey);
        std::get<1>(value) = std::move(pairValue);

        endObject();
    }

    template<typename T> requires IterableSerialisableType<T>
    void Deserialiser::deserialiseArray(std::string_view name, T &array) {
        const auto size = beginArray(name);

        if constexpr (BackInsertableType<T>) {
            using value_type = T::value_type;
            for (std::size_t i = 0; i < size; ++i) {
                value_type value;
                deserialiseValue(i, value);
                array.push_back(std::move(value));

                if (i + 1 < size) {
                    processSeparator();
                }
            }

        } else if constexpr (InsertableType<T>) {
            using value_type = T::value_type;
            for (std::size_t i = 0; i < size; ++i) {
                value_type value;
                deserialiseValue(i, value);
                array.insert(std::move(value));

                if (i + 1 < size) {
                    processSeparator();
                }
            }

        } else {
            auto curr = std::begin(array);
            auto end = std::end(array);

            for (std::size_t i = 0; i < size && curr != end; ++i, curr = std::next(curr)) {
                deserialiseValue(i, *curr);
                auto next = curr;
                next = std::next(next);
                if (i + 1 < size && next != end) {
                    processSeparator();
                }
            }
        }

        endArray();
    }

    template<typename T> requires IterableSerialisableType<T>
    void Deserialiser::deserialiseArray(std::size_t i, T &array) {
    }

    template<typename T>
    void Deserialiser::deserialiseObject(std::string_view name, T &object) {
    }

    template<typename T>
    void Deserialiser::deserialiseObject(std::size_t i, T &object) {
    }

    template<typename T>
    void Deserialiser::deserialiseObject(T &object) {
    }

    template<typename T>
    void Deserialiser::deserialiseValue(std::string_view name, T &value) {

    }

    template<typename T>
    void Deserialiser::deserialiseValue(std::size_t i, T &value) {
    }

    template<typename T>
    void Deserialiser::deserialiseValue(T &value) {
    }

    template<typename T> requires IterableSerialisableType<T>
    void Deserialiser::deserialiseArray(T &array) {
        const auto size = beginArray();

        if constexpr (BackInsertableType<T>) {
            using value_type = T::value_type;
            for (std::size_t i = 0; i < size; ++i) {
                value_type value;
                deserialiseValue(i, value);
                array.push_back(std::move(value));

                if (i + 1 < size) {
                    processSeparator();
                }
            }

        } else if constexpr (InsertableType<T>) {
            using value_type = T::value_type;
            for (std::size_t i = 0; i < size; ++i) {
                value_type value;
                deserialiseValue(i, value);
                array.insert(std::move(value));

                if (i + 1 < size) {
                    processSeparator();
                }
            }

        } else {
            auto curr = std::begin(array);
            auto end = std::end(array);

            for (std::size_t i = 0; i < size && curr != end; ++i, curr = std::next(curr)) {
                deserialiseValue(i, *curr);
                auto next = curr;
                next = std::next(next);
                if (i + 1 < size && next != end) {
                    processSeparator();
                }
            }
        }

        endArray();
    }

    template<typename T>
    void Deserialiser::deserialise(T &dest) {

    }
}

#endif //CPPGAME_DESERIALISER_IMPL_HPP
