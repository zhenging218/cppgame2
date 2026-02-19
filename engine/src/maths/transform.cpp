#include "maths/transform.hpp"

#include <algorithm>

namespace cppengine {
    namespace {
        Matrix4x4 combineComponents(Vector3 const &position, Quaternion const &rotation, Vector3 const &scale) {
            Matrix4x4 rotationMatrix = Matrix4x4{ rotation };

            Matrix4x4 translationMatrix = Matrix4x4{
                1,      0,       0, position.x,
                0,      1,       0, position.y,
                0,      0,       1, position.z,
                0,      0,       0,          1
            };

            Matrix4x4 scaleMatrix = Matrix4x4 {
                scale.x,       0,       0,       0,
                      0, scale.y,       0,       0,
                      0,       0, scale.z,       0,
                      0,       0,       0,       1
            };

            return translationMatrix * rotationMatrix * scaleMatrix;
        }
    }

    Transform::Transform() :
    position(0, 0, 0),
    rotation(Quaternion::identity),
    scale(1, 1, 1), matrix(Matrix4x4::identity), parent(nullptr), children(), dirty(false) {}

    void Transform::propagateChanges() {
        std::for_each(children.begin(), children.end(), [](Transform *child) {
            child->dirty = true;
        });
        dirty = false;
    }

    void Transform::updateMatrix() {
        // rebuild matrix from properties, then parent matrix * matrix (if parent exist)
        matrix = combineComponents(position, rotation, scale);

        if(parent != nullptr) {
            matrix = parent->matrix * matrix;
        }
    }

    Matrix4x4 const &Transform::getMatrix() {
        if(parent != nullptr && parent->dirty) {
            // if parents are dirty, propagate their changes to this depth
            parent->propagateChanges();
            updateMatrix();
        } else if(dirty) {
            updateMatrix();
        }

        dirty = false;

        return matrix;
    }

    Transform *Transform::getParent() {
        return parent;
    }

    Transform const *Transform::getParent() const {
        return parent;
    }

    std::vector<Transform *> Transform::getChildren() {
        return children;
    }

    std::vector<Transform const *> Transform::getChildren() const {
        return std::vector<Transform const *>(children.begin(), children.end());
    }

    void Transform::setParent(Transform *newParent) {
        if(parent != newParent && newParent != this) {
            if(parent != nullptr) {
                parent->removeChild(*this);
                dirty = true;
            }

            parent = newParent;

            if(newParent != nullptr) {
                newParent->addChild(*this);
                dirty = true;
            }
        }
    }

    void Transform::addChild(Transform &newChild) {
        if(std::find_if(children.begin(), children.end(), [&newChild](Transform *child) { return &newChild == child; }) == children.end()) {
            newChild.parent = this;
            children.push_back(&newChild);
        }
    }

    void Transform::removeChild(Transform &childToRemove) {
        auto result = std::find_if(children.begin(), children.end(), [&childToRemove](Transform *child) { return &childToRemove == child; });

        if(result != children.end()) {
            childToRemove.parent = nullptr;
            children.erase(result);
        }
    }

    Vector3 const &Transform::getPosition() const {
        return position;
    }

    void Transform::setPosition(Vector3 const &p) {
        position = p;
        dirty = true;
    }

    Quaternion const &Transform::getRotation() const {
        return rotation;
    }

    void Transform::setRotation(Quaternion const &r) {
        rotation = r;
        dirty = true;
    }

    Vector3 const &Transform::getScale() const {
        return scale;
    }

    void Transform::setScale(Vector3 const &s) {
        scale = s;
        dirty = true;
    }
}