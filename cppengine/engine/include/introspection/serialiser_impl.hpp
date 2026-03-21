#ifndef SERIALIZER_IMPL_HPP
#define SERIALIZER_IMPL_HPP

#include <string>

#include "serialiser.hpp"

namespace cppengine {
  template <typename T>
  concept isTriviallySerialisable = requires {
    TypeTraits<T>::pod_type_v;
    std::is_same_v<T, std::string>;
  };

  template<typename T>
  void Serialiser::serialise(std::string_view name, T const &object) {
    beginObject(name);
    serialise(object);
    endObject();
  }

  template<typename T>
  void Serialiser::serialise(T const &src) {

    if constexpr(isTriviallySerialisable<T>) {
      serialise(TypeTraits<T>::getName(), src);
    } else {
      serialiseObject(typename TypeMemberTraits<T>::members{}, [&](auto && value) {
        serialise(value.getName(), src.*value.getMember());
      });
    }


  }
}

#endif