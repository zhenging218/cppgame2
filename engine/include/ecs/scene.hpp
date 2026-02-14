#ifndef SCENE_HPP
#define SCENE_HPP
#include <algorithm>
#include <cstdint>
#include <map>
#include <set>

#include "component.hpp"
#include "maths/transform.hpp"
#include "memory/type_descriptor.hpp"

namespace cppengine {
    class Scene {
    private:
        using entity_list_type = std::map<std::uint64_t, std::string>;
        using transform_graph_type = std::map<std::uint64_t, ObjectHandle<Transform>>;
        using entity_component_list_type = std::map<std::uint64_t, std::set<TypeDescriptor const *>>;
        using component_list_type = std::map<TypeDescriptor const *, std::map<std::uint64_t, ObjectHandle<Component>>>;

        std::uint64_t nextId;
        entity_list_type entities;
        transform_graph_type transforms;
        entity_component_list_type ecs;
        component_list_type components;

    public:
        Scene();
        Scene(const Scene &other) = delete;
        Scene & operator=(const Scene &other) = delete;

        Scene(Scene &&other) noexcept;
        Scene & operator=(Scene &&other) noexcept;

        template <typename T>
        ObjectHandle<T> getComponent(const std::uint64_t ownerId) const {
            TypeDescriptor const *descriptor = TypeDescriptor::getTypeDescriptor<T>();
            if (ecs.contains(ownerId)) {
                auto const &entityComponents = ecs.at(ownerId);
                if (entityComponents.contains(descriptor)) {
                    return dynamic_handle_cast<T>(components.at(descriptor).at(ownerId));
                }

                auto result = std::find_if(entityComponents.begin(), entityComponents.end(), [&descriptor](auto componentType) {
                    return TypeDescriptor::isSuperType<T>(componentType);
                });

                if (result != entityComponents.end()) {
                    return dynamic_handle_cast<T>(components.at(*result).at(ownerId));
                }
            }

            return nullptr;
        }

        template <typename T, typename ... Args>
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

        template <typename T>
        void removeComponent(const std::uint64_t ownerId) {
            TypeDescriptor const *descriptor = TypeDescriptor::getTypeDescriptor<T>();

            if (ecs.contains(ownerId) && ecs.at(ownerId).contains(descriptor)) {
                components.at(descriptor).erase(ownerId);
                ecs.at(ownerId).erase(descriptor);
            }
        }

        std::uint64_t createEntity();
        void destroyEntity(const std::uint64_t id);
        ObjectHandle<Transform> getTransformOfEntity(const std::uint64_t id) const;

        std::string const &getNameOfEntity(uint64_t id) const;
        void setNameOfEntity(const std::uint64_t id, std::string const &name);
        void setNameOfEntity(const std::uint64_t id, std::string &&name);

        template <typename T>
        std::uint64_t getEntityOfComponent(ObjectHandle<T> component) const {
            // no need poly check, descriptor should always tally
            TypeDescriptor const *descriptor = dynamic_handle_cast<Component>(component)->descriptor;
            auto component_list = std::find_if(components.begin(), components.end(), [&descriptor](const component_list_type::value_type &value) {
                return descriptor == value.first;
            });

            if (component_list != components.end()) {
                auto entity = std::find_if(component_list->second.begin(), component_list->second.end(), [&component](auto const &value) {
                    return value.second == component;
                });

                if (entity != component_list->second.end()) {
                    return entity->first;
                }
            }

            return 0;
        }

        std::uint64_t getEntityOfComponent(Component const *component) const;

        template <typename T>
        std::vector<ObjectHandle<T>> getAllComponentsOfType() const {
            TypeDescriptor const *descriptor = TypeDescriptor::getTypeDescriptor<T>();

            // todo: refactor this method
            // get list of all components that T == component type or T super of component type
            // get the components into list
            // return

            if (components.contains(descriptor)) {
                auto const &targets = components.at(descriptor);
                std::vector<ObjectHandle<T>> results;
                results.reserve(targets.size());
                std::transform(targets.begin(), targets.end(), std::back_inserter(results), [](auto const &handle) { return handle.second; });
                return results;
            }

            return {};
        }
    };
}

#endif