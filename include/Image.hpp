#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <opencv2/opencv.hpp>
#include <filesystem>
#include <cstdint>

struct Image
{
    explicit Image(std::filesystem::path const &image_path);
    explicit Image(std::uint32_t rows, std::uint32_t cols, int type, std::vector<std::uint8_t> const &image_data) noexcept;
    void plot() const noexcept;

    inline cv::Mat image() const noexcept { return image_; }

private:
    std::string image_path_{};
    cv::Mat image_{};
};

#endif /* IMAGE_HPP */
