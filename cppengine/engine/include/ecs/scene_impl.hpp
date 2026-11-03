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

    template<typename T, typename... Args> requires ComponentType<T>
    ObjectHandle<T> Scene::setupComponent(std::uint64_t entityId, Args &&... args) {
        const auto descriptor = TypeDescriptor::getTypeDescriptor<T>();

        if (entities.contains(entityId)) {
            auto &componentMap = componentsOfEntities[entityId];
            if (componentMap.contains(descriptor)) {
                return nullptr;
            }

            auto &entityMap = components[descriptor];

            auto component = static_handle_cast<Component>(componentManager->createComponent<T>(std::forward<Args>(args)...));
            component->setState(ComponentState::INITIALISING);
            component->setStamp(cycleGenerator->curr());
            component->setOwner(entityId);

            const auto [it, emplaced] = entityMap.emplace(std::make_pair(entityId, component));

            if (!emplaced) {
                throw R"(somehow created a new component even though a component of the type already exists)";
            }

            auto [descriptorIt, descriptorEmplaced] = componentMap.emplace(descriptor);

            if (!descriptorEmplaced) {
                throw R"(somehow created a new component even though a component of the type already exists)";
            }

            component->setScene(this);
            return static_handle_cast<T>(component);
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
            if (component->getState() == ComponentState::INITIALISING) {
                static_handle_cast<Component>(component)->setScene(this);
                static_handle_cast<Component>(component)->setState(ComponentState::ACTIVE);
                static_handle_cast<Component>(component)->setOwner(entityId);
            }
        } else {
            // get component but match exactly the type
            component = getComponentExact<T>(entityId);
        }

        return component;
    }

    template<typename T> requires ComponentType<T>
    ObjectHandle<T> Scene::getComponent(std::uint64_t entityId,
        std::unordered_map<std::uint64_t, ObjectHandle<Component>> const &candidates) const {
        const auto result = candidates.find(entityId);

        if (result != candidates.end()) {
            const auto state = result->second->getState();

            return state != ComponentState::DISPOSING && state != ComponentState::DISPOSED ? static_handle_cast<T>(result->second) : nullptr;
        }

        return nullptr;
    }

    template<typename T> requires ComponentType<T>
    ObjectHandle<T> Scene::getComponentExact(std::uint64_t entityId) const {
        const auto target = TypeDescriptor::getTypeDescriptor<T>();

        const auto & componentMap = componentsOfEntities.find(entityId);

        if (componentMap != componentsOfEntities.end()) {
            if (componentMap->second.contains(target)) {
                const auto candidates = components.find(target);

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

            if (const auto & componentMap = componentsOfEntities.find(entityId); componentMap != componentsOfEntities.end()) {
                auto firstMatch = std::ranges::find_if(componentMap->second, [target](auto const &descriptor) {
                    return TypeDescriptor::isSuperType(target, descriptor);
                });

                if (firstMatch != componentMap->second.end()) {
                    target = *firstMatch;

                    const auto candidates = components.find(target);

                    if (candidates != components.end()) {
                        return getComponent<T>(entityId, candidates->second);
                    }
                }
            }

            return nullptr;
        }
    }

    template<typename T, typename... Rest> requires TransformType<T> || ComponentType<T>
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

            for (const auto & componentMap : components) {
                if (componentMap.first == descriptor || TypeDescriptor::isSuperType(descriptor, componentMap.first)) {
                    auto const &c = componentMap.second;
                    for (auto const &[id, component] : c) {
                        if (component->getState() != ComponentState::DISPOSING && component->getState() != ComponentState::DISPOSED) {
                            auto set = std::make_tuple(static_handle_cast<T>(component), getComponent<Rest>(id)...);

                            if (((std::get<ObjectHandle<Rest>>(set) != nullptr) && ...)) {
                                result.emplace_back(std::move(set));
                            }
                        }
                    }
                }
            }
        }

        return result;
    }
}

#endif //CPPGAME_SCENE_IMPL_HPP
