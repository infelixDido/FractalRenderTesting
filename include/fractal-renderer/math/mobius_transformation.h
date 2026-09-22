#pragma once

#include <array>
#include <complex>

#include "fractal-renderer/math/riemann_sphere_point.h"

namespace math {

class MobiusTransformation {
public:
    MobiusTransformation(
        std::complex<double> a,
        std::complex<double> b,
        std::complex<double> c,
        std::complex<double> d
    );

    std::complex<double> determinant() const;

    RiemannSpherePoint apply(
        const RiemannSpherePoint& point
    ) const;

    MobiusTransformation inverse() const;

    MobiusTransformation composeAfter(
        const MobiusTransformation& transformation_applied_first
    ) const;

    std::array<RiemannSpherePoint, 2> fixedPoints() const;

private:
    std::complex<double> a_;
    std::complex<double> b_;
    std::complex<double> c_;
    std::complex<double> d_;
};

}
