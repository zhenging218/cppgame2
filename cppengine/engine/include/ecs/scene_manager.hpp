//
// Created by zyiu on 3/11/2026.
//

#ifndef CPPGAME_SCENE_MANAGER_HPP
#define CPPGAME_SCENE_MANAGER_HPP

#include "ecs/scene_setup.hpp"
#include "ecs/enum_scene_state.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {

  class ComponentManager;
  class TransformManager;

  class SceneManager {
  private:

    ObjectHandle<CycleGenerator> cycleGenerator;
    ObjectHandle<IdGenerator> idGenerator;
    ObjectHandle<ComponentManager> componentManager;
    ObjectHandle<TransformManager> transformManager;

    SceneState state;
    ObjectHandle<Scene> scene;
    ObjectHandle<SceneSetup> nextScene;

    SceneManager();

  public:

    void initialise();
    void shutdown();

    void load();
    void init();
    void update();
    void dispose();
    void unload();

    template <typename T, typename ... Args> requires SceneSetupType<T>
    void loadLevel(Args &&...args);

    [[nodiscard]] SceneState getState() const;

    static SceneManager& getInstance();

    template <typename T, typename ... Rest>
    [[nodiscard]] std::vector<std::tuple<ObjectHandle<T>, ObjectHandle<Rest>...>> getAllComponentSets() const;
  };
}

#endif //CPPGAME_SCENE_MANAGER_HPP