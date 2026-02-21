#ifndef RAYLIB_TEXTURE_HANDLE_HPP
#define RAYLIB_TEXTURE_HANDLE_HPP

#include "raylib.h"
#include "graphics/texture_handle.hpp"

namespace cppengine {
    class RaylibTextureHandle : public TextureHandle {
    private:

    public:
        ::Texture2D const &getTexture() const;
    };
}

#endif
