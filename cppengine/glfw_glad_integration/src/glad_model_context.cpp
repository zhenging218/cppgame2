#include "engine.hpp"
#include "gg_integration.hpp"


namespace cppengine {

    GladModelContext::GladModelContext() {
        Triangle triangle;
        Box2D box2D;
        models = {
            {"TRIANGLE", ObjectHandle(new GladModelHandle(
                triangle.vertices, triangle.getVertexCount(), Triangle::indices, Triangle::index_count)) },
            {"BOX2D", ObjectHandle(new GladModelHandle(
                box2D.vertices, box2D.getVertexCount(), Box2D::indices, Box2D::index_count)) }
        };
    }

    ObjectHandle<ModelHandle> GladModelContext::getModel(std::string_view id) const {
        auto result = models.find(id);

        return result != models.end() ? result->second : nullptr;
    }

    ModelID GladModelContext::loadModel(std::string_view name, const Vector3 *vertices, const std::uint32_t *indices,
            std::uint32_t vertexCount, std::uint32_t indexCount) {
        auto result = models.find(name);
        if (result != models.end()) {
            return result->second->getId();
        }

        ObjectHandle<ModelHandle> model = new GladModelHandle(vertices, vertexCount, indices, indexCount);
        auto const [it, inserted] = models.try_emplace(std::string(name), model);

        if (inserted) {
            return it->second->getId();
        }

        return ModelID::NO_MODEL;
    }

    GladModelContext::~GladModelContext() = default;
}
