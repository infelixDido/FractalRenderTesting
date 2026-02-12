#include <SFML/Graphics.hpp>
#include "fractal-renderer/fractals/mandelbrot.h"
#include <cstdint>
#include <iostream>

int main() {
    const unsigned int WIDTH = 800;
    const unsigned int HEIGHT = 600;
    
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Fractal Renderer");
    sf::Image image({WIDTH, HEIGHT}, sf::Color::Black);

    std::cout << "Image size: " << image.getSize().x << "x" << image.getSize().y << std::endl;
    
    // Render the Mandelbrot set
    for (unsigned int py = 0; py < HEIGHT; py++) {
        for (unsigned int px = 0; px < WIDTH; px++) {
            // Map pixel to complex plane
            double x = (px - WIDTH / 2.0) * 4.0 / WIDTH;
            double y = (py - HEIGHT / 2.0) * 4.0 / HEIGHT;
            
            int iterations = fractals::Mandelbrot::calculate(x, y, 100);
            
            // Simple grayscale coloring
            uint8_t color = (iterations == 100) ? 0 : (iterations * 255 / 100);
            image.setPixel({px, py}, sf::Color(color, color, color));
        }
    }
    
    std::cout << "Rendering complete" << std::endl;
    
    sf::Texture texture;
    if (!texture.loadFromImage(image)) {
        std::cerr << "Failed to load texture from image" << std::endl;
        return -1;
    }
    sf::Sprite sprite(texture);
    
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        
        window.clear();
        window.draw(sprite);
        window.display();
    }
    
    return 0;
}
