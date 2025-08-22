cmake_minimum_required(VERSION 3.20)
project(Backend)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(MQ_PORT=5556 MY_BUFFER_SIZE=1024)

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

set(ZMQ_BUILD_TESTS OFF)

CPMAddPackage(
    NAME ZeroMQ
    GITHUB_REPOSITORY Useful-services/SimpleLogger
    GIT_TAG eb62881473037c4eb97f939839a9f1d052187a71
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

file (GLOB_RECURSE IMG_HANDLING_SRC "src/image_handling/*.cpp")
file (GLOB_RECURSE WEB_HANDLING_SRC "src/web/*.cpp")
file (GLOB_RECURSE ROUTER_SRC       "src/backend_router/*.cpp")

add_library(ImageHandler STATIC ${IMG_HANDLING_SRC})
target_include_directories(ImageHandler PUBLIC include/image_handling stb_image/)

add_library(WebHandler STATIC ${WEB_HANDLING_SRC})
target_include_directories(WebHandler PUBLIC include/web include/custom_types)
target_link_libraries(WebHandler PUBLIC ImageHandler Crow::Crow ZMQ)

add_library(RouterLib STATIC ${ROUTER_SRC})
target_include_directories(RouterLib PUBLIC include/backend_router include/custom_types)
target_link_libraries(RouterLib PUBLIC ZMQ LOGGER)

add_executable(WEB_SERVER web_server.cpp)
target_link_libraries(WEB_SERVER PRIVATE stb_image WebHandler)

add_executable(ROUTER router.cpp)
target_link_libraries(ROUTER PRIVATE RouterLib)