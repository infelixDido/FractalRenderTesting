#include <SFML/Graphics.hpp>
#include "fractal-renderer/fractals/mandelbrot.h"
#include <cstdint>
#include <thread>

using namespace std;
using namespace sf;

void renderRows(Image& image, unsigned int start, unsigned int end, unsigned int WIDTH, unsigned int HEIGHT) {
  for (unsigned int py = start; py < end; py++) {
    for (unsigned int px = 0; px < WIDTH; px++) {
      double x = (px - WIDTH / 2.0) * 4.0 / WIDTH;
      double y = (py - HEIGHT / 2.0) * 4.0 / HEIGHT;

      int iterations = fractals::Mandelbrot::calculate(x, y, 100);
      uint8_t color = (iterations == 100) ? 0 : (iterations * 255 / 100);

      image.setPixel({px, py}, Color(color, color, color));
    }
  }
}


void renderFractal(Image& image, unsigned int WIDTH, unsigned int HEIGHT){
  // Define number of threads
  unsigned int num_threads = thread::hardware_concurrency();
  vector<thread> threads;

  // Render the Mandelbrot set
  for (unsigned int t = 0; t < num_threads; t++) {
    unsigned int start_row = t * HEIGHT / num_threads;
    unsigned int end_row = (t+1) * HEIGHT / num_threads;

    threads.push_back(
      thread(renderRows, ref(image), start_row, end_row, WIDTH, HEIGHT)
    );
  }

  for (auto& thread : threads) {
    thread.join();
  } 
}
