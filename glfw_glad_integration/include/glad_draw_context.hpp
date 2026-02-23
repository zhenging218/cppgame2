#ifndef GLAD_DRAW_CONTEXT_HPP
#define GLAD_DRAW_CCONTEXT_HPP
#include <unordered_map>

#include "graphics/draw_context.hpp"
#include "graphics/shader_handle.hpp"
#include "graphics/texture_handle.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {
    class GladDrawContext : public DrawContext {
    private:

    public:
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
