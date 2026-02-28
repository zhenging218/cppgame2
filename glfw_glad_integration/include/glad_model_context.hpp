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

        ModelID loadModel(const std::string &name, const Vector3 *vertices, const std::size_t *indices,
            std::size_t vertexCount, std::size_t indexCount) override;

        ObjectHandle<ModelHandle> getModel(ModelID id) const override;

        ~GladModelContext() override;
    };
}

#endif
