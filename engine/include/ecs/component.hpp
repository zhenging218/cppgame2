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

        GameObject getGameObject() const;
        GameObject createGameObject() const;

    public:

        virtual void init() = 0;
        virtual void update() = 0;


        virtual ~Component() = default;
    };

}

#endif