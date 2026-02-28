#include "engine.hpp"
#include "gg_integration.hpp"

namespace {
    using namespace cppengine;

    template<typename... Setter>
    struct UniformSetters : Setter... {
        using Setter::operator()...;
    };


    template<typename U, typename S>
    auto getUniformVisitor(U && uniformName, S && shader) {
        return UniformSetters {
            [&uniformName, &shader](std::int32_t v)     { shader->setUniform(uniformName, v); },
            [&uniformName, &shader](std::uint32_t v)    { shader->setUniform(uniformName, v); },
            [&uniformName, &shader](float v)            { shader->setUniform(uniformName, v); },
            [&uniformName, &shader](Colour const &v)    { shader->setUniform(uniformName, v); },
            [&uniformName, &shader](Vector2 const &v)   { shader->setUniform(uniformName, v); },
            [&uniformName, &shader](Vector3 const &v)   { shader->setUniform(uniformName, v); },
            [&uniformName, &shader](Vector4 const &v)   { shader->setUniform(uniformName, v); },
            [&uniformName, &shader](Matrix2x2 const &v) { shader->setUniform(uniformName, v); },
            [&uniformName, &shader](Matrix3x3 const &v) { shader->setUniform(uniformName, v); },
            [&uniformName, &shader](Matrix4x4 const &v) { shader->setUniform(uniformName, v); }
        };
    }
}

namespace cppengine {
    GladDrawContext::GladDrawContext(Rectangle2D const &viewport_, Matrix4x4 const &vpMatrix_)
        : viewport(viewport_), vpMatrix(vpMatrix_) {
    }

    GladDrawContext::~GladDrawContext() = default;

    void GladDrawContext::begin() {
        glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
    }

    void GladDrawContext::bindShader(ObjectHandle<ShaderHandle> shader) {
        commands.emplace_back([shader] { shader->bindShader(); });
    }

    void GladDrawContext::bindModel(ObjectHandle<ModelHandle> model) {
        commands.emplace_back([model] { model->bindModel(); });
    }

    void GladDrawContext::render(ObjectHandle<ShaderHandle> shader, ObjectHandle<ModelHandle> model,
            std::unordered_map<std::string, Uniform> const &uniforms, std::unordered_map<std::string,
            ObjectHandle<TextureHandle>> const &textures, Matrix4x4 const &transform) {
        commands.emplace_back([this, shader, model, uniforms, textures, transform] {
            std::ranges::for_each(uniforms, [shader](auto const &uniform) {
                auto const &uniformName = uniform.first;
                auto const &uniformValue = uniform.second;

                std::visit(getUniformVisitor(uniformName, shader), uniformValue);
            });

            auto mvp = vpMatrix * transform;
            shader->setUniform(SHADER_MVP_MATRIX_UNIFORM, mvp);

            glDrawElements(GL_TRIANGLES, static_handle_cast<GladModelHandle>(model)->getElementCount(), GL_UNSIGNED_INT, 0);
        });
    }

    void GladDrawContext::unbindModel(ObjectHandle<ModelHandle> model) {
        commands.emplace_back([model] { model->unbindModel(); });
    }

    void GladDrawContext::unbindShader(ObjectHandle<ShaderHandle> shader) {
        commands.emplace_back([shader] { shader->unbindShader(); });
    }

    void GladDrawContext::flush() {
        std::ranges::for_each(commands, [](auto const &command) { command(); });
        commands.clear();
    }
}
