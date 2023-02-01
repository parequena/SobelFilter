#include <Image.hpp>

#include <exception>
#include <array>
#include <numeric>
#include <algorithm>
#include <execution>

Image::Image(std::filesystem::path const &image_path)
    : image_path_{image_path.string()}
{
    // Load image.
    cv::Mat img = cv::imread(image_path.string(), cv::IMREAD_COLOR);

    if (img.empty())
    {
        throw std::invalid_argument("Image: " + image_path.string() + " doesn't exists!\n");
    }

    cv::cvtColor(img, image_, cv::COLOR_BGR2GRAY);
    std::cout << "This image has been converted into grayscale!\n";
}

void Image::plot() const noexcept
{
    cv::imshow(image_path_, image_);
    cv::waitKey(0);
}