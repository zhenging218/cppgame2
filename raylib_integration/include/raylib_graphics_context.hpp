#ifndef RAYLIB_GRAPHICS_CONTEXT_HPP
#define RAYLIB_GRAPHICS_CONTEXT_HPP

#include "integration/graphics_context.hpp"

namespace cppengine {
    class RaylibGraphicsContext : public GraphicsContext {
    private:

    public:
        void BeginDraw() override;

        void draw() override;

        void EndDraw() override;

        ~RaylibGraphicsContext() override = default;
    };
}

#endif