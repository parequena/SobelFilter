#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <opencv2/opencv.hpp>
#include <filesystem>
#include <cstdint>

struct Image
{
    Image(std::filesystem::path const &image_path);
    explicit Image(std::uint32_t rows, std::uint32_t cols, int type, std::vector<std::uint8_t> const &image_data) noexcept;
    void plot() const noexcept;

    constexpr auto rows() const noexcept -> std::uint32_t { return rows_; }
    constexpr auto cols() const noexcept -> std::uint32_t { return cols_; }
    constexpr auto type() const noexcept -> int { return type_; }
    constexpr auto data() const noexcept -> std::vector<std::uint8_t> const & { return data_; }

    inline static void Sobel_OpenCV(std::filesystem::path const &image_path)
    {
        // Load image.
        cv::Mat img = cv::imread(image_path.string(), cv::IMREAD_COLOR);

        if (img.empty())
        {
            throw std::invalid_argument("Image: " + image_path.string() + " doesn't exists!\n");
        }

        cv::Mat out_x{}, out_y{};
        cv::Sobel(img, out_x, CV_32F, 1, 0);
        cv::Sobel(img, out_y, CV_32F, 0, 1);

        cv::imshow(image_path, img);
        cv::imshow("Sobel-1-0: ", out_x);
        cv::imshow("Sobel-0-1: ", out_y);
        cv::waitKey(0);
    }

private:
    std::uint32_t rows_{};
    std::uint32_t cols_{};
    int type_{};
    std::string image_path_{};
    std::vector<std::uint8_t> data_{};
};

#endif /* IMAGE_HPP */
