#ifndef SERIALIZER_IMPL_HPP
#define SERIALIZER_IMPL_HPP

#include <iostream>

#include "serialiser.hpp"

namespace cppengine {

  template <typename ... Visitor>
  struct FieldSerialiser : Visitor... {
    using Visitor::operator()...;
  };

  template<typename T>
  void Serialiser::serialiseValue(T const &value) {
    if constexpr (IterableSerialisableType<T>) {
      serialiseArray(value);
    } else {
      serialiseObject(value);
    }
  }

  template <typename T>
  void Serialiser::serialiseValue(std::string_view name, T const &value) {
    if constexpr (IterableSerialisableType<T>) {
      serialiseArray(name, value);
    } else {
      serialiseObject(name, value);
    }
  }

  template <typename Visitor, typename ... T>
  void Serialiser::serialiseObjectFields(ArgumentList<T...>, Visitor &&v) {
    [[maybe_unused]] bool first = true;
    (([&] {
          if (!first)
            placeSeparator();
        first = false;
        v(T{});
    }()), ...);
  }

  template<typename T> requires IterableSerialisableType<T>
  void Serialiser::serialiseArray(std::string_view name, T const &array) {
    auto begin = std::begin(array);
    auto end = std::end(array);

    beginArray(name);
    for (auto i = begin; i != end; i = std::next(i)) {
      serialiseValue(*i);
      if (std::next(i) != end) {
        placeSeparator();
      }
    }
    endArray();
  }

  template<typename T> requires IterableSerialisableType<T>
  void Serialiser::serialiseArray(T const &array) {
    auto begin = std::begin(array);
    auto end = std::end(array);

    beginArray();
    for (auto i = begin; i != end; i = std::next(i)) {
      serialiseValue(*i);
      if (std::next(i) != end) {
        placeSeparator();
      }
    }
    endArray();
  }

  template<typename T>
  void Serialiser::serialiseObject(std::string_view name, T const &object) {
    beginObject(name);
    serialiseObjectFields(typename TypeMemberTraits<T>::members{}, [&](auto && value) {
        serialise(value.getName(), object.*value.getMember());
    });
    endObject();
  }

  template<typename T>
  void Serialiser::serialiseObject(T const &object) {
    beginObject();
    serialiseObjectFields(typename TypeMemberTraits<T>::members{}, [&](auto && value) {
        serialiseValue(value.getName(), object.*value.getMember());
    });
    endObject();
  }

  template<typename T>
  void Serialiser::serialise(T const &src) {

    if constexpr(NonTriviallySerialisableType<T> && !IterableSerialisableType<T> && !std::is_convertible_v<T, std::string_view>) {
      serialiseObject(src);
    } else if constexpr (IterableSerialisableType<T> && !std::is_convertible_v<T, std::string_view>) {
      serialiseArray(src);
    } else {
      serialiseValue(src);
    }


  }
}

#endif