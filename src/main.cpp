#include <SFML/Graphics.hpp>
#include <iostream>
#include "fractal-renderer/fractals/mobius.h"

void cpuRenderMandelbrotFractal(sf::Image& image, unsigned int WIDTH, unsigned int HEIGHT);

int main() {
  Mobius m  = math::Mobius(1.0, 0.0, 0.0, 1.0);
  std::cout << m.a << std::endl; 

  const unsigned int WIDTH = 800;
  const unsigned int HEIGHT = 600;
  bool use_gpu = false;

  sf::RenderWindow mywindow(sf::VideoMode({WIDTH, HEIGHT}), "Fractal Renderer");

  // CPU rendering setup
  sf::Image myimage({WIDTH, HEIGHT}, sf::Color::Black);
  sf::Texture mytexture;
  sf::Sprite mysprite(mytexture);

  // GPU rendering setup
  sf::Shader myshader;
  sf::RectangleShape myquad;
  
  if (use_gpu) {
    bool shaderLoaded = myshader.loadFromFile("shaders/mandelbrot.frag", sf::Shader::Type::Fragment);
    if (!shaderLoaded) {
      std::cerr << "Failed to load shader" << std::endl;
      return -1;
    }
    std::cout << "shader loaded successfully" << std::endl;

    myshader.setUniform("u_resolution", sf::Vector2f(WIDTH, HEIGHT));
    myshader.setUniform("u_max_iterations", 100);
    
    myquad.setSize(sf::Vector2f(WIDTH, HEIGHT));

  } else {
    
    std::cout << "Image size: " << myimage.getSize().x << "x" << myimage.getSize().y << std::endl;
    cpuRenderMandelbrotFractal(myimage, WIDTH, HEIGHT);
    std::cout << "Rendering complete" << std::endl;
    
    bool textureLoaded = mytexture.loadFromImage(myimage);
    if (!textureLoaded) {
      std::cerr << "Failed to load mytexture from myimage" << std::endl;
      return -1;
    }
    mysprite.setTexture(mytexture, true);
  }

  while (mywindow.isOpen()) {
    while (auto event = mywindow.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        mywindow.close();
      }
    }
    
    mywindow.clear();

    if (use_gpu) {
      mywindow.draw(myquad, &myshader);
    } else {
      mywindow.draw(mysprite);
    }

    mywindow.display();
  }
  
  return 0;
}
