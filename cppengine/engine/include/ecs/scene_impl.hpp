//
// Created by Admin on 31/10/2026.
//

#ifndef CPPGAME_SCENE_IMPL_HPP
#define CPPGAME_SCENE_IMPL_HPP

#include "ecs/ecs_concepts.hpp"
#include "ecs/scene.hpp"

namespace cppengine {
    template<typename T> requires ComponentType<T>
    void Scene::removeComponent(std::uint64_t entityId) {
        const auto descriptor = TypeDescriptor::getTypeDescriptor<T>();
        removeComponent(entityId, descriptor);
    }

    template<typename T, typename... Args>
    ObjectHandle<T> Scene::setupComponent(std::uint64_t entityId, Args &&... args) {
        const auto descriptor = TypeDescriptor::getTypeDescriptor<T>();

        if (entities.contains(entityId)) {
            auto &componentMap = componentsOfEntities[entityId];
            if (componentMap.contains(descriptor)) {
                return nullptr;
            }

            auto &entityMap = components[descriptor];

            auto entity = std::ranges::find_if(entityMap, [entityId](auto const &list) {
                return list.first == entityId;
            });

            if (entity == entityMap.end()) {
                auto component = static_handle_cast<Component>(componentManager->createComponent<T>(std::forward<Args>(args)...));
                component->setState(ComponentState::INITIALISING);
                component->setStamp(cycleGenerator->curr());
                const auto [it, emplaced] = entityMap.emplace(std::make_pair(entityId, component));

                if (!emplaced) {
                    throw R"(somehow created a new component even though a component of the type already exists)";
                }

                auto [descriptorIt, descriptorEmplaced] = componentMap.emplace(descriptor);

                if (!descriptorEmplaced) {
                    throw R"(somehow created a new component even though a component of the type already exists)";
                }

                return static_handle_cast<T>(component);
            }
        }

        return nullptr;
    }

    template<typename T, typename... Args> requires ComponentType<T>
    ObjectHandle<T> Scene::addComponent(std::uint64_t entityId, Args &&... args) {
        auto component = setupComponent<T>(entityId, std::forward<Args>(args)...);

        if (component != nullptr) {
            if constexpr(InitialisableComponentType<T>) {
                component->init();
            }
            static_handle_cast<Component>(component)->setState(ComponentState::ACTIVE);
        } else {
            // get component but match exactly the type
            component = getComponentExact<T>(entityId);
        }

        return component;
    }

    template<typename T> requires ComponentType<T>
    ObjectHandle<T> Scene::getComponent(std::uint64_t entityId,
        std::unordered_map<std::uint64_t, ObjectHandle<Component>> const &candidates) const {
        auto result = std::ranges::find_if(candidates, [entityId](auto const &component) {
            auto state = component.second->getState();
            return entityId == component.first && state != ComponentState::DISPOSING && state != ComponentState::DISPOSED;
        });

        return result != candidates.end() ? static_handle_cast<T>(result->second) : nullptr;
    }

    template<typename T> requires ComponentType<T>
    ObjectHandle<T> Scene::getComponentExact(std::uint64_t entityId) const {
        const auto target = TypeDescriptor::getTypeDescriptor<T>();

        const auto & componentMap = std::ranges::find_if(componentsOfEntities, [entityId](auto const &coe) { return coe.first == entityId; });

        if (componentMap != componentsOfEntities.end()) {
            if (componentMap->second.contains(target)) {
                const auto candidates = std::ranges::find_if(components, [target](auto const &list) {
                    return list.first == target;
                });

                if (candidates != components.end()) {
                    return getComponent<T>(entityId, candidates->second);
                }
            }
        }

        return nullptr;
    }

    template<typename T> requires TransformType<T> || ComponentType<T>
    ObjectHandle<T> Scene::getComponent(std::uint64_t entityId) const {
        if constexpr (TransformType<T>) {
            auto const t = transforms.find(entityId);

            return t != transforms.end() ? t->second : nullptr;
        } else {
            auto target = TypeDescriptor::getTypeDescriptor<T>();

            const auto & componentMap = std::ranges::find_if(componentsOfEntities, [entityId](auto const &coe) {
                return coe.first == entityId;
            });

            if (componentMap != componentsOfEntities.end()) {
                auto firstMatch = std::ranges::find_if(componentMap->second, [target](auto const &descriptor) {
                    return TypeDescriptor::isSuperType(target, descriptor);
                });

                if (firstMatch != componentMap->second.end()) {
                    target = *firstMatch;

                    const auto candidates = std::ranges::find_if(components, [target](auto const &list) {
                        return list.first == target;
                    });

                    if (candidates != components.end()) {
                        return getComponent<T>(entityId, candidates->second);
                    }
                }
            }

            return nullptr;
        }
    }

    template<typename T, typename... Rest>
    std::vector<std::tuple<ObjectHandle<T>, ObjectHandle<Rest>...>> Scene::getAllComponentSets() const {
        std::vector<std::tuple<ObjectHandle<T>, ObjectHandle<Rest>...>> result;

        if  constexpr (TransformType<T>) {

            for (auto const& [id, transform] : transforms) {
                auto set = std::make_tuple(transform, getComponent<Rest>(id)...);

                if (((std::get<ObjectHandle<Rest>>(set) != nullptr) && ...)) {
                    result.emplace_back(std::move(set));
                }
            }

        } else if constexpr (ComponentType<T>) {
            const auto descriptor = TypeDescriptor::getTypeDescriptor<T>();

            auto c = std::ranges::find_if(components, [descriptor](auto const &list) {
                return list.first == descriptor || TypeDescriptor::isSuperType(list->first, descriptor);
            });

            if (c != components.end()) {
                for (auto const &[id, component] : c->second) {
                    auto set = std::make_tuple(static_handle_cast<T>(component), getComponent<Rest>(id)...);

                    if (((std::get<ObjectHandle<Rest>>(set) != nullptr) && ...)) {
                        result.emplace_back(std::move(set));
                    }
                }
            }
        }

        return result;
    }
}

#endif //CPPGAME_SCENE_IMPL_HPP
