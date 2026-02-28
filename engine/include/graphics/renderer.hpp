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

        static ModelID getModel(std::string const &name);
        static ShaderID getShader(std::string const &name);

        static ModelID loadModel(std::string const &name, Vector3 const *vertices, std::size_t vertex_count, std::size_t const *indices, std::size_t index_count);
        static ShaderID loadShader(std::string const &name);
        static Texture loadTexture(std::string const &path);
    };
}

#endif