#ifndef DRAW_CONTEXT_HPP
#define DRAW_CONTEXT_HPP
#include "model_handle.hpp"
#include "uniform.hpp"

namespace cppengine {
    struct Box2D;
    struct Triangle;
    class Vector3;
    class Matrix4x4;

    class DrawContext {
    private:

    public:
        virtual void begin() = 0;
        virtual void beginBatch(ObjectHandle<ShaderHandle> shader) = 0;
        virtual void endBatch(ObjectHandle<ShaderHandle> shader) = 0;
        virtual void renderTriangle(Triangle const &triangle, Matrix4x4 const &transform) = 0;
        virtual void renderBox2D(Box2D const &box2D, Matrix4x4 const &transform) = 0;

        virtual void render(ObjectHandle<ShaderHandle> shader, ObjectHandle<ModelHandle> model,
            std::unordered_map<std::string, Uniform> const &uniforms, std::unordered_map<std::string,
            ObjectHandle<TextureHandle>> const &textures, Matrix4x4 const &transform) = 0;

        virtual void flush() = 0;
        virtual ~DrawContext() = 0;
    };

    inline DrawContext::~DrawContext() = default;
}

#endif