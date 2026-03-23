#pragma once

namespace fractals {

class Mandelbrot {
public:
    static int calculateIterations(double x, double y, int max_iterations = 100);
};

}
