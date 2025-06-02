#pragma once
#include <cstdint>
#include <memory>
#include <span>
#include "Size.h"

namespace img {

enum class PixelFormat {
    RGB,
    BGR,
    RGBA,
    BGRA,
};

enum class FirstRowIs {
    Bottom,
    Top,
};

/// An Image is an array of pixel channels
/// The pixels are stored sequentially, something like [255, 200, 100, 255, 120, 30, 80, 255, ...] where (255, 200, 100, 255) would be the first pixel and (120, 30, 80, 255) the second pixel
/// The order in which the pixels are stored is up to the user to decide
struct Image {
public:
    /// NB: The Image takes ownership of the data pointer
    /// It is your responsibility to make sure that size and pixel_format properly match what is in data
    /// Alternatively you can use img::load() to create an Image
    Image(Size size, PixelFormat pixel_format, FirstRowIs row_order, uint8_t* data)
        : _size{size}, _pixel_format{pixel_format}, _row_order{row_order}, _data{data}
    {
    }

    /// Returns the size of the image (in pixels)
    Size size() const { return _size; }

    /// Returns the width of the image (in pixels)
    Size::DataType width() const { return size().width(); }

    /// Returns the height of the image (in pixels)
    Size::DataType height() const { return size().height(); }

    /// Returns the number of channels per pixel (e.g. 4 if the format is RGBA)
    auto channels_count() const -> size_t;
    auto pixel_format() const -> PixelFormat { return _pixel_format; }
    auto row_order() const -> FirstRowIs { return _row_order; }

    std::span<uint8_t>       data_span() { return {data(), data_size()}; }
    std::span<uint8_t const> data_span() const { return {data(), data_size()}; }

    /// Returns a pointer to the beginning of the data array
    uint8_t* data() { return _data.get(); }

    /// Returns a pointer to the beginning of the data array
    uint8_t const* data() const { return _data.get(); }

    /// Returns the number of elements in the data array
    size_t data_size() const { return size().pixels_count() * channels_count(); }

private:
    Size                       _size;
    PixelFormat                _pixel_format;
    FirstRowIs                 _row_order;
    std::unique_ptr<uint8_t[]> _data; // NOLINT(*avoid-c-arrays)
};

} // namespace img