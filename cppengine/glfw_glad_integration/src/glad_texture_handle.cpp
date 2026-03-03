#include "engine.hpp"
#include "gg_integration.hpp"

namespace cppengine {
    std::size_t GladTextureHandle::getId() const {
        return textureId;
    }
}
