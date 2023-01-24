#include <iostream>
#include <string>

#include <Image.hpp>
#include <SobelFilter.hpp>

static constexpr auto k_assets_path{"../assets/"};

int main()
{
    std::string const image_name{"valve.png"};
    std::string const image_path{k_assets_path + image_name};

    Image im1{image_path};
    // im1.plot();
    Image::Sobel_OpenCV(image_path);

    // Image im2 = SobelFilter::apply(im1);

    return EXIT_SUCCESS;
}