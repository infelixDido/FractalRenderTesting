#include <SFML/Graphics.hpp>

#include <complex>
#include <iostream>
#include <vector>

#include "fractal-renderer/groups/classical_schottky.h"
#include "fractal-renderer/rendering/kleinian_limit_set_renderer.h"
#include "fractal-renderer/groups/grandmas_recipe.h"

int main() {
    constexpr unsigned int window_width = 900;
    constexpr unsigned int window_height = 900;

    std::complex<double> generator_a_trace(2.0, 0.0);
    std::complex<double> generator_b_trace(2.0, 0.0);

    groups::KleinianGroup kleinian_group =
        groups::createParabolicCommutatorGroupFromTraces(
            generator_a_trace,
            generator_b_trace
        );

    const math::MobiusTransformation& first_generator =
        kleinian_group.generators()[0];

    std::array<math::RiemannSpherePoint, 2> fixed_points =
        first_generator.fixedPoints();

    // A fixed point of a loxodromic generator belongs to the
    // Kleinian group's limit set.
    math::RiemannSpherePoint starting_limit_point =
        fixed_points[0];

    sf::Image image(
        {window_width, window_height},
        sf::Color::Black
    );

    rendering::ComplexViewport viewport = {
        -3,
        3,
        -3,
        3.0
    };

    unsigned int maximum_word_length = 13;

    rendering::renderKleinianLimitSet(
        image,
        kleinian_group,
        starting_limit_point,
        maximum_word_length,
        viewport,
        0
    );

    sf::Texture texture;

    if (!texture.loadFromImage(image)) {
        std::cerr << "Failed to create texture." << std::endl;
        return 1;
    }

    sf::Sprite sprite(texture);

    sf::RenderWindow window(
        sf::VideoMode({window_width, window_height}),
        "Kleinian Limit Set"
    );

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

    return 0;
}
