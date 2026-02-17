#ifndef SCENE_HPP
#define SCENE_HPP
#include <algorithm>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>

#include "component.hpp"
#include "maths/transform.hpp"
#include "memory/type_descriptor.hpp"

namespace cppengine {
    template <typename T>
    concept ComponentType = std::is_base_of_v<Component, T>;

    template <typename T>
    concept TransformType = std::is_same_v<Transform, T>;

    class Scene {
    private:
        using entity_map_type = std::unordered_map<std::uint64_t, std::string>;
        using transform_graph_type = std::unordered_map<std::uint64_t, ObjectHandle<Transform>>;
        using entity_component_map_type = std::unordered_map<uint64_t, std::unordered_set<TypeDescriptor const *>>;
        using component_entity_map_type = std::unordered_map<std::uint64_t, ObjectHandle<Component>>;
        using component_map_type = std::unordered_map<TypeDescriptor const *, component_entity_map_type>;

        std::uint64_t nextId;
        entity_map_type entities;
        transform_graph_type transforms;
        entity_component_map_type ecs;
        component_map_type components;

    public:
        Scene();
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
        ObjectHandle<T> getComponent(const std::uint64_t ownerId) const {
            if constexpr (TransformType<T>) {
                return getTransformOfEntity(ownerId);
            }

            TypeDescriptor const *descriptor = TypeDescriptor::getTypeDescriptor<T>();
            if (ecs.contains(ownerId)) {
                auto const &entityComponents = ecs.at(ownerId);
                if (entityComponents.contains(descriptor)) {
                    return dynamic_handle_cast<T>(components.at(descriptor).at(ownerId));
                }

                auto result = std::find_if(
                    entityComponents.begin(), entityComponents.end(),
                    [&descriptor](auto componentType) {
                    return TypeDescriptor::isSuperType<T>(componentType);
                });

                if (result != entityComponents.end()) {
                    return dynamic_handle_cast<T>(components.at(*result).at(ownerId));
                }
            }

            return nullptr;
        }

        template <typename T, typename ... Args> requires ComponentType<T>
        ObjectHandle<T> addComponent(const std::uint64_t ownerId, Args &&... args) {
            TypeDescriptor const *descriptor = TypeDescriptor::getTypeDescriptor<T>();

            if (ecs.contains(ownerId)) {
                if (ecs.at(ownerId).contains(descriptor)) {
                    return dynamic_handle_cast<T>(components.at(descriptor).at(ownerId));
                }

                ObjectHandle<Component> handle = createHandle<T>(std::forward<Args>(args)...);
                handle->descriptor = descriptor;
                components[descriptor][ownerId] = handle;
                ecs[ownerId].insert(descriptor);
                return dynamic_handle_cast<T>(handle);
            }

            return nullptr;
        }

        template <typename T> requires ComponentType<T>
        void removeComponent(const std::uint64_t ownerId) {
            TypeDescriptor const *descriptor = TypeDescriptor::getTypeDescriptor<T>();

            if (ecs.contains(ownerId) && ecs.at(ownerId).contains(descriptor)) {
                components.at(descriptor).erase(ownerId);
                ecs.at(ownerId).erase(descriptor);
            }
        }

        template <typename T> requires ComponentType<T>
        std::uint64_t getEntityOfComponent(ObjectHandle<T> component) const {
            if (component != nullptr) {
                // no need poly check, descriptor should always tally
                TypeDescriptor const *descriptor = dynamic_handle_cast<Component>(component)->descriptor;
                auto component_list = std::find_if(
                    components.begin(), components.end(),
                    [&descriptor](const component_map_type::value_type &value) {
                    return descriptor == value.first;
                });

                if (component_list != components.end()) {
                    auto entity = std::find_if(
                        component_list->second.begin(), component_list->second.end(),
                        [&component](auto const &value) {
                        return value.second == component;
                    });

                    if (entity != component_list->second.end()) {
                        return entity->first;
                    }
                }
            }
            return 0;
        }

        template<typename T> requires ComponentType<T>
        std::vector<ObjectHandle<T>> getAllComponentsOfType(const std::uint64_t ownerId) const {
            TypeDescriptor const *descriptor = TypeDescriptor::getTypeDescriptor<T>();
            std::vector<ObjectHandle<T>> results;
            if (ecs.contains(ownerId)) {
                auto const &componentsOfEntity = ecs.at(ownerId);
                std::for_each(componentsOfEntity.begin(), componentsOfEntity.end(),
                    [this, &results, &descriptor, &ownerId](TypeDescriptor const *componentType) {
                    if (TypeDescriptor::isSuperType(descriptor, componentType)) {
                        results.push_back(dynamic_handle_cast<T>(components.at(componentType).at(ownerId)));
                    }
                });
            }
            return results;
        }

        template <typename T> requires ComponentType<T>
        std::vector<ObjectHandle<T>> getAllComponentsOfType() const {
            TypeDescriptor const *descriptor = TypeDescriptor::getTypeDescriptor<T>();

            std::vector<ObjectHandle<T>> results;

            if (components.contains(descriptor)) {
            auto const &entityMap = components.at(descriptor);
            results.reserve(entityMap.size());
            std::ranges::transform(entityMap, std::back_inserter(results),
                    [](auto const &component) {
                    return dynamic_handle_cast<T>(component.second);
                });
            }

            return results;
        }

        template <typename T, typename ... Rest>
        std::vector<std::tuple<ObjectHandle<T>, ObjectHandle<Rest>...>> getAllComponentSets() const {

            std::vector<std::tuple<ObjectHandle<T>, ObjectHandle<Rest>...>> results;

            for (auto const &[id, name] : entities) {
                auto list = std::make_tuple(
                    getComponent<T>(id),
                    getComponent<Rest>(id)...
                );
                if (std::get<ObjectHandle<T>>(list) != nullptr
                    && ((std::get<ObjectHandle<Rest>>(list) != nullptr) && ...)) {
                    results.emplace_back(std::move(list));
                }
            }

            return results;
        }
    };

}

#endif