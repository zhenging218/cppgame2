#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include "memory/object_handle.hpp"

namespace cppengine {
    class Scene;
    class GameObject;

    class Component {
    private:
        friend class Scene;
        TypeDescriptor const *descriptor;
        ObjectHandle<Scene> scene;

    protected:

        GameObject getGameObject() const;

    public:

        virtual ~Component() = 0;
    };

}

#endif