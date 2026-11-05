#ifndef GLAD_MODEL_CONTEXT_HPP
#define GLAD_MODEL_CONTEXT_HPP
#include <unordered_map>

#include "graphics/model_context.hpp"

namespace cppengine {
    class GladModelContext : public ModelContext {
    private:
        std::unordered_map<std::string, ObjectHandle<ModelHandle>, HashHelper::StringHash, std::equal_to<>> models;

    public:
        GladModelContext();
        GladModelContext(GladModelContext const &) = delete;
        GladModelContext &operator=(GladModelContext const &) = delete;

        ModelID loadModel(std::string_view, const Vector3 *vertices, const std::uint32_t *indices,
            std::uint32_t vertexCount, std::uint32_t indexCount) override;

        ObjectHandle<ModelHandle> getModel(std::string_view id) const override;

        ~GladModelContext() override;
    };
}

#endif
