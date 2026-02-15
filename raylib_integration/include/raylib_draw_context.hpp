#ifndef RAYLIB_DRAW_CONTEXT_HPP
#define RAYLIB_DRAW_CONTEXT_HPP
#include "integration/draw_context.hpp"

namespace cppengine {
    class RaylibDrawContext : public DrawContext {
    private:

    public:
        void renderTriangle(TrianglePrimitive const &triangle) override;
        ~RaylibDrawContext() override = default;
    };
}

#endif