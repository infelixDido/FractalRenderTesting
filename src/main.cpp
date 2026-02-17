#include <SFML/Graphics.hpp>
#include "fractal-renderer/fractals/mandelbrot.h"
#include <cstdint>
#include <iostream>

using namespace std;
using namespace sf;

int main() {
    const unsigned int WIDTH = 800;
    const unsigned int HEIGHT = 600;
    
    RenderWindow mywindow(VideoMode({WIDTH, HEIGHT}), "Fractal Renderer");
    Image myimage({WIDTH, HEIGHT}, Color::Black);

    cout << "Image size: " << myimage.getSize().x << "x" << myimage.getSize().y << endl;
    
    // Render the Mandelbrot set
    for (unsigned int py = 0; py < HEIGHT; py++) {
        for (unsigned int px = 0; px < WIDTH; px++) {
            // Map pixel to complex plane
            double x = (px - WIDTH / 2.0) * 4.0 / WIDTH;
            double y = (py - HEIGHT / 2.0) * 4.0 / HEIGHT;
            
            int iterations = fractals::Mandelbrot::calculate(x, y, 100);
            
            // Simple grayscale mycoloring
            uint8_t mycolor = (iterations == 100) ? 0 : (iterations * 255 / 100);
            myimage.setPixel({px, py}, Color(mycolor, mycolor, mycolor));
        }
    }
    
    cout << "Rendering complete" << endl;
    
    Texture mytexture;
    if (!mytexture.loadFromImage(myimage)) {
        cerr << "Failed to load mytexture from myimage" << endl;
        return -1;
    }
    Sprite mysprite(mytexture);
    
    while (mywindow.isOpen()) {
        while (auto event = mywindow.pollEvent()) {
            if (event->is<Event::Closed>()) {
                mywindow.close();
            }
        }
        
        mywindow.clear();
        mywindow.draw(mysprite);
        mywindow.display();
    }
    
    return 0;
}
