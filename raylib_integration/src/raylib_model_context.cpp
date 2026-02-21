#include <cstring>

#include "engine.hpp"
#include "raylib_integration.hpp"

namespace {
    using namespace cppengine;

    ObjectHandle<ModelHandle> createModelHandle(std::string const &name, ::Mesh &mesh) {
        return static_handle_cast<ModelHandle>(createHandle<RaylibModelHandle>(name, mesh));
    }

    ObjectHandle<ModelHandle> createTriangleModelHandle() {
        ::Mesh mesh = {};

        Triangle triangle;

        mesh.vertexCount = Triangle::vertex_count;
        mesh.triangleCount = Triangle::index_count / 3;
        auto vertexSize = mesh.vertexCount * Triangle::vertex_type::value_count * sizeof(Triangle::value_type);
        auto indexSize = Triangle::index_count * sizeof(unsigned short);

        mesh.vertices = static_cast<float *>(MemAlloc(vertexSize));
        std::memcpy(mesh.vertices, MathHelper::StructToArrayConverter<Triangle::vertex_type, Triangle::value_type>::convert(triangle.vertices), vertexSize);
        mesh.indices = static_cast<unsigned short *>(MemAlloc(indexSize));

        for (std::size_t i = 0; i < Triangle::index_count; ++i) {
            mesh.indices[i] = Triangle::indices[i];
        }

        return createModelHandle("TRIANGLE", mesh);
    }

    ObjectHandle<ModelHandle> createBox2DModelHandle() {
        ::Mesh mesh = {};

        Box2D box2D;

        mesh.vertexCount = Box2D::vertex_count;
        mesh.triangleCount = Box2D::index_count / 3;
        auto vertexSize = mesh.vertexCount * Box2D::vertex_type::value_count * sizeof(Box2D::value_type);
        auto indexSize = Box2D::index_count * sizeof(unsigned short);

        mesh.vertices = static_cast<float *>(MemAlloc(vertexSize));
        std::memcpy(mesh.vertices, MathHelper::StructToArrayConverter<Box2D::vertex_type, Box2D::value_type>::convert(box2D.vertices), vertexSize);
        mesh.indices = static_cast<unsigned short *>(MemAlloc(indexSize));

        for (std::size_t i = 0; i < Box2D::index_count; ++i) {
            mesh.indices[i] = Box2D::indices[i];
        }

        return createModelHandle("BOX2D", mesh);
    }
}

namespace cppengine {
    RaylibModelContext::RaylibModelContext() : models({
     {
            static_cast<ModelID>(HashHelper::fnv1a_64(std::string_view{"TRIANGLE"})),
            createTriangleModelHandle()
        },
     {
            static_cast<ModelID>(HashHelper::fnv1a_64(std::string_view{"BOX2D"})),
            createBox2DModelHandle()
        },
    }) {

    }

    ObjectHandle<ModelHandle> RaylibModelContext::getModel(ModelID id) const {
        if (models.contains(id)) {
            return models.at(id);
        }
        return nullptr;
    }

    ModelID RaylibModelContext::loadModel(std::string const &name, Vector3 const *vertices, std::size_t const *indices, std::size_t vertexCount, std::size_t indexCount) {
        auto result = std::ranges::find_if(models, [&](auto const &model) {
            return model.second->getName() == name;
        });

        if (result != models.end()) {
            return result->first;
        }

        // load mesh with vertices and indices
        ::Mesh mesh = {};
        mesh.vertexCount = static_cast<int>(vertexCount);
        mesh.triangleCount = static_cast<int>(indexCount / 3);
        auto vertexSize = vertexCount * Vector3::value_count * sizeof(float);
        auto indexSize = indexCount * sizeof(unsigned short);

        mesh.vertices = static_cast<float *>(MemAlloc(vertexSize));
        std::memcpy(mesh.vertices, MathHelper::StructToArrayConverter<Vector3, float>::convert(vertices), vertexSize);
        mesh.indices = static_cast<unsigned short *>(MemAlloc(indexSize));

        for (std::size_t i = 0; i < indexCount; ++i) {
            mesh.indices[i] = indices[i];
        }

        auto handle = static_handle_cast<ModelHandle>(createHandle<RaylibModelHandle>(name, mesh));

        auto[it, inserted] = models.insert({
            static_cast<ModelID>(HashHelper::fnv1a_64(std::string_view{name})),
            handle});

        if (inserted) {
            return it->first;
        }

        return NO_MODEL;
    }
}
