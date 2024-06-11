cmake_minimum_required(VERSION 3.28)
project(ExtraLifeHelper)

set(CMAKE_CXX_STANDARD 23)

set (SOURCE_DIR_DEFINITION SOURCE_DIR="${PROJECT_SOURCE_DIR}")

# Specify the path to your Boost installation
if (MSVC)
    set(BOOST_ROOT "c:/boost")
    set(Boost_USE_STATIC_RUNTIME ON)
else(MSVC)
    set(Boost_USE_STATIC_RUNTIME OFF)
endif(MSVC)

# Find Boost and link it to your project
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenSSL REQUIRED)

add_compile_definitions(APP_NAME="${PROJECT_NAME}" APP_VERSION_STRING="1.0.0" ${SOURCE_DIR_DEFINITION})

add_subdirectory(EasyAppBase)
include_directories(EasyAppBase
        EasyAppBase/shared_recursive_mutex
        EasyAppBase/imgui
        EasyAppBase/imgui/backends
        EasyAppBase/json_document
        EasyAppBase/json_document/ArbitraryOrderMap
        EasyAppBase/json_document/SDString
        ${Boost_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        ${OPENSSL_INCLUDE_DIR}
)

link_directories(
        ${Boost_LIB_DIRS}
        json_document
)

add_executable(ExtraLifeHelper
        main.cpp
        utils.cpp
        utils.h
        ExtraLifeDonationScraper.cpp
        ExtraLifeDonationScraper.h
        ExtraLifeGUI.cpp
        ExtraLifeGUI.h
)

target_link_libraries(ExtraLifeHelper
        easy_app_base
        ${Boost_LIBRARIES}
)
