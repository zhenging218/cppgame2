#ifndef DRAW_CONTEXT_HPP
#define DRAW_CONTEXT_HPP

namespace cppengine {
    struct Box2D;
    struct Triangle;
    class Matrix4x4;

    class DrawContext {
    private:

    public:
        virtual void begin() = 0;
        virtual void renderTriangle(Triangle const &triangle, Matrix4x4 const &transform) = 0;
        virtual void renderBox2D(Box2D const &box2D, Matrix4x4 const &transform) = 0;
        virtual void flush() = 0;
        virtual ~DrawContext() = 0;
    };

    inline DrawContext::~DrawContext() = default;
}

#endif