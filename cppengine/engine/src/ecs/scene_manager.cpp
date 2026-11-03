//
// Created by zyiu on 3/11/2026.
//

#include "ecs/ecs.hpp"

namespace {
  using namespace cppengine;

  struct FromOneIdGenerator : public IdGenerator {
    std::uint64_t id = 0;

    [[nodiscard]] std::uint64_t unidentified() const override {
      return 0;
    }

    [[nodiscard]] std::uint64_t next() override {
      return ++id;
    }

    [[nodiscard]] std::uint64_t curr() override {
      return id;
    }
  };

  struct FromOneCycleGenerator : public CycleGenerator {

    std::uint64_t cycle = 0;

    [[nodiscard]] std::uint64_t next() override {
      return ++cycle;
    }

    [[nodiscard]] std::uint64_t curr() override {
      return cycle;
    }
  };
}

namespace cppengine {

  void SceneManager::load() {
    auto next = createHandle<Scene>(
      transformManager,
      componentManager,
      idGenerator,
      cycleGenerator);

    nextScene->scene = &(*next);
    nextScene->setup();
    scene = next;
    nextScene = nullptr;
    ++state;
  }

  void SceneManager::init() {
    scene->init();
    ++state;
  }

  void SceneManager::update() {
    scene->update();
  }

  void SceneManager::dispose() {
    scene->dispose();
    ++state;
  }

  void SceneManager::unload() {
    scene = nullptr;
    ++state;
  }

  SceneManager::SceneManager()
  : cycleGenerator(createHandle<FromOneCycleGenerator>()),
    idGenerator(createHandle<FromOneIdGenerator>()),
    componentManager(createHandle<ComponentManager>()),
    transformManager(createHandle<TransformManager>()),
    state(SceneState::STARTUP) {

  }

  SceneState SceneManager::getState() const {
    return state;
  }

  SceneManager &SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
  }

  void SceneManager::initialise() {

  }

  void SceneManager::shutdown() {

  }
}
