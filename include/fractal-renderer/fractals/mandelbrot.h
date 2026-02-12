#pragma once

namespace fractals {

class Mandelbrot {
public:
    // Returns number of iterations before escape (or max_iterations if it doesn't escape)
    static int calculate(double x, double y, int max_iterations = 100);
};

}
