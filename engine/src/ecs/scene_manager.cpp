#include "engine.hpp"

namespace cppengine {
    std::uint64_t SceneManager::createEntity() {
        return scene->createEntity();
    }

    void SceneManager::destroyEntity(const std::uint64_t id) {
        scene->destroyEntity(id);
    }

    std::uint64_t SceneManager::getEntityOfComponent(Component const *component) const {
        return scene->getEntityOfComponent(component);
    }

    std::string const &SceneManager::getNameOfEntity(uint64_t id) const {
        return scene->getNameOfEntity(id);
    }

    void SceneManager::setNameOfEntity(const std::uint64_t id, std::string const &name) {
        scene->setNameOfEntity(id, name);
    }

    void SceneManager::setNameOfEntity(const std::uint64_t id, std::string &&name) {
        scene->setNameOfEntity(id, name);
    }

    ObjectHandle<Transform> SceneManager::getTransformOfEntity(const std::uint64_t id) const {
        return scene->getTransformOfEntity(id);
    }

    std::uint64_t SceneManager::getEntityOfTransform(ObjectHandle<Transform> transform) const {
        return scene->getEntityOfTransform(transform);
    }

    void SceneManager::initialise() {

    }

    void SceneManager::shutdown() {

    }

    void SceneManager::setup() {
        auto next = createHandle<Scene>();
        nextScene->setup(next);
        scene = next;
        nextScene = nullptr;
        ++state;
    }

    void SceneManager::teardown() {
        scene = nullptr;
        ++state;
    }

    SceneManager::SceneManager()
    : state(SceneState::INITIALISE) {

    }

    SceneState SceneManager::getState() const {
        return state;
    }

    SceneManager &SceneManager::getInstance() {
        static SceneManager instance;
        return instance;
    }
}
