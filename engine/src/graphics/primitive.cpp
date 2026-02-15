#include "engine.hpp"

namespace cppengine {
    std::size_t Primitive::getStride() const {
        return sizeof(vertex_value_type);
    }
}
