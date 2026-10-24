#include "maths/transform.hpp"

#include <algorithm>

namespace cppengine {
    namespace {
        Matrix4x4 combineComponents(Vector3 const &position, Quaternion const &rotation, Vector3 const &scale_) {
            return translate(position) * rotate(rotation) * scale(scale_);
        }
    }

    bool Transform::isCycle(Transform const *target, Transform const *start) {
        while (start != nullptr) {
            if (start == target) {
                return true;
            }
            start = start->parent;
        }
        return false;
    }

    Transform::Transform() :
    position(0, 0, 0),
    rotation(Quaternion::identity),
    scale(1, 1, 1), matrix(Matrix4x4::identity), parent(nullptr), children(), dirty(false) {}

    void Transform::markDirty() {
        if (!dirty) {
            dirty = true;
            for (auto *child : children) {
                child->markDirty();
            }
        }
    }

    void Transform::updateMatrix() {
        matrix = combineComponents(position, rotation, scale);
        if (parent != nullptr) {
            matrix = parent->getMatrix() * matrix;
        }
    }

    Matrix4x4 const &Transform::getMatrix() {

        if (dirty) {
            updateMatrix();
            dirty = false;
        }

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
        if(parent != newParent && newParent != this && !isCycle(this, newParent)) {
            if(parent != nullptr) {
                parent->removeChild(*this);
            }

            if(newParent != nullptr) {
                newParent->addChild(*this);
            }
        }
    }

    void Transform::addChild(Transform &newChild) {
        if(std::find_if(children.begin(), children.end(), [&newChild](Transform *child) { return &newChild == child; }) == children.end()) {
            newChild.parent = this;
            children.push_back(&newChild);
            newChild.markDirty();
        }
    }

    void Transform::removeChild(Transform &childToRemove) {
        auto result = std::find_if(children.begin(), children.end(), [&childToRemove](Transform *child) { return &childToRemove == child; });

        if(result != children.end()) {
            childToRemove.parent = nullptr;
            children.erase(result);
            childToRemove.markDirty();
        }
    }

    Vector3 const &Transform::getPosition() const {
        return position;
    }

    void Transform::setPosition(Vector3 const &p) {
        position = p;
        markDirty();
    }

    Quaternion const &Transform::getRotation() const {
        return rotation;
    }

    void Transform::setRotation(Quaternion const &r) {
        rotation = r;
        markDirty();
    }

    Vector3 const &Transform::getScale() const {
        return scale;
    }

    void Transform::setScale(Vector3 const &s) {
        scale = s;
        markDirty();
    }

    Transform::~Transform() {
        setParent(nullptr);
        for (auto *child : children) {
            child->parent = nullptr;
            child->markDirty();
        }
    }
}
