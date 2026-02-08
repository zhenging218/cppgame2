#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include "memory/object_handle.hpp"

namespace cppengine {
    class Component {
    private:
        friend class Scene;
        ObjectHandle<Scene> scene;
    public:

        virtual ~Component() = 0;
    };

}

#endif