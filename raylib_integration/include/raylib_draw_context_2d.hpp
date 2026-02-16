#ifndef RAYLIB_DRAW_CONTEXT_2D_HPP
#define RAYLIB_DRAW_CONTEXT_2D_HPP
#include "../../cmake-build-debug/_deps/raylib-src/src/raylib.h"
#include "integration/draw_context.hpp"

namespace cppengine {

    class RaylibDrawContext2D : public DrawContext {
    private:
        ::Camera2D camera;
    public:
        RaylibDrawContext2D(::Camera2D const &camera);
        void renderTriangle(Triangle const &triangle, Matrix4x4 const &transform) override;
        void flush() override;
        ~RaylibDrawContext2D() override = default;
    };
}

#endif