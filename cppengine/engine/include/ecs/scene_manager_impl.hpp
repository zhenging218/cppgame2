#ifndef SCENE_MANAGER_IMPL_HPP
#define SCENE_MANAGER_IMPL_HPP

namespace cppengine {
  template <typename T, typename ... Args>
  ObjectHandle<T> SceneManager::addComponent(const std::uint64_t id, Args &&... args) {
    auto component = scene->addComponent<T>(id, std::forward<Args>(args)...);
    auto const *descriptor = static_handle_cast<Component>(component)->descriptor;
    descriptor->init(component);
    return component;
  }

  template <typename T>
  void SceneManager::removeComponent(const std::uint64_t id) {
    auto component = scene->getComponent<T>(id);
    auto const *descriptor = static_handle_cast<Component>(component)->descriptor;
    descriptor->dispose(component);
    scene->removeComponent<T>(id);
  }

  template <typename T>
  ObjectHandle<T> SceneManager::getComponent(const std::uint64_t id) const {
    return scene->getComponent<T>(id);
  }

  template <typename T>
  std::vector<ObjectHandle<T>> SceneManager::getAllComponentsOfType() const {
    return scene->getAllComponentsOfType<T>();
  }

  template <typename T, typename ... Rest>
  std::vector<std::tuple<ObjectHandle<T>, ObjectHandle<Rest>...>> SceneManager::getAllComponentSets() const {
    return scene->getAllComponentSets<T, Rest...>();
  }
}

#endif