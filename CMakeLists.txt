cmake_minimum_required(VERSION 3.20)
project(Backend)

set(CMAKE_CXX_STANDARD 20)

# Create a header-only library for stb_image
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE stb_image/)

# stb_image is header-only, implementation is in stb_image_impl.cpp

add_library(ImageHandler STATIC src/Image.cpp src/stb_image_impl.cpp)

target_include_directories(ImageHandler PUBLIC include/ stb_image/)

add_executable(MAIN main.cpp)
target_link_libraries(MAIN PRIVATE ImageHandler stb_image)