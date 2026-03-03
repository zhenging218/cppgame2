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

        ImageHandle();

        ImageHandle(std::string const &name_,
            image_data_pointer data_,
            int width_,
            int height_,
            int channels_);

        ImageHandle(ImageHandle const &other);
        ImageHandle(ImageHandle &&other) noexcept;
        ImageHandle &operator=(ImageHandle const &other);
        ImageHandle &operator=(ImageHandle &&other) noexcept;
        ~ImageHandle();

        image_data_type &operator[](int index);
        const_image_data_type&operator[](int index) const;

        explicit operator image_data_pointer();
        explicit operator image_data_const_pointer() const;

    };
}

#endif