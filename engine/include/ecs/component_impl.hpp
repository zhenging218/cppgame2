#ifndef COMPONENT_IMPL_HPP
#define COMPONENT_IMPL_HPP

namespace cppengine {
    template<typename T, typename U>
    void Component::addEventListener(void (T::*handler)(U const &)) {
        std::uint64_t id = SceneManager::getInstance().getEntityOfComponent(this);

        EventDispatcher<U>::getInstance().addEventListener(id, static_cast<T*>(this), handler);
    }

    template<typename T, typename U>
    void Component::removeEventListener(void (T::*handler)(U const &)) {
        std::uint64_t id = SceneManager::getInstance().getEntityOfComponent(this);

        EventDispatcher<U>::getInstance().removeEventListener(id, static_cast<T*>(this), handler);
    }
}

#endif