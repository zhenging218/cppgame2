#ifndef GLAD_TEXURE_CONTEXT_HPP
#define GLAD_TEXTURE_CONTEXT_HPP
#include "graphics/texture_context.hpp"

namespace cppengine {
    class GladTextureContext : public TextureContext {
    private:

    public:
        inline ~GladTextureContext() override = default;
    };
}

#endif
