#include "engine.hpp"

namespace cppengine {
    std::uint64_t Texture::getId() const {
        return id;
    }

    std::string const &Texture::getName() const {
        return "";
    }

    std::uint64_t Texture::getWidth() const {
        return 0;
    }

    std::uint64_t Texture::getHeight() const {
        return 0;
    }
}
