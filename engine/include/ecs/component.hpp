#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include "scene_manager.hpp"
#include "events/event_dispatcher.hpp"

namespace cppengine {
    struct ComponentDescriptor;
    class Scene;
    class GameObject;
    class TypeDescriptor;

    class Component {
    private:
        friend class Scene;
        friend class SceneManager;
        ComponentDescriptor const *descriptor;
    protected:
        Component() = default;

        GameObject createGameObject() const;

        template <typename T, typename U>
        void addEventListener(void (T::*handler)(U const &));

        template <typename T, typename U>
        void removeEventListener(void (T::*handler)(U const &));
    public:

        GameObject getGameObject() const;
        void destroyGameObject(GameObject const &gameObject) const;

        virtual ~Component() = 0;
    };

    inline Component::~Component() = default;
}

#endif