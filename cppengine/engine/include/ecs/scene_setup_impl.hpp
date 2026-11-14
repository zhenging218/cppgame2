//
// Created by Admin on 2/11/2026.
//

#ifndef CPPGAME_SCENE_SETUP_IMPL_HPP
#define CPPGAME_SCENE_SETUP_IMPL_HPP

#include "ecs/ecs_concepts.hpp"
#include "ecs/scene_setup.hpp"

namespace cppengine {
    template<typename T, typename... Args> requires ComponentType<T>
    ComponentProxy<T> GameObjectProxy::addComponent(Args &&... args) const {
        return { id, sceneSetup->scene->setupComponent<T>(id, std::forward<Args>(args)...), sceneSetup };
    }

    template<typename T> requires ComponentType<T>
    ComponentProxy<T> GameObjectProxy::getComponent() const {
        return { sceneSetup->scene->getComponent<T>(id), sceneSetup };
    }

    template<typename T> requires ComponentType<T>
    ComponentProxy<T>::ComponentProxy(std::uint64_t owner_, ObjectHandle<T> component_, SceneSetup const *sceneSetup_)
        : owner(owner_), component(component_), sceneSetup(sceneSetup_) {

    }

    template<typename T> requires ComponentType<T>
    GameObjectProxy ComponentProxy<T>::getGameObject() const {
        const auto [id, name] = sceneSetup->scene->getEntity(owner);

        return { id, sceneSetup };
    }

    template<typename T> requires ComponentType<T>
    template<typename U>
    void ComponentProxy<T>::set(std::string_view fieldName, U &&value) const {
        using value_type = std::remove_cvref_t<U>;
        constexpr bool needs_string = !std::same_as<value_type, std::string> && std::is_convertible_v<U, std::string_view>;
        using lookup_type = std::conditional_t<needs_string, std::string, value_type>;

        auto fieldList = TypeDescriptor::getTypeDescriptor<T>()->getFields();
        auto it = std::ranges::find_if(fieldList, [&fieldName](auto const &descriptor) {
            return fieldName == descriptor.getName() && TypeDescriptor::getTypeDescriptor<lookup_type>() == descriptor.getTypeDescriptor();
        });

        if (it != fieldList.end()) {
            if constexpr (needs_string) {
                std::string stringValue(std::string_view{value});
                it->set(&(*component), &stringValue);
            } else {
                it->set(&(*component), &value);
            }

        } else {
            throw MismatchedFieldTypeOperation(
                TypeDescriptor::getTypeDescriptor<T>(),
                TypeDescriptor::getTypeDescriptor<lookup_type>(),
                fieldName);
        }
    }
}

#endif //CPPGAME_SCENE_SETUP_IMPL_HPP
