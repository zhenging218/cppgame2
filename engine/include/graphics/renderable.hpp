#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "ecs/component.hpp"
#include "maths/transform.hpp"

namespace cppengine {
    class DrawContext;

    class Renderable : public Component {
    private:

    protected:
        ObjectHandle<Transform> transform;

    public:
        void init() override;

        virtual Vector3 const *getVertices() const = 0;
        virtual std::size_t getVertexCount() const = 0;
        virtual std::size_t const *getIndices() const = 0;
        virtual std::size_t getIndexCount() const = 0;

        // todo: implement this after shader
        // virtual Vector3 const *getNormals() const = 0;

        ~Renderable() override = 0;
    };

    inline Renderable::~Renderable() = default;
}

#endif