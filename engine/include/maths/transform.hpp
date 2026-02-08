#pragma once

#include <vector>

#include "maths/quaternion.hpp"
#include "maths/vector3.hpp"
#include "maths/matrix4x4.hpp"

// TODO: reference this 3D game engine transform hierarchy in java and impl in c++
//       https://github.com/BennyQBD/3DGameEngine/blob/master/src/com/base/engine/core/Transform.java

namespace cppengine {
    class Transform {
    private:
        Vector3 position;
        Quaternion rotation;
        Vector3 scale;

        Matrix4x4 matrix;

        Transform * parent;
        std::vector<Transform *> children;

        bool dirty;

        void propagateChanges();
        void updateMatrix();
    public:
        Transform();
        Transform(Transform const &other) = delete;
        Transform &operator=(Transform const &other) = delete;

        Transform *getParent();
        Transform const *getParent() const;
        std::vector<Transform *> getChildren();
        std::vector<Transform const *> getChildren() const;

        void setParent(Transform *newParent);
        void addChild(Transform &newChild);
        void removeChild(Transform &childToRemove);

        Vector3 const &getPosition() const;
        void setPosition(Vector3 const &p);

        Quaternion const &getRotation() const;
        void setRotation(Quaternion const &r);

        Vector3 const &getScale() const;
        void setScale(Vector3 const &s);

        Matrix4x4 const &getMatrix();
    };
}