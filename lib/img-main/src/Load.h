#pragma once
#include <filesystem>
#include <optional>
#include <string>
#include "Image.h"
#include "tl/expected.hpp"

namespace img {

/// Loads an Image from a file; might return an error message, e.g. if the fail does not exist
/// @param file_path The path to the image: something like "icons/myImage.png"
/// @param desired_channels_count The number of channels that you want the image to have. For example if your file contains only RGB but you want RGBA, this will add a 4th component of 255 to each pixel. You can also set this to std::nullopt to use the same channels count as what is in the file.
/// @param desired_row_order By default we use the OpenGL convention: the first row will be the bottom of the image. You can set `desired_row_order` to  img::FirstRowIs::Top if you want the first row to be the top of the image.
auto load(std::filesystem::path const& file_path, std::optional<int> desired_channels_count = 4, img::FirstRowIs desired_row_order = img::FirstRowIs::Bottom) -> tl::expected<Image, std::string>;

} // namespace img
