#ifndef GLAD_TEXTURE_HANDLE_HPP
#define GLAD_TEXTURE_HANDLE_HPP
#include "graphics/texture_handle.hpp"

namespace cppengine {
    class GladTextureHandle : public TextureHandle {
    private:

    public:
        inline ~GladTextureHandle() override = default;
    };
}

#endif
