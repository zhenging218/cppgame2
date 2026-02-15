#ifndef DRAW_CONTEXT_HPP
#define DRAW_CONTEXT_HPP

namespace cppengine {
    class TrianglePrimitive;

    class DrawContext {
    private:

    public:
        virtual void renderTriangle(TrianglePrimitive const &triangle) = 0;
        virtual ~DrawContext() = 0;
    };

    inline DrawContext::~DrawContext() = default;
}

#endif