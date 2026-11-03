//
// Created by zyiu on 3/11/2026.
//

#ifndef CPPGAME_SCENE_MANAGER_HPP
#define CPPGAME_SCENE_MANAGER_HPP

#include "ecs/enum_scene_state.hpp"
#include "memory/object_handle.hpp"

namespace cppengine {

  class ComponentManager;
  class TransformManager;

  class SceneManager {
    private:

      ObjectHandle<ComponentManager> componentManager;
      ObjectHandle<TransformManager> transformManager;

      ObjectHandle<Scene> scene;
      ObjectHandle<Scene> nextScene;
    public:

      void initialise();
      void shutdown();

      void load();
      void init();
      void update();
      void dispose();
      void unload();

      SceneState getState() const;

      static SceneManager& getInstance();

      template <typename T, typename ... Rest>
      [[nodiscard]] std::vector<std::tuple<ObjectHandle<T>, ObjectHandle<Rest>...>> getAllComponentSets() const;
  };
}

#endif //CPPGAME_SCENE_MANAGER_HPP