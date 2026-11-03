//
// Created by Admin on 31/10/2026.
//

#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <functional>
#include <string_view>
#include <vector>

#include "memory/object_handle.hpp"
#include "ecs/ecs_concepts.hpp"
#include "ecs/generators.hpp"

namespace cppengine {
    class TypeDescriptor;
    class Transform;
    class Component;
    class TransformManager;
    class ComponentManager;

    class Scene {
    private:
        friend class SceneSetup;

        friend class GameObjectProxy;

        template <typename T> requires ComponentType<T>
        friend class ComponentProxy;

        std::uint64_t cycle = 0;
        ObjectHandle<CycleGenerator> cycleGenerator;
        ObjectHandle<IdGenerator> idGenerator;
        ObjectHandle<TransformManager> transformManager;
        ObjectHandle<ComponentManager> componentManager;

        std::unordered_map<std::uint64_t, std::string> entities;
        std::unordered_map<std::uint64_t, ObjectHandle<Transform>> transforms;
        std::unordered_map<std::uint64_t, std::unordered_set<TypeDescriptor const *>> componentsOfEntities;
        std::unordered_map<TypeDescriptor const *, std::unordered_map<std::uint64_t, ObjectHandle<Component>>> components;

        std::queue<std::function<void()>> disposalQueue;

        template <typename T, typename ... Args> requires ComponentType<T>
        ObjectHandle<T> setupComponent(std::uint64_t entityId, Args && ... args);

        template <typename T> requires ComponentType<T>
        ObjectHandle<T> getComponentExact(std::uint64_t entityId) const;

        template <typename T> requires ComponentType<T>
        ObjectHandle<T> getComponent(std::uint64_t entityId, std::unordered_map<std::uint64_t, ObjectHandle<Component>> const &candidates) const;

        void removeComponent(std::uint64_t entityId, TypeDescriptor const *descriptor);

        void commitDisposals();
    public:

        Scene(ObjectHandle<TransformManager> transformManager_, ObjectHandle<ComponentManager> componentManager_,
            ObjectHandle<IdGenerator> idGenerator_,
            ObjectHandle<CycleGenerator> cycleGenerator_);

        Scene(Scene const &) = delete;
        Scene(Scene &&other) noexcept = delete;
        Scene &operator=(Scene const &) = delete;
        Scene &operator=(Scene &&other) noexcept = delete;

        template <typename T, typename ... Args> requires ComponentType<T>
        ObjectHandle<T> addComponent(std::uint64_t entityId, Args &&... args);

        template <typename T> requires TransformType<T> || ComponentType<T>
        ObjectHandle<T> getComponent(std::uint64_t entityId) const;

        template <typename T> requires ComponentType<T>
        void removeComponent(std::uint64_t entityId);

        template <typename T, typename ... Rest> requires TransformType<T> || ComponentType<T>
        std::vector<std::tuple<ObjectHandle<T>, ObjectHandle<Rest>...>> getAllComponentSets() const;

        void setEntityName(std::uint64_t entityId, std::string_view newName);
        std::pair<std::uint64_t, std::string_view> createEntity();
        std::pair<std::uint64_t, std::string_view> createEntity(std::string_view name);
        std::pair<std::uint64_t, std::string_view> getEntity(std::uint64_t id) const;
        void removeEntity(std::uint64_t entityId);

        void init();
        void update();
        void dispose();

    };
}

#endif //SCENE_HPP
