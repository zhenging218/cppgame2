#ifndef MODEL_CONTEXT_HPP
#define MODEL_CONTEXT_HPP

#include "memory/object_handle.hpp"
#include "enum_model_id.hpp"
#include "model_handle.hpp"
#include <string>

namespace cppengine {

    class Vector3;

    class ModelContext {
    private:

    public:
        virtual ModelID loadModel(std::string const &name, Vector3 const *vertices, std::size_t const * indices, std::size_t vertexCount, std::size_t indexCount) = 0;
        virtual ObjectHandle<ModelHandle> getModel(ModelID id) const = 0;

        virtual ~ModelContext() = 0;
    };
    inline ModelContext::~ModelContext() = default;
}

#endif