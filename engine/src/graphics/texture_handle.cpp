#include "engine.hpp"

namespace cppengine {
    std::uint64_t TextureHandle::getId() const {
        return id;
    }

    std::string const &TextureHandle::getName() const {
        return "";
    }

    std::uint64_t TextureHandle::getWidth() const {
        return 0;
    }

    std::uint64_t TextureHandle::getHeight() const {
        return 0;
    }
}
