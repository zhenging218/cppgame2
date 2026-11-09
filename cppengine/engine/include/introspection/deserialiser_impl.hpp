//
// Created by Admin on 7/11/2026.
//

#ifndef CPPGAME_DESERIALISER_IMPL_HPP
#define CPPGAME_DESERIALISER_IMPL_HPP

#include "introspection_traits.hpp"
#include "deserialiser.hpp"
#include "reflection/type_descriptor.hpp"

namespace cppengine {
    template<typename T> requires StringKeyConvertibleType<T>
    T Deserialiser::convertFieldKey(std::string_view key) {
        using result_type = std::remove_cv_t<T>;

        if constexpr(std::same_as<result_type, std::string>) {
            return std::string(key);
        } else if constexpr(std::same_as<result_type, bool>) {
            return convertBooleanValue(key);
        } else {
            result_type value{};

            auto first = key.data();
            auto last = key.data() + key.size();

            auto [ptr, ec] = std::from_chars(first, last, value);

            if (ec != std::errc{} || ptr != last) {
                throw std::runtime_error(std::format("unable to parse key value from {} to type {} due to {}",
                    key, TypeDescriptor::getTypeDescriptor<T>()->getName(), std::make_error_code(ec).message()));
            }

            return value;

        }
    }

    template<typename Visitor, typename ... T>
    void Deserialiser::deserialiseObjectFields(ArgumentList<T...>, Visitor &&v) {
        [[maybe_unused]] bool first = true;
        (([&] {
              if (!first)
                  processSeparator();
              first = false;
              v(T{});
          }()), ...);
    }

    template<typename T> requires KeyValuePairType<T>
    void Deserialiser::deserialiseKeyValuePair(std::string_view name, T &value) {
        beginObject(name);

        using key_type = std::remove_cv_t<std::tuple_element_t<0, T>>;
        using value_type = std::remove_cv_t<std::tuple_element_t<1, T>>;

        auto fieldKey = getFieldKey();
        value_type pairValue{};

        deserialiseValue(fieldKey, pairValue);

        endObject();

        if constexpr (std::same_as<key_type, std::string>) {
            std::get<0>(value) = std::move(fieldKey);
        } else {
            key_type pairKey = convertFieldKey<key_type>(fieldKey);
            std::get<0>(value) = std::move(pairKey);
        }

        std::get<1>(value) = std::move(pairValue);
    }

    template<typename T> requires KeyValuePairType<T>
    void Deserialiser::deserialiseKeyValuePair(std::size_t at, T &value) {
        beginObject(at);

        using key_type = std::remove_cv_t<std::tuple_element_t<0, T>>;
        using value_type = std::remove_cv_t<std::tuple_element_t<1, T>>;

        auto fieldKey = getFieldKey();
        value_type pairValue{};

        deserialiseValue(fieldKey, pairValue);

        endObject();

        if constexpr (std::same_as<key_type, std::string>) {
            std::get<0>(value) = std::move(fieldKey);
        } else {
            key_type pairKey = convertFieldKey<key_type>(fieldKey);
            std::get<0>(value) = std::move(pairKey);
        }

        std::get<1>(value) = std::move(pairValue);
    }

    template<typename T> requires KeyValuePairType<T>
    void Deserialiser::deserialiseKeyValuePair(T &value) {
        beginObject();

        using key_type = std::remove_cv_t<std::tuple_element_t<0, T>>;
        using value_type = std::remove_cv_t<std::tuple_element_t<1, T>>;

        auto fieldKey = getFieldKey();
        value_type pairValue{};

        deserialiseValue(fieldKey, pairValue);

        endObject();

        if constexpr (std::same_as<key_type, std::string>) {
            std::get<0>(value) = std::move(fieldKey);
        } else {
            key_type pairKey = convertFieldKey<key_type>(fieldKey);
            std::get<0>(value) = std::move(pairKey);
        }

        std::get<1>(value) = std::move(pairValue);
    }

