#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <cstdint>

#include "enum_scene_state.hpp"
#include "memory/object_handle.hpp"
#include "scene.hpp"
#include "scene_setup.hpp"

namespace cppengine {
    class SceneManager {
    private:
        SceneState state;
        ObjectHandle<SceneSetup> nextScene;
        ObjectHandle<Scene> scene;
    public:
        SceneManager();
        SceneManager(SceneManager const &) = delete;
        SceneManager(SceneManager &&) = delete;
        SceneManager &operator=(SceneManager const &) = delete;
        SceneManager &operator=(SceneManager &&) = delete;

        static SceneManager &getInstance();

        void initialise();

        template <typename T, typename ... Args>
        void loadLevel(Args &&... args) {
            nextScene = createHandle<T>(std::forward<Args>(args)...);
            ++state;
        }

        void setup();
        void teardown();

        SceneState getState() const;
        void shutdown();

        template <typename T, typename ... Args>
        ObjectHandle<T> addComponent(const std::uint64_t id, Args &&... args) {
            return scene->addComponent<T>(id, std::forward<Args>(args)...);
        }

        template <typename T>
        void removeComponent(const std::uint64_t id) {
            scene->removeComponent<T>(id);
        }

        template <typename T>
        ObjectHandle<T> getComponent(const std::uint64_t id) const {
            return scene->getComponent<T>(id);
        }

        std::uint64_t createEntity();
        void destroyEntity(const std::uint64_t id);
        ObjectHandle<Transform> getTransformOfEntity(const std::uint64_t id) const;

        std::string const &getNameOfEntity(uint64_t id) const;
        void setNameOfEntity(const std::uint64_t id, std::string const &name);
        void setNameOfEntity(const std::uint64_t id, std::string &&name);

        std::uint64_t getEntityOfComponent(Component const *component) const;
        std::uint64_t getEntityOfTransform(ObjectHandle<Transform> transform) const;

        template <typename T>
        std::vector<ObjectHandle<T>> getAllComponentsOfType() const {
            return scene->getAllComponentsOfType<T>();
        }

        template <typename T, typename ... Rest>
        std::vector<std::tuple<ObjectHandle<T>, ObjectHandle<Rest>...>> getAllComponentSets() const {
            return scene->getAllComponentSets<T, Rest...>();
        }

    };
}

#endif