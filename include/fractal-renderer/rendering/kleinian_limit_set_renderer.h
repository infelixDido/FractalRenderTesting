#pragma once

#include <SFML/Graphics.hpp>

#include "fractal-renderer/groups/kleinian_group.h"
#include "fractal-renderer/math/riemann_sphere_point.h"

namespace rendering {

struct ComplexViewport {
    double minimum_real;
    double maximum_real;

    double minimum_imaginary;
    double maximum_imaginary;
};

void renderKleinianLimitSet(
    sf::Image& image,
    const groups::KleinianGroup& group,
    const math::RiemannSpherePoint& starting_limit_point,
    unsigned int maximum_word_length,
    const ComplexViewport& viewport,
    unsigned int point_radius_pixels = 0
);

}
