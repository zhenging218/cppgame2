#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include "memory/object_handle.hpp"

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

    public:

        GameObject getGameObject() const;


        virtual ~Component() = 0;
    };

    inline Component::~Component() = default;
}

#endif