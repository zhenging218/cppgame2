#ifndef RAYLIB_MODEL_HANDLE_HPP
#define RAYLIB_MODEL_HANDLE_HPP
#include "raylib.h"
#include "graphics/model_handle.hpp"

namespace cppengine {
    class RaylibModelHandle : public ModelHandle {
    private:

        std::string name;
        ::Mesh mesh;

    public:
        RaylibModelHandle(std::string const &name_, ::Mesh const &mesh_);
        RaylibModelHandle(std::string &&name_, ::Mesh const &mesh_);

        RaylibModelHandle(RaylibModelHandle const &) = delete;
        RaylibModelHandle &operator=(RaylibModelHandle const &) = delete;

        RaylibModelHandle(RaylibModelHandle &&other) noexcept;
        RaylibModelHandle &operator=(RaylibModelHandle &&other) noexcept;

        std::string const &getName() const override;
        ::Mesh const &getMesh() const;

        ~RaylibModelHandle() override;
    };
}

#endif
