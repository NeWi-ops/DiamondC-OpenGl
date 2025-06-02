#include "Image.h"

namespace img {

auto Image::channels_count() const -> size_t
{
    switch (_pixel_format)
    {
    case PixelFormat::RGB:
    case PixelFormat::BGR:
        return 3;
    case PixelFormat::RGBA:
    case PixelFormat::BGRA:
        return 4;
    }
    assert(false);
    return 0;
}

} // namespace img