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
}

#endif //CPPGAME_SCENE_MANAGER_IMPL_HPP