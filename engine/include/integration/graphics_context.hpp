#ifndef GRAPHICS_CONTEXT_HPP
#define GRAPHICS_CONTEXT_HPP

namespace cppengine {
    class GraphicsContext {
    private:

    public:
        virtual void BeginDraw() = 0;
        virtual void draw() = 0;
        virtual void EndDraw() = 0;
        virtual ~GraphicsContext() = default;
    };
}

#endif