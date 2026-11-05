#ifndef MODEL_HANDLE_HPP
#define MODEL_HANDLE_HPP
#include "enum_model_id.hpp"

namespace cppengine {
    class ModelHandle {
    private:

    public:
        [[nodiscard]] virtual ModelID getId() const = 0;
        virtual void bindModel() = 0;
        virtual void unbindModel() = 0;
        virtual ~ModelHandle() = 0;
    };

    inline ModelHandle::~ModelHandle() = default;
}

#endif