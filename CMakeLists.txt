cmake_minimum_required(VERSION 3.10)

project(mandelbrot_set)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 REQUIRED)

include_directories(
    include
    ${SDL2_INCLUDE_DIRS}
    )

set(SOURCES
    src/main.cpp    
    )

add_executable(
    ${PROJECT_NAME} 
    ${SOURCES}
    )

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE ${SDL2_LIBRARIES}
    )


