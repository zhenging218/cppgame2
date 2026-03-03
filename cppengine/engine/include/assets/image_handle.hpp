#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdint>

namespace cppengine
{
    class ImageHandle
    {
    public:
        using image_data_type = std::uint8_t;
        using const_image_data_type = const image_data_type;
        using image_data_pointer = image_data_type *;
        using image_data_const_pointer = const_image_data_type *;

        virtual ~ImageHandle() = 0;

        virtual image_data_type &operator[](int index) = 0;
        virtual const_image_data_type&operator[](int index) const = 0;

        virtual image_data_pointer getData() = 0;
        virtual image_data_const_pointer getData() const = 0;
    };

    inline ImageHandle::~ImageHandle() = default;
}

#endif