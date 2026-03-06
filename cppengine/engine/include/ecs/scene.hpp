#ifndef SCENE_HPP
#define SCENE_HPP

#include <algorithm>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>

#include "scene_manager.hpp"
#include "maths/transform.hpp"

namespace cppengine {

    class Component;
    template <typename T>
    class ObjectHandle;

    template <typename T>
    concept ComponentType = std::is_base_of_v<Component, T>;

    template <typename T>
    concept TransformType = std::is_same_v<Transform, T>;

    class Scene {
    private:

        using entity_map_type = std::unordered_map<std::uint64_t, std::string>;
        using transform_graph_type = std::unordered_map<std::uint64_t, ObjectHandle<Transform>>;
        using entity_component_map_type = std::unordered_map<uint64_t, std::unordered_set<ComponentDescriptor const *>>;
        using component_entity_map_type = std::unordered_map<std::uint64_t, ObjectHandle<Component>>;
        using component_map_type = std::unordered_map<ComponentDescriptor const *, component_entity_map_type>;

        std::uint64_t nextId;
        ObjectHandle<ObjectAllocatorContext> allocators;
        entity_map_type entities;
        transform_graph_type transforms;
        entity_component_map_type ecs;
        component_map_type components;

        template <typename T, typename U> requires ComponentType<T>
        static ObjectHandle<T> castComponentHandle(ObjectHandle<U> handle);

        template <typename T, typename U> requires TransformType<T>
        static ObjectHandle<T> castComponentHandle(ObjectHandle<U> handle);

    public:
        Scene(ObjectHandle<ObjectAllocatorContext> allocators_);
        Scene(const Scene &other) = delete;
        Scene & operator=(const Scene &other) = delete;

        Scene(Scene &&other) noexcept;
        Scene & operator=(Scene &&other) noexcept;

        std::uint64_t createEntity();
        void destroyEntity(const std::uint64_t id);
        ObjectHandle<Transform> getTransformOfEntity(const std::uint64_t id) const;

        std::string const &getNameOfEntity(uint64_t id) const;
        void setNameOfEntity(const std::uint64_t id, std::string const &name);
        void setNameOfEntity(const std::uint64_t id, std::string &&name);
        std::uint64_t getEntityOfComponent(Component const *component) const;
        std::uint64_t getEntityOfTransform(ObjectHandle<Transform> transform) const;

        std::vector<ObjectHandle<Component>> getAllComponents() const;

        template <typename T> requires (ComponentType<T> || TransformType<T>)
        ObjectHandle<T> getComponent(const std::uint64_t ownerId) const;

        template <typename T, typename ... Args> requires ComponentType<T>
        ObjectHandle<T> addComponent(const std::uint64_t ownerId, Args &&... args);

        template <typename T> requires ComponentType<T>
        void removeComponent(const std::uint64_t ownerId);

        template <typename T> requires ComponentType<T>
        std::uint64_t getEntityOfComponent(ObjectHandle<T> component) const;

        template<typename T> requires ComponentType<T>
        std::vector<ObjectHandle<T>> getAllComponentsOfType(const std::uint64_t ownerId) const;

        template <typename T> requires ComponentType<T>
        std::vector<ObjectHandle<T>> getAllComponentsOfType() const;

        template <typename T, typename ... Rest>
        std::vector<std::tuple<ObjectHandle<T>, ObjectHandle<Rest>...>> getAllComponentSets() const;

        void init();
        void update();
        void dispose();
    };
}

#endif