#ifndef GLAD_MODEL_CONTEXT_HPP
#define GLAD_MODEL_CONTEXT_HPP
#include <unordered_map>

#include "graphics/model_context.hpp"

namespace cppengine {
    class GladModelContext : public ModelContext {
    private:
        std::unordered_map<ModelID, ObjectHandle<GladModelHandle>> models;

    public:
        GladModelContext();
        GladModelContext(GladModelContext const &) = delete;
        GladModelContext &operator=(GladModelContext const &) = delete;

        ModelID loadModel(const std::string &name, const Vector3 *vertices, const std::uint32_t *indices,
            std::uint32_t vertexCount, std::uint32_t indexCount) override;

        ModelID getModel(std::string const &name) const override;
        ObjectHandle<ModelHandle> getModel(ModelID id) const override;

        ~GladModelContext() override;
    };
}

#endif
