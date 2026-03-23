cmake_minimum_required(VERSION 3.20)
project(fractal-renderer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Find SFML
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Create executable
add_executable(fractal-renderer
    src/main.cpp
    src/fractals/mandelbrot.cpp
    src/renderer/mandelbrot_cpu_renderer.cpp
  )
# Include directories
target_include_directories(fractal-renderer PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Link SFML
target_link_libraries(fractal-renderer PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)
