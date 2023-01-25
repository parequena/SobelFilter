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

cv::Mat Image::sobelPablo3() const noexcept
{
    constexpr std::array<std::int8_t, 9> kernel_x{1, 0, -1, 2, 0, -2, 1, 0, -1};
    constexpr std::array<std::int8_t, 9> kernel_y{1, 2, 1, 0, 0, 0, -1, -2, -1};

    int const rows = image_.rows;
    int const cols = image_.cols;

    cv::Mat mat = image_;
    cv::Mat ret = cv::Mat::zeros(mat.size(), mat.type());

    std::vector<int>
        rowsInd(std::size_t(rows - 1));
    std::iota(rowsInd.begin(), rowsInd.end(), 1);

    std::for_each(std::execution::par_unseq, rowsInd.begin(), rowsInd.end(), [&](int const i)
                  {
        for (int j{1}; j < cols - 1; ++j)
        {
            int const x_0 = kernel_x[0] * mat.at<std::uint8_t>(i - 1, j - 1) + 
                            kernel_x[1] * mat.at<std::uint8_t>(i - 1, j - 0) + 
                            kernel_x[2] * mat.at<std::uint8_t>(i - 1, j + 1) + 
            
                            kernel_x[3] * mat.at<std::uint8_t>(i - 0, j - 1) + 
                            kernel_x[4] * mat.at<std::uint8_t>(i - 0, j - 0) + 
                            kernel_x[5] * mat.at<std::uint8_t>(i - 0, j + 1) + 
            
                            kernel_x[6] * mat.at<std::uint8_t>(i + 1, j - 1) + 
                            kernel_x[7] * mat.at<std::uint8_t>(i + 1, j - 0) + 
                            kernel_x[8] * mat.at<std::uint8_t>(i + 1, j + 1);

            int const y_0 = kernel_y[0] * mat.at<std::uint8_t>(i - 1, j - 1) + 
                            kernel_y[1] * mat.at<std::uint8_t>(i - 1, j - 0) + 
                            kernel_y[2] * mat.at<std::uint8_t>(i - 1, j + 1) + 
            
                            kernel_y[3] * mat.at<std::uint8_t>(i - 0, j - 1) + 
                            kernel_y[4] * mat.at<std::uint8_t>(i - 0, j - 0) + 
                            kernel_y[5] * mat.at<std::uint8_t>(i - 0, j + 1) + 
            
                            kernel_y[6] * mat.at<std::uint8_t>(i + 1, j - 1) + 
                            kernel_y[7] * mat.at<std::uint8_t>(i + 1, j - 0) + 
                            kernel_y[8] * mat.at<std::uint8_t>(i + 1, j + 1);

            int const sum = int(std::sqrt(x_0 * x_0 + y_0 * y_0));
            ret.at<std::uint8_t>(i, j) = sum > 255 ? 255U : std::uint8_t(sum);
        } });

    return ret;
}