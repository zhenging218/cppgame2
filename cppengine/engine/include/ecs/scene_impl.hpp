#ifndef SCENE_IMPL_HPP
#define SCENE_IMPL_HPP

namespace cppengine {
    template <typename T, typename U> requires ComponentType<T>
    ObjectHandle<T> Scene::castComponentHandle(ObjectHandle<U> handle) {
        return static_handle_cast<T>(handle);
    }

    template <typename T, typename U> requires TransformType<T>
    ObjectHandle<T> Scene::castComponentHandle(ObjectHandle<U> handle) {
        static_assert(!TransformType<T>, "function should not be instanced");
        return nullptr;
    }

    template <typename T>  requires (ComponentType<T> || TransformType<T>)
    ObjectHandle<T> Scene::getComponent(const std::uint64_t ownerId) const {
        if constexpr (TransformType<T>) {
            return getTransformOfEntity(ownerId);
        } else {
            ComponentDescriptor const *descriptor = ComponentDescriptor::getComponentDescriptor<T>();
            if (ecs.contains(ownerId)) {
                auto const &entityComponents = ecs.at(ownerId);
                if (entityComponents.contains(descriptor)) {
                    return castComponentHandle<T>(components.at(descriptor).at(ownerId));
                }

                auto result = std::find_if(
                    entityComponents.begin(), entityComponents.end(),
                    [&descriptor](auto componentType) {
                    return descriptor->isSuperType(componentType);
                });

                if (result != entityComponents.end()) {
                    return castComponentHandle<T>(components.at(*result).at(ownerId));
                }
            }
        }

        return nullptr;
    }

    template <typename T, typename ... Args> requires ComponentType<T>
    ObjectHandle<T> Scene::addComponent(const std::uint64_t ownerId, Args &&... args) {
        ComponentDescriptor const *descriptor = ComponentDescriptor::getComponentDescriptor<T>();

        if (ecs.contains(ownerId)) {
            if (ecs.at(ownerId).contains(descriptor)) {
                return dynamic_handle_cast<T>(components.at(descriptor).at(ownerId));
            }

            ObjectHandle<Component> handle = allocators->createHandle<T>(std::forward<Args>(args)...);

            handle->descriptor = descriptor;
            components[descriptor][ownerId] = handle;
            ecs[ownerId].insert(descriptor);
            return static_handle_cast<T>(handle);
        }

        return nullptr;
    }

    template <typename T> requires ComponentType<T>
    void Scene::removeComponent(const std::uint64_t ownerId) {
        ComponentDescriptor const *descriptor = ComponentDescriptor::getComponentDescriptor<T>();

        if (ecs.contains(ownerId) && ecs.at(ownerId).contains(descriptor)) {
            auto &entityMap = components.at(descriptor);
            entityMap.erase(ownerId);
            ecs.at(ownerId).erase(descriptor);
        }
    }

    template <typename T> requires ComponentType<T>
    std::uint64_t Scene::getEntityOfComponent(ObjectHandle<T> component) const {
        if (component != nullptr) {
            // no need poly check, descriptor should always tally
            ComponentDescriptor const *descriptor = dynamic_handle_cast<Component>(component)->descriptor;
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
    std::vector<ObjectHandle<T>> Scene::getAllComponentsOfType(const std::uint64_t ownerId) const {
        ComponentDescriptor const *descriptor = ComponentDescriptor::getComponentDescriptor<T>();
        std::vector<ObjectHandle<T>> results;
        if (ecs.contains(ownerId)) {
            auto const &componentsOfEntity = ecs.at(ownerId);
            std::for_each(componentsOfEntity.begin(), componentsOfEntity.end(),
                [this, &results, &descriptor, &ownerId](ComponentDescriptor const *componentType) {
                if (descriptor->isSuperType(componentType)) {
                    results.push_back(static_handle_cast<T>(components.at(componentType).at(ownerId)));
                }
            });
        }
        return results;
    }

    template <typename T> requires ComponentType<T>
    std::vector<ObjectHandle<T>> Scene::getAllComponentsOfType() const {
        ComponentDescriptor const *descriptor = ComponentDescriptor::getComponentDescriptor<T>();

        std::vector<ObjectHandle<T>> results;

        if (components.contains(descriptor)) {
            auto const &entityMap = components.at(descriptor);
            results.reserve(entityMap.size());
            std::ranges::transform(entityMap, std::back_inserter(results),
                    [](auto const &component) {
                    return static_handle_cast<T>(component.second);
                });
        }

        return results;
    }

    template <typename T, typename ... Rest>
    std::vector<std::tuple<ObjectHandle<T>, ObjectHandle<Rest>...>> Scene::getAllComponentSets() const {

        std::vector<std::tuple<ObjectHandle<T>, ObjectHandle<Rest>...>> results;

        if constexpr (TransformType<T>) {

            for (auto const &[id, transform] : transforms) {
                auto list = std::make_tuple(
                    transform,
                    getComponent<Rest>(id)...
                );

                if (((std::get<ObjectHandle<Rest>>(list) != nullptr) && ...)) {
                    results.emplace_back(std::move(list));
                }
            }
        } else {
            ComponentDescriptor const *anchoringType = ComponentDescriptor::getComponentDescriptor<T>();
            for (auto const &[descriptor, entityMap] : components) {
                if (anchoringType->isSuperType(descriptor)) {
                    for (auto const &[id, handle] : entityMap) {
                        auto list = std::make_tuple(
                            static_handle_cast<T>(handle),
                            getComponent<Rest>(id)...
                        );

                        if (((std::get<ObjectHandle<Rest>>(list) != nullptr) && ...)) {
                            results.emplace_back(std::move(list));
                        }
                    }
                }
            }
        }
        return results;
    }
}

#endif