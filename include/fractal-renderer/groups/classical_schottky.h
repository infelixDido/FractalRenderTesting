#pragma once

#include <complex>
#include <vector>

#include "fractal-renderer/groups/kleinian_group.h"

namespace groups {

struct Circle {
    std::complex<double> center;
    double radius;
};

struct CirclePairing {
    Circle source_circle;
    Circle target_circle;
};

math::MobiusTransformation createCirclePairingTransformation(
    const Circle& source_circle,
    const Circle& target_circle
);

KleinianGroup createClassicalSchottkyGroup(
    const std::vector<CirclePairing>& circle_pairings
);

}
