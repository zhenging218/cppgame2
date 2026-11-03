//
// Created by zyiu on 3/11/2026.
//

#ifndef CPPGAME_SCENE_MANAGER_IMPL_HPP
#define CPPGAME_SCENE_MANAGER_IMPL_HPP

namespace cppengine {
  template<typename T, typename... Rest>
  std::vector<std::tuple<ObjectHandle<T>, ObjectHandle<Rest>...>> SceneManager::getAllComponentSets() const {
    return scene->getAllComponentSets<T, Rest...>();
  }

  template<typename T, typename... Args> requires SceneSetupType<T>
  void SceneManager::loadLevel(Args &&... args) {
    nextScene = createHandle<T>(std::forward<Args>(args)...);
    ++state;
  }
}

#endif //CPPGAME_SCENE_MANAGER_IMPL_HPP