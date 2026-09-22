#pragma once

#include <complex>

#include "fractal-renderer/groups/kleinian_group.h"

namespace groups {

KleinianGroup createParabolicCommutatorGroupFromTraces(
    std::complex<double> generator_a_trace,
    std::complex<double> generator_b_trace
);

}
