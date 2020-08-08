cmake_minimum_required(VERSION 3.10)

project(mandelbrot_set)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
# set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 REQUIRED)
# find_package(OpenCV REQUIRED)
# find_package(Boost REQUIRED)


include_directories(
    include
    # ${OpenCV_INCLUDE_DIRS}
    # ${Boost_INCLUDE_DIRS}
    )

set(SOURCES
    src/main.cpp    
    src/mandelbrot.cpp
    src/window.cpp
    src/color.cpp
    )

add_executable(
    ${PROJECT_NAME} 
    ${SOURCES}
    )

target_link_libraries(
    ${PROJECT_NAME}
    SDL2::SDL2
    # ${OpenCV_LIBS}
    # ${Boost_LIBS}
    )


