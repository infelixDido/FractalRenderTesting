#include <SFML/Graphics.hpp>
#include <iostream>


using namespace std;
using namespace sf;

void renderFractal(Image& image, unsigned int WIDTH, unsigned int HEIGHT);

int main() {
  const unsigned int WIDTH = 800;
  const unsigned int HEIGHT = 600;
  
  RenderWindow mywindow(VideoMode({WIDTH, HEIGHT}), "Fractal Renderer");
  Image myimage({WIDTH, HEIGHT}, Color::Black);
  Texture mytexture;
  Sprite mysprite(mytexture);
  Shader myshader;
  RectangleShape myquad;
  
  bool use_gpu = true;
  
  if (use_gpu) {

    bool shaderLoaded = myshader.loadFromFile("shaders/mandelbrot.frag", Shader::Type::Fragment);
    if (!shaderLoaded) {
      cerr << "Failed to load shader" << endl;
      return -1;
    }
    cout << "shader loaded successfully" << endl;
    
    myshader.setUniform("u_resolution", Vector2f(WIDTH, HEIGHT));
    myshader.setUniform("u_max_iterations", 100);

    myquad.setSize(Vector2f(WIDTH, HEIGHT));


  } else {
    
    cout << "Image size: " << myimage.getSize().x << "x" << myimage.getSize().y << endl;
    renderFractal(myimage, WIDTH, HEIGHT);
    cout << "Rendering complete" << endl;
    
    bool textureLoaded = mytexture.loadFromImage(myimage);
    if (!textureLoaded) {
        cerr << "Failed to load mytexture from myimage" << endl;
        return -1;
    }
  }
    


  while (mywindow.isOpen()) {
      while (auto event = mywindow.pollEvent()) {
          if (event->is<Event::Closed>()) {
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
