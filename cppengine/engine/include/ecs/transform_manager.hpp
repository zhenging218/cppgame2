//
// Created by Admin on 31/10/2026.
//

#ifndef TRANSFORM_MANAGER_HPP
#define TRANSFORM_MANAGER_HPP

#include "maths/transform.hpp"

namespace cppengine {

    class TransformManager {
    private:
        ObjectAllocator<Transform> allocator;
    public:
        ObjectHandle<Transform> createTransform();
    };

}

#endif //TRANSFORM_MANAGER_HPP
