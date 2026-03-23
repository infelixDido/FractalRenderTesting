#include <SFML/Graphics.hpp>
#include "fractal-renderer/fractals/mandelbrot.h"
#include <cstdint>
#include <thread>

void renderRows(sf::Image& image, unsigned int start, unsigned int end, unsigned int WIDTH, unsigned int HEIGHT) {
  for (unsigned int py = start; py < end; py++) {
    for (unsigned int px = 0; px < WIDTH; px++) {
      double x = (px - WIDTH / 2.0) * 4.0 / WIDTH;
      double y = (py - HEIGHT / 2.0) * 4.0 / HEIGHT;

      int iterations = fractals::Mandelbrot::calculateIterations(x, y, 100);
      uint8_t color = (iterations == 100) ? 0 : (iterations * 255 / 100);

      image.setPixel({px, py}, sf::Color(color, color, color));
    }
  }
}

void cpuRenderMandelbrotFractal(sf::Image& image, unsigned int WIDTH, unsigned int HEIGHT){
  // Define number of threads
  unsigned int num_threads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads;

  // Render the Mandelbrot set by spliting the image into horizontal bars
    for (unsigned int t = 0; t < num_threads; t++) {
    unsigned int start_row = t * HEIGHT / num_threads;
    unsigned int end_row = (t+1) * HEIGHT / num_threads;

    threads.push_back(
      std::thread(renderRows, std::ref(image), start_row, end_row, WIDTH, HEIGHT)
    );
  }

  for (std::thread& thread : threads) {
    thread.join();
  } 
}
