cmake_minimum_required(VERSION 3.20)

project(fractal-renderer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
    SFML 3
    COMPONENTS Graphics Window System
    REQUIRED
)

add_executable(
    fractal-renderer

    src/main.cpp

    src/math/mobius_transformation.cpp
    src/math/kleinian_group.cpp
    src/math/classical_schottky.cpp
    src/math/grandmas_recipe.cpp

    src/renderer/kleinian_limit_set_renderer.cpp

    # src/fractals/mandelbrot.cpp
    # src/renderer/mandelbrot_cpu_renderer.cpp
)

target_include_directories(
    fractal-renderer
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
    fractal-renderer
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)
