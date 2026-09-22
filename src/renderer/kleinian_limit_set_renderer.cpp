#include "fractal-renderer/rendering/kleinian_limit_set_renderer.h"

#include <cmath>
#include <complex>
#include <optional>

namespace rendering {

namespace {

void drawComplexPoint(
    sf::Image& image,
    const std::complex<double>& point,
    const ComplexViewport& viewport,
    unsigned int point_radius_pixels
) {
    double real_part = point.real();
    double imaginary_part = point.imag();

    if (
        !std::isfinite(real_part)
        || !std::isfinite(imaginary_part)
    ) {
        return;
    }

    if (
        real_part < viewport.minimum_real
        || real_part > viewport.maximum_real
        || imaginary_part < viewport.minimum_imaginary
        || imaginary_part > viewport.maximum_imaginary
    ) {
        return;
    }

    sf::Vector2u image_size = image.getSize();

    double horizontal_fraction =
        (real_part - viewport.minimum_real)
        / (viewport.maximum_real - viewport.minimum_real);

    double vertical_fraction =
        (viewport.maximum_imaginary - imaginary_part)
        / (viewport.maximum_imaginary - viewport.minimum_imaginary);

    int pixel_x = static_cast<int>(
        horizontal_fraction * (image_size.x - 1)
    );

    int pixel_y = static_cast<int>(
        vertical_fraction * (image_size.y - 1)
    );

    int radius = static_cast<int>(point_radius_pixels);

    for (
        int vertical_offset = -radius;
        vertical_offset <= radius;
        vertical_offset++
    ) {
        for (
            int horizontal_offset = -radius;
            horizontal_offset <= radius;
            horizontal_offset++
        ) {
            int draw_x = pixel_x + horizontal_offset;
            int draw_y = pixel_y + vertical_offset;

            if (
                draw_x < 0
                || draw_y < 0
                || draw_x >= static_cast<int>(image_size.x)
                || draw_y >= static_cast<int>(image_size.y)
            ) {
                continue;
            }

            image.setPixel(
                {
                    static_cast<unsigned int>(draw_x),
                    static_cast<unsigned int>(draw_y)
                },
                sf::Color::White
            );
        }
    }
}

void traverseReducedGroupWords(
    sf::Image& image,
    const groups::KleinianGroup& group,
    const math::RiemannSpherePoint& current_point,
    const groups::DirectedGenerator* previous_generator,
    unsigned int current_word_length,
    unsigned int maximum_word_length,
    const ComplexViewport& viewport,
    unsigned int point_radius_pixels
) {
    std::optional<std::complex<double>> affine_coordinate =
        current_point.affineCoordinate();

    if (affine_coordinate.has_value()) {
        drawComplexPoint(
            image,
            affine_coordinate.value(),
            viewport,
            point_radius_pixels
        );
    }

    if (current_word_length == maximum_word_length) {
        return;
    }

    for (
        const groups::DirectedGenerator& next_generator :
        group.directedGenerators()
    ) {
        if (
            previous_generator != nullptr
            && group.immediatelyCancels(
                *previous_generator,
                next_generator
            )
        ) {
            continue;
        }

        math::RiemannSpherePoint next_point =
            next_generator.transformation.apply(current_point);

        traverseReducedGroupWords(
            image,
            group,
            next_point,
            &next_generator,
            current_word_length + 1,
            maximum_word_length,
            viewport,
            point_radius_pixels
        );
    }
}

}

void renderKleinianLimitSet(
    sf::Image& image,
    const groups::KleinianGroup& group,
    const math::RiemannSpherePoint& starting_limit_point,
    unsigned int maximum_word_length,
    const ComplexViewport& viewport,
    unsigned int point_radius_pixels
) {
    traverseReducedGroupWords(
        image,
        group,
        starting_limit_point,
        nullptr,
        0,
        maximum_word_length,
        viewport,
        point_radius_pixels
    );
}

}
