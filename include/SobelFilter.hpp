#ifndef SOBEL_FILTER_HPP
#define SOBEL_FILTER_HPP

#include <Image.hpp>

#include <array>
#include <cstdint>
#include <vector>

struct SobelFilter
{
    inline static constexpr std::array<std::int8_t, 9> kernel_x{1, 0, -1, 2, 0, -2, 1, 0, -1};
    inline static constexpr std::array<std::int8_t, 9> kernel_y{1, 2, 1, 0, 0, 0, -1, -2, -1};

    inline static Image apply(Image const &original_image)
    {
        auto const rows = original_image.rows();
        auto const cols = original_image.cols();
        auto const type = original_image.type();
        auto const data = original_image.data();

        return Image{rows, cols, type, data};
    }
};

#endif /* SOBEL_FILTER_HPP */
