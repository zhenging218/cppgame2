#include "engine.hpp"
#include "gg_integration.hpp"

namespace {
    using namespace cppengine;

    std::unordered_map<ModelID, ObjectHandle<GladModelHandle>> loadDefaultModels() {
        Triangle triangle;
        Box2D box2D;
        return {
            {ModelID::TRIANGLE, ObjectHandle(createHandle<GladModelHandle>("TRIANGLE",
                triangle.vertices, triangle.getVertexCount(), Triangle::indices, Triangle::index_count)) },
            {ModelID::BOX2D, ObjectHandle(createHandle<GladModelHandle>("BOX2D",
                box2D.vertices, box2D.getVertexCount(), Box2D::indices, Box2D::index_count)) }
        };
    }
}

namespace cppengine {

    GladModelContext::GladModelContext() : models(loadDefaultModels()) {

    }


    ModelID GladModelContext::getModel(std::string const &name) const {
        auto result = std::ranges::find_if(models, [&name](auto const &model) {
            return model.second->getName() == name;
        });

        return result != models.end() ? result->first : NO_MODEL;
    }

    ObjectHandle<ModelHandle> GladModelContext::getModel(ModelID id) const {
        auto result = std::ranges::find_if(models, [&id](auto const &model) {
            return model.first == id;
        });

        return result != models.end() ? result->second : nullptr;
    }

    ModelID GladModelContext::loadModel(const std::string &name, const Vector3 *vertices, const std::uint32_t *indices,
            std::uint32_t vertexCount, std::uint32_t indexCount) {
        auto result = std::ranges::find_if(models, [&name] (auto const &model) {
            return model.second->getName() == name;
        });

        if (result != models.end()) {
            return result->first;
        }

        ObjectHandle model = createHandle<GladModelHandle>(name, vertices, vertexCount, indices, indexCount);
        auto const [it, inserted] = models.try_emplace(static_cast<ModelID>(model->getId()), model);

        if (inserted) {
            return it->first;
        }

        return ModelID::NO_MODEL;
    }

    GladModelContext::~GladModelContext() = default;
}
