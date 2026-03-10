#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "renderable.hpp"
#include "maths/rectangle_2d.hpp"
#include "../reflection/type_descriptor.hpp"

namespace cppengine {
    class Sprite : public Renderable {
    private:
        // get the sheet from the sprite sheet component
        Rectangle2D frame;
    public:

    };
}

DECL_TYPE_DESCRIPTOR(cppengine::Sprite, cppengine::Renderable)


#endif
