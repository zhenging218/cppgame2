#ifndef GLAD_TEXTURE_HANDLE_HPP
#define GLAD_TEXTURE_HANDLE_HPP
#include "graphics/texture_handle.hpp"

namespace cppengine {
    class GladTextureHandle : public TextureHandle {
    private:
        std::size_t textureId;
    public:
        std::size_t getId() const;
        inline ~GladTextureHandle() override = default;
    };
}

#endif
