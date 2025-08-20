cmake_minimum_required(VERSION 3.20)
project(Backend)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/boostorg/asio/tree/boost-1.89.0
  GIT_TAG boost-1.89.0
)
FetchContent_MakeAvailable(asio)

add_subdirectory(Crow/)

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE stb_image/)

add_library(ImageHandler STATIC src/Image.cpp src/stb_image_impl.cpp)

target_include_directories(ImageHandler PUBLIC include/ stb_image/)

add_executable(MAIN main.cpp)
target_link_libraries(MAIN PRIVATE ImageHandler stb_image)