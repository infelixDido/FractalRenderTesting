#include "fractal-renderer/groups/classical_schottky.h"

#include <cmath>
#include <stdexcept>

namespace groups {

namespace {

bool circlesHaveDisjointInteriors(
    const Circle& first_circle,
    const Circle& second_circle
) {
    double center_distance =
        std::abs(
            first_circle.center
            - second_circle.center
        );

    return center_distance
        > first_circle.radius + second_circle.radius;
}

}

math::MobiusTransformation createCirclePairingTransformation(
    const Circle& source_circle,
    const Circle& target_circle
) {
    if (
        source_circle.radius <= 0.0
        || target_circle.radius <= 0.0
    ) {
        throw std::invalid_argument(
            "Schottky circles must have positive radius."
        );
    }

    std::complex<double> radius_product =
        source_circle.radius * target_circle.radius;

    // g(z)
    //
    // = target_center
    //   + radius_product / (z - source_center)
    //
    // = [target_center * z
    //    + radius_product
    //    - target_center * source_center]
    //   /
    //   [z - source_center]

    return math::MobiusTransformation(
        target_circle.center,
        radius_product
            - target_circle.center * source_circle.center,
        std::complex<double>(1.0, 0.0),
        -source_circle.center
    );
}

KleinianGroup createClassicalSchottkyGroup(
    const std::vector<CirclePairing>& circle_pairings
) {
    if (circle_pairings.empty()) {
        throw std::invalid_argument(
            "A Schottky group needs at least one circle pairing."
        );
    }

    std::vector<Circle> all_circles;

    for (const CirclePairing& pairing : circle_pairings) {
        all_circles.push_back(pairing.source_circle);
        all_circles.push_back(pairing.target_circle);
    }

    for (
        std::size_t first_index = 0;
        first_index < all_circles.size();
        first_index++
    ) {
        for (
            std::size_t second_index = first_index + 1;
            second_index < all_circles.size();
            second_index++
        ) {
            if (
                !circlesHaveDisjointInteriors(
                    all_circles[first_index],
                    all_circles[second_index]
                )
            ) {
                throw std::invalid_argument(
                    "The Schottky construction requires mutually disjoint disks."
                );
            }
        }
    }

    std::vector<math::MobiusTransformation> generators;

    for (const CirclePairing& pairing : circle_pairings) {
        generators.push_back(
            createCirclePairingTransformation(
                pairing.source_circle,
                pairing.target_circle
            )
        );
    }

    return KleinianGroup(generators);
}

}
