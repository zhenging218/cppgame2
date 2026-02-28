#ifndef GLAD_MODEL_HANDLE_HPP
#define GLAD_MODEL_HANDLE_HPP
#include <string>

#include "graphics/model_handle.hpp"

namespace cppengine {
    class Vector3;

    class GladModelHandle : public ModelHandle {
    private:
        std::string name;
        GLuint vao, vbo, ebo;
        std::size_t elementCount;

    public:
        GladModelHandle(
            std::string const &name,
            Vector3 const *vertices,
            std::size_t vertexCount,
            std::size_t const *indices,
            std::size_t indexCount);

        GladModelHandle(
            std::string &&name,
            Vector3 const *vertices,
            std::size_t vertexCount,
            std::size_t const *indices,
            std::size_t indexCount);

        GladModelHandle(GladModelHandle const &) = delete;
        GladModelHandle &operator=(GladModelHandle const &) = delete;

        void bindModel() override;
        void unbindModel() override;

        GLuint getId() const;
        std::size_t getElementCount() const;
        std::string const &getName() const override;

        ~GladModelHandle() override;
    };
}

#endif
