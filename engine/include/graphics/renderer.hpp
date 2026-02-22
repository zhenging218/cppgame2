#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "memory/object_handle.hpp"

namespace cppengine {
    class RendererContext;

    class Renderer {
    private:
        static ObjectHandle<RendererContext> createContext();
        ObjectHandle<RendererContext> context;
    public:
        Renderer();
        Renderer(Renderer const &) = delete;
        Renderer(Renderer &&) = delete;
        Renderer &operator=(Renderer const &) = delete;
        Renderer &operator=(Renderer &&) = delete;

        void initialise();
        void shutdown();

        void draw();

        static Renderer &getInstance();

        static ShaderID loadShader(std::string const &name, char const *vertexShaderPath, char const *fragmentShaderPath);
        static Texture loadTexture(std::string const &path);
    };
}

#endif