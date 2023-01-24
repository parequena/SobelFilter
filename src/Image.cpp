#include <Image.hpp>

#include <exception>

Image::Image(std::filesystem::path const &image_path)
    : image_path_{image_path.string()}
{
    // Load image.
    cv::Mat img = cv::imread(image_path.string(), cv::IMREAD_COLOR);

    if (img.empty())
    {
        throw std::invalid_argument("Image: " + image_path.string() + " doesn't exists!\n");
    }

    cv::Mat im_gray{};
    cv::cvtColor(img, im_gray, cv::COLOR_BGR2GRAY);
    std::cout << "This image has been converted into grayscale!\n";

    rows_ = std::uint32_t(im_gray.rows);
    cols_ = std::uint32_t(im_gray.cols);
    type_ = im_gray.type();
    data_ = std::vector<std::uint8_t>{im_gray.begin<std::uint8_t>(), im_gray.end<std::uint8_t>()};
}

Image::Image(std::uint32_t rows, std::uint32_t cols, int type, std::vector<std::uint8_t> const &image_data) noexcept
    : rows_{rows}, cols_{cols}, type_{type}, image_path_{"Created from data."}, data_{image_data}
{
    std::cout << "COPY\n";
}

void Image::plot() const noexcept
{
    // Never construct a mat this way! // reinterpret_cast normally it's a undefined behaivour!
    cv::Mat mat{int(rows_), int(cols_), type_, reinterpret_cast<void *>(const_cast<std::uint8_t *>(data_.data()))};
    cv::imshow(image_path_, mat);
    cv::waitKey(0);
}
