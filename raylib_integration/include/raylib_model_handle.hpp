#ifndef RAYLIB_MODEL_HANDLE_HPP
#define RAYLIB_MODEL_HANDLE_HPP
#include "raylib.h"
#include "graphics/model_handle.hpp"

namespace cppengine {
    class RaylibModelHandle : public ModelHandle {
    private:

    public:
        ::Mesh const &getMesh() const;
    };
}

#endif
