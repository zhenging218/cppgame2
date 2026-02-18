#ifndef SPRITE_SHEET_HPP
#define SPRITE_SHEET_HPP
#include "ecs/component.hpp"
#include "texture_handle.hpp"

namespace cppengine {
    class SpriteSheet : public Component {
    private:
        TextureHandle texture;
        int rows, columns;
    public:

        SpriteSheet() = default;
        SpriteSheet(SpriteSheet const &) = default;
        SpriteSheet &operator=(SpriteSheet const &) = default;

        void setTexture(TextureHandle const &other);
        TextureHandle getTexture() const;

        void setDimensions(int rows_, int columns_);

        int getRows() const;
        int getColumns() const;

        Rectangle2D getCellAt(int row_, int column_) const;
    };
}

#endif