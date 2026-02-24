#ifndef GLAD_DRAW_CONTEXT_HPP
#define GLAD_DRAW_CCONTEXT_HPP
#include <unordered_map>

#include "graphics/draw_context.hpp"
#include "graphics/shader_handle.hpp"
#include "graphics/texture_handle.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {
    struct Rectangle2D;

    class GladDrawContext : public DrawContext {
    private:

    public:
        GladDrawContext(Rectangle2D const &viewport, Matrix4x4 const &vpMatrix);
        GladDrawContext(GladDrawContext const &) = delete;
        GladDrawContext &operator=(GladDrawContext const &) = delete;

        void begin() override;

        void beginBatch(ObjectHandle<ShaderHandle> shader) override;
        void endBatch(ObjectHandle<ShaderHandle> shader) override;


        void render(ObjectHandle<ShaderHandle> shader, ObjectHandle<ModelHandle> model,
            std::unordered_map<std::string, Uniform> const &uniforms, std::unordered_map<std::string,
            ObjectHandle<TextureHandle>> const &textures, Matrix4x4 const &transform) override;

        void flush() override;

        inline ~GladDrawContext() override;
    };
}

#endif
