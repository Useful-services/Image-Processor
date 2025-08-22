cmake_minimum_required(VERSION 3.20)
project(Backend)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows-specific settings
if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
    add_definitions(-D_WIN32_WINDOWS=0x0601)
endif()

# Включаем CPM для загрузки зависимостей
include(${CMAKE_CURRENT_SOURCE_DIR}/Crow/cmake/CPM.cmake)

# Загружаем asio через CPM
CPMAddPackage(
    NAME asio
    GITHUB_REPOSITORY chriskohlhoff/asio
    GIT_TAG asio-1-28-0
)

# Включаем Crow с настройками для standalone asio
set(CROW_USE_BOOST OFF CACHE BOOL "" FORCE)
set(CROW_ENABLE_SSL OFF CACHE BOOL "" FORCE)
set(CROW_ENABLE_COMPRESSION OFF CACHE BOOL "" FORCE)
set(CROW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CROW_BUILD_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(Crow/)

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE stb_image/)

add_library(ImageHandler STATIC src/Image.cpp src/stb_image_impl.cpp src/ImageEncoder.cpp)
add_library(WebHandler src/ApiListener.cpp)

target_include_directories(ImageHandler PUBLIC include/ stb_image/)
target_include_directories(WebHandler PUBLIC include/)
target_link_libraries(WebHandler PUBLIC ImageHandler Crow::Crow)

add_executable(WEB_SERVER web_server.cpp)
target_link_libraries(WEB_SERVER PRIVATE stb_image WebHandler)