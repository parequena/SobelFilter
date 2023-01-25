#ifndef SOBEL_FILTER_HPP
#define SOBEL_FILTER_HPP

#include <array>
#include <cstdint>
#include <vector>

#include <algorithm>
#include <execution>

#include <opencv4/opencv2/core.hpp>

/*
1 0 -1
2 0 -2
1 0 -1

A B C D E F
G H I J K L
M N Ñ O P Q
R S T U V W
*/

struct SobelFilter
{
  static constexpr std::array<int, 9> kernel_x{1, 0, -1, 2, 0, -2, 1, 0, -1};
  static constexpr std::array<int, 9> kernel_y{1, 2, 1, 0, 0, 0, -1, -2, -1};

  inline static cv::Mat apply(cv::Mat const &img)
  {
    cv::Mat ret = cv::Mat::zeros(img.size(), img.type());
    int const rows = img.rows;
    int const cols = img.cols;

    for (int i{1}; i < rows - 1; ++i)
    {
      for (int j{1}; j < cols - 1; ++j)
      {
        // clang-format off
        int const x = kernel_x[0] * img.at<std::uint8_t>(i - 1, j - 1) + 
                            kernel_x[1] * img.at<std::uint8_t>(i - 1, j - 0) + 
                            kernel_x[2] * img.at<std::uint8_t>(i - 1, j + 1) + 
            
                            kernel_x[3] * img.at<std::uint8_t>(i - 0, j - 1) + 
                            kernel_x[4] * img.at<std::uint8_t>(i - 0, j - 0) + 
                            kernel_x[5] * img.at<std::uint8_t>(i - 0, j + 1) + 
            
                            kernel_x[6] * img.at<std::uint8_t>(i + 1, j - 1) + 
                            kernel_x[7] * img.at<std::uint8_t>(i + 1, j - 0) + 
                            kernel_x[8] * img.at<std::uint8_t>(i + 1, j + 1);

            int const y = kernel_y[0] * img.at<std::uint8_t>(i - 1, j - 1) + 
                            kernel_y[1] * img.at<std::uint8_t>(i - 1, j - 0) + 
                            kernel_y[2] * img.at<std::uint8_t>(i - 1, j + 1) + 
            
                            kernel_y[3] * img.at<std::uint8_t>(i - 0, j - 1) + 
                            kernel_y[4] * img.at<std::uint8_t>(i - 0, j - 0) + 
                            kernel_y[5] * img.at<std::uint8_t>(i - 0, j + 1) + 
            
                            kernel_y[6] * img.at<std::uint8_t>(i + 1, j - 1) + 
                            kernel_y[7] * img.at<std::uint8_t>(i + 1, j - 0) + 
                            kernel_y[8] * img.at<std::uint8_t>(i + 1, j + 1);
        // clang-format on

        int const sum = int(std::sqrt(x * x + y * y));
        ret.at<std::uint8_t>(i, j) = sum > 255 ? 255U : std::uint8_t(sum);
      }
    }

    return ret;
  }

