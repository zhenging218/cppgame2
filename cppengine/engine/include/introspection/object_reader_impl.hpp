#ifndef OBJECT_READER_IMPL_HPP
#define OBJECT_READER_IMPL_HPP

#include "object_reader.hpp"

namespace cppengine {
  template<typename T>
  void ObjectReader::inspect(T const &src, ObjectReader &r) {
    if constexpr (InspectorReadableType<T>) {
      beginObject();
      src.inspect(r);
      endObject();
    } else {
      // read leaf node
    }
  }
}

#endif