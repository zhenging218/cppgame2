#ifndef RAYLIB_MODEL_CONTEXT_HPP
#define RAYLIB_MODEL_CONTEXT_HPP
#include <cstdint>

#include "graphics/model_context.hpp"

namespace cppengine {
    class RaylibModelContext : public ModelContext {
    private:
        std::unordered_map<ModelID, ObjectHandle<ModelHandle>> models;

    public:
        RaylibModelContext();

        ModelID loadModel(std::string const &name,
            Vector3 const *vertices, std::size_t const * indices,
            std::size_t vertexCount, std::size_t indexCount) override;

        ObjectHandle<ModelHandle> getModel(ModelID id) const override;
    };
}

#endif
