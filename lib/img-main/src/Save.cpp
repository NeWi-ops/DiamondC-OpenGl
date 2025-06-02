#include "Save.h"
#include <stb_image/stb_image_write.h>

namespace img {

auto save_png(std::filesystem::path const& file_path, Image const& image, stbiw_SaveOptions const& options) -> bool
{
    return save_png(file_path, image.width(), image.height(), image.data(), image.channels_count(), image.row_order(), options);
}

auto save_png(
    std::filesystem::path const& file_path,
    Size::DataType               width,
    Size::DataType               height,
    const void*                  data,
    size_t                       channels_count,
    FirstRowIs                   row_order,
    stbiw_SaveOptions const&     options
) -> bool
{
    stbi_flip_vertically_on_write(row_order == FirstRowIs::Bottom ? 1 : 0);
    return 0 != stbi_write_png(file_path.string().c_str(), static_cast<int>(width), static_cast<int>(height), static_cast<int>(channels_count), data, 0, options);
}

auto save_png_to_string(Image const& image, stbiw_SaveOptions const& options) -> std::optional<std::string>
{
    return save_png_to_string(image.width(), image.height(), image.data(), image.channels_count(), image.row_order(), options);
}

static void write_to_string(void* context, void* data, int size)
{
    auto& str = *reinterpret_cast<std::string*>(context);
    str += std::string{reinterpret_cast<char*>(data), static_cast<size_t>(size)};
}

auto save_png_to_string(
    Size::DataType           width,
    Size::DataType           height,
    const void*              data,
    size_t                   channels_count,
    FirstRowIs               row_order,
    stbiw_SaveOptions const& options
) -> std::optional<std::string>
{
    stbi_flip_vertically_on_write(row_order == FirstRowIs::Bottom ? 1 : 0);

    std::string res{};
    if (0 != stbi_write_png_to_func(&write_to_string, &res, static_cast<int>(width), static_cast<int>(height), static_cast<int>(channels_count), data, 0, options))
        return res;
    return std::nullopt;
}

auto save_jpeg(std::filesystem::path const& file_path, Image const& image, stbiw_SaveOptions const& options) -> bool
{
    return save_jpeg(file_path.string().c_str(), image.width(), image.height(), image.data(), image.channels_count(), image.row_order(), options);
}

auto save_jpeg(
    std::filesystem::path const& file_path,
    Size::DataType               width,
    Size::DataType               height,
    void const*                  data,
    size_t                       channels_count,
    FirstRowIs                   row_order,
    stbiw_SaveOptions const&     options
) -> bool
{
    stbi_flip_vertically_on_write(row_order == FirstRowIs::Bottom ? 1 : 0);
    return 0 != stbi_write_jpg(file_path.string().c_str(), static_cast<int>(width), static_cast<int>(height), static_cast<int>(channels_count), data, 100, options);
}

} // namespace img