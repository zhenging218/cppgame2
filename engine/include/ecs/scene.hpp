#ifndef SCENE_HPP
#define SCENE_HPP
#include <algorithm>
#include <cstdint>
#include <map>

#include "component.hpp"
#include "maths/transform.hpp"
#include "memory/type_descriptor.hpp"

namespace cppengine {
    class Scene {
    private:
        using entity_list_type = std::map<std::uint64_t, std::string>;
        using transform_graph_type = std::map<std::uint64_t, ObjectHandle<Transform>>;
        using component_list_type = std::map<TypeDescriptor const *, std::map<std::uint64_t, ObjectHandle<Component>>>;

        std::uint64_t nextId;
        entity_list_type entities;
        transform_graph_type transforms;
        component_list_type components;

    public:
        Scene();
        Scene(const Scene &other) = delete;
        Scene & operator=(const Scene &other) = delete;

        Scene(Scene &&other) noexcept
            : nextId(other.nextId),
              entities(std::move(other.entities)),
              transforms(std::move(other.transforms)),
              components(std::move(other.components)) {
        }

        Scene & operator=(Scene &&other) noexcept {
            std::swap(nextId, other.nextId);
            std::swap(entities, other.entities);
            std::swap(transforms, other.transforms);
            std::swap(components, other.components);
            return *this;
        }

        template <typename T>
        ObjectHandle<T> getComponent(std::uint64_t ownerId) const {
            TypeDescriptor const *descriptor = TypeDescriptor::getTypeDescriptor<T>();
            auto component_list = std::find_if(components.begin(), components.end(), [&descriptor, &ownerId](const component_list_type::value_type &value) {
                return descriptor == value.first && value.second.contains(ownerId);
            });

            if (component_list != components.end()) {
                return dynamic_handle_cast<T>((component_list->second)[ownerId]);
            }

            return nullptr;
        }

        template <typename T, typename ... Args>
        ObjectHandle<T> addComponent(std::uint64_t ownerId, Args &&... args) {
            TypeDescriptor const *descriptor = TypeDescriptor::getTypeDescriptor<T>();
            auto component_list = std::find_if(components.begin(), components.end(), [&descriptor, &ownerId](const component_list_type::value_type &value) {
                return descriptor == value.first && value.second.contains(ownerId);
            });

            if (component_list != components.end()) {
                return dynamic_handle_cast<T>((component_list->second)[ownerId]);
            }

            auto handle = createHandle<T>(std::forward<Args>(args)...);
            (component_list->second)[ownerId] = handle;
            return handle;
        }

        template <typename T>
        void removeComponent(std::uint64_t ownerId) {
            TypeDescriptor const *descriptor = TypeDescriptor::getTypeDescriptor<T>();
            auto component_list = std::find_if(components.begin(), components.end(), [&descriptor, &ownerId](const component_list_type::value_type &value) {
                return descriptor == value.first && value.second.contains(ownerId);
            });

            if (component_list != components.end()) {
                (component_list->second).erase(ownerId);
            }
        }

        std::uint64_t createEntity();
        void destroyEntity(std::uint64_t id);

        template <typename T>
        std::uint64_t getEntityOfComponent(ObjectHandle<T> component) {
            TypeDescriptor const *descriptor = TypeDescriptor::getTypeDescriptor<T>();
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

    };
}

#endif