    template<typename T, typename S> requires IterableSerialisableType<T>
    void Deserialiser::deserialiseArrayElements(T &array, S size) {
        if constexpr (ResettableIterableType<T>) {
            array.clear();
        }

        if constexpr (BackInsertableType<T>) {
            using value_type = WritableElementType<T>::type;

            for (std::size_t i = 0; i < size; ++i) {
                value_type value{};
                deserialiseValue(i, value);
                array.push_back(std::move(value));

                if (i + 1 < size) {
                    processSeparator();
                }
            }

        } else if constexpr (InsertableType<T>) {
            using value_type = WritableElementType<T>::type;

            for (std::size_t i = 0; i < size; ++i) {
                value_type value{};
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
    }

    template<typename T> requires IterableSerialisableType<T>
    void Deserialiser::deserialiseArray(std::string_view name, T &array) {
        const auto size = beginArray(name);
        deserialiseArrayElements(array, size);
        endArray();
    }

    template<typename T> requires IterableSerialisableType<T>
    void Deserialiser::deserialiseArray(std::size_t at, T &array) {
        const auto size = beginArray(at);
        deserialiseArrayElements(array, size);
        endArray();
    }

    template<typename T> requires IterableSerialisableType<T>
    void Deserialiser::deserialiseArray(T &array) {
        const auto size = beginArray();
        deserialiseArrayElements(array, size);
        endArray();
    }

    template<typename T>
    void Deserialiser::deserialiseObject(std::string_view name, T &object) {
        beginObject(name);
        deserialiseObjectFields(typename TypeMemberTraits<T>::members{}, [&](auto && descriptor) {
            using descriptor_type = std::remove_cvref_t<decltype(descriptor)>;

            if constexpr (descriptor_type::hasMember) {
                deserialiseValue(descriptor.getName(), descriptor.get(object));
            } else {
                using value_type = typename descriptor_type::field_type;
                value_type value = descriptor.get(object);
                deserialiseValue(descriptor.getName(), value);
                descriptor.set(object, std::move(value));
            }
        });

        endObject();
    }

    template<typename T>
    void Deserialiser::deserialiseObject(std::size_t at, T &object) {
        beginObject(at);
        deserialiseObjectFields(typename TypeMemberTraits<T>::members{}, [&](auto && descriptor) {
            using descriptor_type = std::remove_cvref_t<decltype(descriptor)>;

            if constexpr (descriptor_type::hasMember) {
                deserialiseValue(descriptor.getName(), descriptor.get(object));
            } else {
                using value_type = typename descriptor_type::field_type;
                value_type value = descriptor.get(object);
                deserialiseValue(descriptor.getName(), value);
                descriptor.set(object, value);
            }
        });

        endObject();
    }

    template<typename T>
    void Deserialiser::deserialiseObject(T &object) {
        beginObject();
        deserialiseObjectFields(typename TypeMemberTraits<T>::members{}, [&](auto && descriptor) {
            using descriptor_type = std::remove_cvref_t<decltype(descriptor)>;

            if constexpr (descriptor_type::hasMember) {
                deserialiseValue(descriptor.getName(), descriptor.get(object));
            } else {
                using value_type = typename descriptor_type::field_type;
                value_type value = descriptor.get(object);
                deserialiseValue(descriptor.getName(), value);
                descriptor.set(object, value);
            }
        });

        endObject();
    }

    template<typename T> requires DeserialisableType<T>
    void Deserialiser::deserialiseValue(std::string_view name, T &value) {
        if constexpr (std::same_as<T, std::string> || TriviallyIntrospectableType<T>) {
            deserialiseValue(name, value);
        }  else if constexpr (IterableSerialisableType<T>) {
            deserialiseArray(name, value);
        } else if constexpr (NonTriviallyIntrospectableType<T>) {
            deserialiseObject(name, value);
        } else if constexpr (KeyValuePairType<T>) {
            deserialiseKeyValuePair(name, value);
        }
    }

    template<typename T> requires DeserialisableType<T>
    void Deserialiser::deserialiseValue(std::size_t at, T &value) {
        if constexpr (std::same_as<T, std::string> || TriviallyIntrospectableType<T>) {
            deserialiseValue(at, value);
        }  else if constexpr (IterableSerialisableType<T>) {
            deserialiseArray(at, value);
        } else if constexpr (NonTriviallyIntrospectableType<T>) {
            deserialiseObject(at, value);
        } else if constexpr (KeyValuePairType<T>) {
            deserialiseKeyValuePair(at, value);
        }
    }

    template<typename T> requires DeserialisableType<T>
    void Deserialiser::deserialiseValue(T &value) {
        if constexpr (std::same_as<T, std::string> || TriviallyIntrospectableType<T>) {
            deserialiseValue(value);
        }  else if constexpr (IterableSerialisableType<T>) {
            deserialiseArray(value);
        } else if constexpr (NonTriviallyIntrospectableType<T>) {
            deserialiseObject(value);
        } else if constexpr (KeyValuePairType<T>) {
            deserialiseKeyValuePair(value);
        }
    }

    template<typename T>
    void Deserialiser::deserialise(T &dest) {
        deserialiseValue(dest);
    }
}

#endif //CPPGAME_DESERIALISER_IMPL_HPP
