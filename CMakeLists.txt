cmake_minimum_required(VERSION 3.0.0)
project(SobelFilter VERSION 0.1.0)

set(ALL_CLANG_WARNINGS "-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough")
set(ALL_GCC_WARNINGS "${ALL_CLANG_WARNINGS} -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${ALL_CLANG_WARNINGS} -Werror")
else()
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${ALL_GCC_WARNINGS} -Werror")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add sources.
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(SobelFilter ${SRC_FILES} main.cpp)

# Add OpenCV.
find_package( OpenCV REQUIRED )
find_package(TBB REQUIRED)
find_package(OpenMP REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( SobelFilter TBB::tbb ${OpenCV_LIBS} OpenMP::OpenMP_CXX)

# Add include as directoy.
target_include_directories(SobelFilter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)