#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "renderable.hpp"
#include "maths/rectangle_2d.hpp"
#include "memory/type_descriptor.hpp"

namespace cppengine {
    class Sprite : public Renderable {
    private:
        // get the sheet from the sprite sheet component
        Rectangle2D frame;
    public:

    };
}

DECL_POLY_TYPE(cppengine::Sprite, cppengine::Renderable)

#endif
