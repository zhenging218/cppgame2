#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include "memory/object_handle.hpp"

namespace cppengine {
    class Scene;
    class GameObject;
    class TypeDescriptor;

    class Component {
    private:
        friend class Scene;
        TypeDescriptor const *descriptor;
    protected:
        Component() = default;

        GameObject createGameObject() const;

    public:

        GameObject getGameObject() const;
        virtual void init();
        virtual void update();
        virtual void teardown();


        virtual ~Component() = 0;
    };

    inline Component::~Component() = default;
}

#endif