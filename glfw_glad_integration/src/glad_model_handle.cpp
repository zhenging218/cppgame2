#include "engine.hpp"
#include "gg_integration.hpp"

namespace {
    using namespace cppengine;
    struct VertexAttribute {
        Vector3 position;
        Vector3 normal;
        Vector3 tangent;
        Colour colour;
        Vector2 uv;
    };

    constexpr std::uint32_t stride = sizeof(VertexAttribute);

    std::vector<VertexAttribute> createAttributeArray(Vector3 const *vertices, std::uint32_t vertexCount) {
        std::vector<VertexAttribute> attributes;
        attributes.reserve(vertexCount);
        std::ranges::transform(vertices, vertices + vertexCount, std::back_insert_iterator(attributes), [](auto const &vertex) {
            return VertexAttribute{
                .position = vertex,
                .normal = {0,1,0},
                .tangent =  {1, 0, 0},
                .colour = {1, 1, 1, 1},
                .uv = { 0, 0 }
            };
        });

        return attributes;
    }

    void initialiseModel(
        GLuint &vao, GLuint &vbo, GLuint &ebo,
        Vector3 const *vertices,
        std::uint32_t vertexCount,
        std::uint32_t const *indices,
        std::uint32_t indexCount) {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        auto attributes = createAttributeArray(vertices, vertexCount);

        glBufferData(GL_ARRAY_BUFFER,
            vertexCount * sizeof(VertexAttribute),
            attributes.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            indexCount * sizeof(decltype(indices[0])),
            indices,
            GL_STATIC_DRAW);

        glVertexAttribPointer(
            AttributeLocation::ATTRIBUTE_POSITION,
            Vector3::value_count,
            GL_FLOAT,
            GL_FALSE,
            stride,
            (void*)offsetof(VertexAttribute, position)
        );
        glEnableVertexAttribArray(AttributeLocation::ATTRIBUTE_POSITION);

        glVertexAttribPointer(
            AttributeLocation::ATTRIBUTE_NORMAL,
            Vector3::value_count,
            GL_FLOAT,
            GL_FALSE,
            stride,
            (void*)offsetof(VertexAttribute, normal)
        );
        glEnableVertexAttribArray(AttributeLocation::ATTRIBUTE_NORMAL);

        glVertexAttribPointer(
            AttributeLocation::ATTRIBUTE_TANGENT,
            Vector3::value_count,
            GL_FLOAT,
            GL_FALSE,
            stride,
            (void*)offsetof(VertexAttribute, tangent)
        );
        glEnableVertexAttribArray(AttributeLocation::ATTRIBUTE_TANGENT);

        glVertexAttribPointer(
            AttributeLocation::ATTRIBUTE_COLOUR,
            Colour::value_count,
            GL_FLOAT,
            GL_FALSE,
            stride,
            (void*)offsetof(VertexAttribute, colour)
        );
        glEnableVertexAttribArray(AttributeLocation::ATTRIBUTE_COLOUR);

        glVertexAttribPointer(
            AttributeLocation::ATTRIBUTE_UV,
            Vector2::value_count,
            GL_FLOAT,
            GL_FALSE,
            stride,
            (void*)offsetof(VertexAttribute, uv)
        );
        glEnableVertexAttribArray(AttributeLocation::ATTRIBUTE_UV);

        glBindVertexArray(0);
    }
}

namespace cppengine {
    GladModelHandle::GladModelHandle(
        std::string &&name,
        Vector3 const *vertices,
        std::uint32_t vertexCount,
        std::uint32_t const *indices,
        std::uint32_t indexCount) : name(std::move(name)), vao(0), vbo(0), ebo(0), elementCount(indexCount) {
        initialiseModel(vao, vbo, ebo, vertices, vertexCount, indices, indexCount);
    }

    GladModelHandle::GladModelHandle(
        std::string const &name,
        Vector3 const *vertices,
        std::uint32_t vertexCount,
        std::uint32_t const *indices,
        std::uint32_t indexCount) : name(name), vao(0), vbo(0), ebo(0), elementCount(indexCount) {
        initialiseModel(vao, vbo, ebo, vertices, vertexCount, indices, indexCount);
    }

    void GladModelHandle::bindModel() {
        glBindVertexArray(vao);
    }

    void GladModelHandle::unbindModel() {
        glBindVertexArray(0);
    }

    std::string const &GladModelHandle::getName() const {
        return name;
    }

    GLuint GladModelHandle::getId() const {
        return vao;
    }

    std::uint32_t GladModelHandle::getElementCount() const {
        return elementCount;
    }

    GladModelHandle::~GladModelHandle() {
        glDeleteBuffers(1, &ebo);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }
}