  inline static cv::Mat apply_opm(cv::Mat const &img)
  {
    cv::Mat ret = cv::Mat::zeros(img.size(), img.type());
    int const rows = img.rows;
    int const cols = img.cols;

#pragma omp parallel
#pragma omp for
    for (int i = 1; i < rows - 1; ++i)
    {
      for (int j{1}; j < cols - 1; ++j)
      {
        // clang-format off
        int const x = kernel_x[0] * img.at<std::uint8_t>(i - 1, j - 1) + 
                            kernel_x[1] * img.at<std::uint8_t>(i - 1, j - 0) + 
                            kernel_x[2] * img.at<std::uint8_t>(i - 1, j + 1) + 
            
                            kernel_x[3] * img.at<std::uint8_t>(i - 0, j - 1) + 
                            kernel_x[4] * img.at<std::uint8_t>(i - 0, j - 0) + 
                            kernel_x[5] * img.at<std::uint8_t>(i - 0, j + 1) + 
            
                            kernel_x[6] * img.at<std::uint8_t>(i + 1, j - 1) + 
                            kernel_x[7] * img.at<std::uint8_t>(i + 1, j - 0) + 
                            kernel_x[8] * img.at<std::uint8_t>(i + 1, j + 1);

            int const y = kernel_y[0] * img.at<std::uint8_t>(i - 1, j - 1) + 
                            kernel_y[1] * img.at<std::uint8_t>(i - 1, j - 0) + 
                            kernel_y[2] * img.at<std::uint8_t>(i - 1, j + 1) + 
            
                            kernel_y[3] * img.at<std::uint8_t>(i - 0, j - 1) + 
                            kernel_y[4] * img.at<std::uint8_t>(i - 0, j - 0) + 
                            kernel_y[5] * img.at<std::uint8_t>(i - 0, j + 1) + 
            
                            kernel_y[6] * img.at<std::uint8_t>(i + 1, j - 1) + 
                            kernel_y[7] * img.at<std::uint8_t>(i + 1, j - 0) + 
                            kernel_y[8] * img.at<std::uint8_t>(i + 1, j + 1);
        // clang-format on

        int const sum = int(std::sqrt(x * x + y * y));
        ret.at<std::uint8_t>(i, j) = sum > 255 ? 255U : std::uint8_t(sum);
      }
    }

    return ret;
  }

  inline static cv::Mat apply_stl(cv::Mat const &img)
  {
    cv::Mat ret = cv::Mat::zeros(img.size(), img.type());
    int const rows = img.rows;
    int const cols = img.cols;

    std::size_t vSize{std::size_t(rows) - 2};
    std::vector<int> rowsIdx(vSize);
    std::iota(rowsIdx.begin(), rowsIdx.end(), 1);

    std::for_each(std::execution::par_unseq, rowsIdx.begin(), rowsIdx.end(), [&](int const i)
                  {
      for (int j{1}; j < cols - 1; ++j)
      {
        // clang-format off
        int const x = kernel_x[0] * img.at<std::uint8_t>(i - 1, j - 1) + 
                      kernel_x[1] * img.at<std::uint8_t>(i - 1, j - 0) + 
                      kernel_x[2] * img.at<std::uint8_t>(i - 1, j + 1) + 
      
                      kernel_x[3] * img.at<std::uint8_t>(i - 0, j - 1) + 
                      kernel_x[4] * img.at<std::uint8_t>(i - 0, j - 0) + 
                      kernel_x[5] * img.at<std::uint8_t>(i - 0, j + 1) + 
      
                      kernel_x[6] * img.at<std::uint8_t>(i + 1, j - 1) + 
                      kernel_x[7] * img.at<std::uint8_t>(i + 1, j - 0) + 
                      kernel_x[8] * img.at<std::uint8_t>(i + 1, j + 1);

        int const y = kernel_y[0] * img.at<std::uint8_t>(i - 1, j - 1) + 
                      kernel_y[1] * img.at<std::uint8_t>(i - 1, j - 0) + 
                      kernel_y[2] * img.at<std::uint8_t>(i - 1, j + 1) + 
      
                      kernel_y[3] * img.at<std::uint8_t>(i - 0, j - 1) + 
                      kernel_y[4] * img.at<std::uint8_t>(i - 0, j - 0) + 
                      kernel_y[5] * img.at<std::uint8_t>(i - 0, j + 1) + 
      
                      kernel_y[6] * img.at<std::uint8_t>(i + 1, j - 1) + 
                      kernel_y[7] * img.at<std::uint8_t>(i + 1, j - 0) + 
                      kernel_y[8] * img.at<std::uint8_t>(i + 1, j + 1);
        // clang-format on

        int const sum = int(std::sqrt(x * x + y * y));
        ret.at<std::uint8_t>(i, j) = sum > 255 ? 255U : std::uint8_t(sum);
      } });

    return ret;
  }
};

#endif /* SOBEL_FILTER_HPP */
