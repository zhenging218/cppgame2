#ifndef GLAD_MODEL_HANDLE_HPP
#define GLAD_MODEL_HANDLE_HPP
#include <string>

#include "graphics/model_handle.hpp"

namespace cppengine {
    class GladModelHandle : public ModelHandle {
    private:
        std::string name;
        int vao, vbo, ebo;

    public:
        ~GladModelHandle() override;
    };
}

#endif
