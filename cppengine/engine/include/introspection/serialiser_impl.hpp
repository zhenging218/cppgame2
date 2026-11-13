#ifndef SERIALIZER_IMPL_HPP
#define SERIALIZER_IMPL_HPP

#include <format>

#include "introspection_traits.hpp"
#include "serialiser.hpp"

namespace cppengine {
  template<typename T> requires KeyStringConvertibleType<T>
  std::string Serialiser::convertKey(T const &key) {
    if constexpr (std::same_as<std::remove_cv_t<T>, std::string>) {
      return key;
    } else if constexpr (std::convertible_to<decltype(key), std::string_view>) {
      return std::string(key);
    } else {
      return std::to_string(key);
    }
  }
  template<typename T> requires VariantSerialisableType<T>
  void Serialiser::serialiseVariant(std::string_view name, T const &value) {
  }

  template<typename T> requires VariantSerialisableType<T>
  void Serialiser::serialiseVariant(T const &value) {
    using variants = VariantTraits<T>::variants;


  }

  template <typename T> requires (KeyValuePairType<T>)
  void Serialiser::serialiseKeyValuePair(std::string_view name, T const &value) {
    beginObject(name);
    serialiseValue(convertKey(std::get<0>(value)), std::get<1>(value));
    endObject();
  }

  template <typename T> requires (KeyValuePairType<T>)
  void Serialiser::serialiseKeyValuePair(T const &value) {
    beginObject();
    serialiseValue(convertKey(std::get<0>(value)), std::get<1>(value));
    endObject();
  }

  template<typename T> requires SerialisableType<T>
  void Serialiser::serialiseValue(T const &value) {
    if constexpr(std::is_convertible_v<T, std::string_view>) {
      serialiseValue(std::string_view{value});
    } else if constexpr (TriviallyIntrospectableType<T>) {
      serialiseValue(value);
    } else if constexpr (IterableSerialisableType<T>) {
      serialiseArray(value);
    } else if constexpr (NonTriviallyIntrospectableType<T>) {
      serialiseObject(value);
    } else if constexpr (KeyValuePairType<T>) {
      serialiseKeyValuePair(value);
    }
  }

  template <typename T> requires SerialisableType<T>
  void Serialiser::serialiseValue(std::string_view name, T const &value) {
    if constexpr(std::is_convertible_v<T, std::string_view>) {
      serialiseValue(name, std::string_view{value});
    } else if constexpr (TriviallyIntrospectableType<T>) {
      serialiseValue(name, value);
    } else if constexpr (IterableSerialisableType<T>) {
      serialiseArray(name, value);
    } else if constexpr (NonTriviallyIntrospectableType<T>) {
      serialiseObject(name, value);
    } else if constexpr (KeyValuePairType<T>) {
      serialiseKeyValuePair(name, value);
    }
  }

  template <typename Visitor, typename ... T>
  void Serialiser::serialiseObjectFields(ArgumentList<T...>, Visitor &&v) {
    [[maybe_unused]] bool first = true;
    (([&] {
          if (!first)
            processSeparator();
        first = false;
        v(T{});
    }()), ...);
  }

  template<typename T>
  void Serialiser::serialiseArrayElements(T const &array) {
    auto begin = std::begin(array);
    auto end = std::end(array);
    for (auto i = begin; i != end; i = std::next(i)) {
      serialiseValue(*i);
      if (std::next(i) != end) {
        processSeparator();
      }
    }
  }

  template<typename T> requires IterableSerialisableType<T>
  void Serialiser::serialiseArray(std::string_view name, T const &array) {
    beginArray(name);
    serialiseArrayElements(array);
    endArray();
  }

  template<typename T> requires IterableSerialisableType<T>
  void Serialiser::serialiseArray(T const &array) {
    beginArray();
    serialiseArrayElements(array);
    endArray();
  }

  template<typename T>
  void Serialiser::serialiseObject(std::string_view name, T const &object) {
    beginObject(name);
    serialiseObjectFields(typename TypeMemberTraits<T>::members{}, [&](auto && value) {
        serialiseValue(value.getName(), value.get(object));
    });
    endObject();
  }

  template<typename T>
  void Serialiser::serialiseObject(T const &object) {
    beginObject();
    serialiseObjectFields(typename TypeMemberTraits<T>::members{}, [&](auto && value) {
        serialiseValue(value.getName(), value.get(object));
    });
    endObject();
  }

  template<typename T>
  void Serialiser::serialise(T const &src) {
    serialiseValue(src);
  }
}

#endif