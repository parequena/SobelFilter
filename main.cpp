#include <iostream>
#include <string>

#include <Image.hpp>
#include <SobelFilter.hpp>

static constexpr auto k_assets_path{"../assets/"};
static constexpr auto df_nTimes{1};

template <typename func_t>
void benchmark(func_t func)
{
    auto start = std::chrono::steady_clock::now();
    for (auto i{0}; i < df_nTimes; ++i)
    {
        func();
    }
    std::chrono::duration<double, std::milli> diff = std::chrono::steady_clock::now() - start;
    std::cout << "Time elapsed = " << diff.count() << "ms.\n";
}

void test(std::string const &name)
{
    std::cout << "Name: " << name << '\n';
    std::string const image_path_1{k_assets_path + name};
    Image im1{image_path_1};
    cv::Mat sb{}, sb_omp{}, sb_stl{};

    // clang-format off
    benchmark(
        [&]() { sb = SobelFilter::apply(im1.image()); }
    );

    benchmark(
        [&]() { sb_omp = SobelFilter::apply_opm(im1.image()); }
    );

    benchmark(
        [&]() { sb_stl = SobelFilter::apply_stl(im1.image()); }
    );
    // clang-format on
    std::cout << "\n\n\n";
}

int main()
{
    std::string const image_name_1{"valve.png"};
    std::string const image_name_2{"new_york.jpg"};

    test(image_name_1);
    test(image_name_2);

    return EXIT_SUCCESS;
}