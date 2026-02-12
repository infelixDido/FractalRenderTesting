#include "fractal-renderer/fractals/mandelbrot.h"

namespace fractals {

int Mandelbrot::calculate(double x, double y, int max_iterations) {
    double zx = 0.0;
    double zy = 0.0;
    int iteration = 0;
    
    while (zx * zx + zy * zy < 4.0 && iteration < max_iterations) {
        double temp = zx * zx - zy * zy + x;
        zy = 2.0 * zx * zy + y;
        zx = temp;
        iteration++;
    }
    
    return iteration;
}

}
