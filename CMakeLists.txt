cmake_minimum_required(VERSION 3.28)
project(ExtraLifeHelper)

set(CMAKE_CXX_STANDARD 23)

# Specify the path to your Boost installation
set(BOOST_ROOT "c:/boost")

# Use static runtime
set(Boost_USE_STATIC_RUNTIME ON)

# Find Boost and link it to your project
find_package(Boost REQUIRED COMPONENTS filesystem)

add_executable(ExtraLifeHelper main.cpp
        utils.cpp
        utils.h
        ExtraLifeDonationScraper.cpp
        ExtraLifeDonationScraper.h)

if(Boost_FOUND)
    target_link_libraries(ExtraLifeHelper ${Boost_LIBRARIES})
endif()