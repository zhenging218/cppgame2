#ifndef RAYLIB_DRAW_CONTEXT_2D_HPP
#define RAYLIB_DRAW_CONTEXT_2D_HPP
#include <functional>

#include "../../cmake-build-debug/_deps/raylib-src/src/raylib.h"
#include "integration/draw_context.hpp"

namespace cppengine {

    class RaylibDrawContext2D : public DrawContext {
    private:
        std::vector<std::function<void()>> commands;
        Rectangle2D viewport;
        ::Camera2D camera;
    public:
        RaylibDrawContext2D(Rectangle2D const &viewport_, Transform const &transform);
        void begin() override;
        void renderTriangle(Triangle const &triangle, Matrix4x4 const &transform) override;
        void flush() override;
        ~RaylibDrawContext2D() override = default;
    };
}

#endif