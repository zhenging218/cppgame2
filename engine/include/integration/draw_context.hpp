#ifndef DRAW_CONTEXT_HPP
#define DRAW_CONTEXT_HPP

namespace cppengine {
    struct Triangle;
    class Matrix4x4;

    class DrawContext {
    private:

    public:
        virtual void renderTriangle(Triangle const &triangle, Matrix4x4 const &transform) = 0;
        virtual void flush() = 0;
        virtual ~DrawContext() = 0;
    };

    inline DrawContext::~DrawContext() = default;
}

#endif