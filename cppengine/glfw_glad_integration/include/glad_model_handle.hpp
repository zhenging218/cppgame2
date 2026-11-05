#ifndef GLAD_MODEL_HANDLE_HPP
#define GLAD_MODEL_HANDLE_HPP
#include <cstdint>
#include <string>

#include "graphics/model_handle.hpp"

namespace cppengine {
    class Vector3;

    class GladModelHandle : public ModelHandle {
    private:
        GLuint vao, vbo, ebo;
        std::uint32_t elementCount;

    public:
        GladModelHandle(
            Vector3 const *vertices,
            std::uint32_t vertexCount,
            std::uint32_t const *indices,
            std::uint32_t indexCount);

        GladModelHandle(GladModelHandle const &) = delete;
        GladModelHandle &operator=(GladModelHandle const &) = delete;

        void bindModel() override;
        void unbindModel() override;

        [[nodiscard]] ModelID getId() const override;
        [[nodiscard]] std::uint32_t getElementCount() const;

        ~GladModelHandle() override;
    };
}

#endif
