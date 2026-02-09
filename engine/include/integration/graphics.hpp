#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include "memory/object_handle.hpp"

namespace cppengine {
    class GraphicsContext;

    class Graphics {
    private:
        static ObjectHandle<GraphicsContext> createContext();
        ObjectHandle<GraphicsContext> context;
    public:
        Graphics();
        Graphics(Graphics const &) = delete;
        Graphics(Graphics &&) = delete;
        Graphics &operator=(Graphics const &) = delete;
        Graphics &operator=(Graphics &&) = delete;

        void initialise();
        void shutdown();

        void beginDraw();
        void draw();
        void endDraw();

        static Graphics &getInstance();
    };
}

#endif