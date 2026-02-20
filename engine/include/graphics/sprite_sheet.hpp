#ifndef SPRITE_SHEET_HPP
#define SPRITE_SHEET_HPP
#include "ecs/component.hpp"
#include "maths/rectangle_2d.hpp"
#include "texture.hpp"

namespace cppengine {
    class SpriteSheet : public Component {
    private:
        Texture texture;
        int rows, columns;
    public:

        SpriteSheet() = default;
        SpriteSheet(SpriteSheet const &) = default;
        SpriteSheet &operator=(SpriteSheet const &) = default;

        void setTexture(Texture const &other);
        Texture getTexture() const;

        void setDimensions(int rows_, int columns_);

        int getRows() const;
        int getColumns() const;

        Rectangle2D getCellAt(int row_, int column_) const;
    };
}

#endif