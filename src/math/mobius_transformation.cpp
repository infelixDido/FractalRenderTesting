#include "fractal-renderer/math/mobius_transformation.h"

#include <cmath>
#include <stdexcept>

namespace math {

MobiusTransformation::MobiusTransformation(
    std::complex<double> a,
    std::complex<double> b,
    std::complex<double> c,
    std::complex<double> d
)
    : a_(a),
      b_(b),
      c_(c),
      d_(d) {

    constexpr double determinant_tolerance = 1e-12;

    if (std::abs(determinant()) < determinant_tolerance) {
        throw std::invalid_argument(
            "A Mobius transformation must have nonzero determinant."
        );
    }
}

std::complex<double> MobiusTransformation::determinant() const {
    return a_ * d_ - b_ * c_;
}

RiemannSpherePoint MobiusTransformation::apply(
    const RiemannSpherePoint& point
) const {
    std::complex<double> numerator =
        a_ * point.homogeneousNumerator()
        + b_ * point.homogeneousDenominator();

    std::complex<double> denominator =
        c_ * point.homogeneousNumerator()
        + d_ * point.homogeneousDenominator();

    return RiemannSpherePoint(numerator, denominator);
}

MobiusTransformation MobiusTransformation::inverse() const {
    std::complex<double> matrix_determinant = determinant();

    return MobiusTransformation(
        d_ / matrix_determinant,
        -b_ / matrix_determinant,
        -c_ / matrix_determinant,
        a_ / matrix_determinant
    );
}

MobiusTransformation MobiusTransformation::composeAfter(
    const MobiusTransformation& transformation_applied_first
) const {
    std::complex<double> composed_a =
        a_ * transformation_applied_first.a_
        + b_ * transformation_applied_first.c_;

    std::complex<double> composed_b =
        a_ * transformation_applied_first.b_
        + b_ * transformation_applied_first.d_;

    std::complex<double> composed_c =
        c_ * transformation_applied_first.a_
        + d_ * transformation_applied_first.c_;

    std::complex<double> composed_d =
        c_ * transformation_applied_first.b_
        + d_ * transformation_applied_first.d_;

    return MobiusTransformation(
        composed_a,
        composed_b,
        composed_c,
        composed_d
    );
}

std::array<RiemannSpherePoint, 2>
MobiusTransformation::fixedPoints() const {
    constexpr double coefficient_tolerance = 1e-12;

    // Solve
    //
    //          az + b
    //     z = --------
    //          cz + d
    //
    // giving
    //
    // c z^2 + (d - a) z - b = 0.

    if (std::abs(c_) > coefficient_tolerance) {
        std::complex<double> linear_coefficient = d_ - a_;

        std::complex<double> discriminant =
            linear_coefficient * linear_coefficient
            + 4.0 * b_ * c_;

        std::complex<double> square_root_discriminant =
            std::sqrt(discriminant);

        std::complex<double> first_fixed_point =
            (-linear_coefficient + square_root_discriminant)
            / (2.0 * c_);

        std::complex<double> second_fixed_point =
            (-linear_coefficient - square_root_discriminant)
            / (2.0 * c_);

        return {
            RiemannSpherePoint(first_fixed_point),
            RiemannSpherePoint(second_fixed_point)
        };
    }

    // If c = 0, infinity is fixed.
    //
    // The remaining finite equation is
    //
    // (d - a)z - b = 0.

    if (std::abs(d_ - a_) > coefficient_tolerance) {
        std::complex<double> finite_fixed_point =
            b_ / (d_ - a_);

        return {
            RiemannSpherePoint(finite_fixed_point),
            RiemannSpherePoint::infinity()
        };
    }

    // z -> z + constant has infinity as its only fixed point,
    // counted twice.
    if (std::abs(b_) > coefficient_tolerance) {
        return {
            RiemannSpherePoint::infinity(),
            RiemannSpherePoint::infinity()
        };
    }

    // A scalar matrix represents the identity transformation,
    // so every point is fixed.
    throw std::domain_error(
        "The identity Mobius transformation does not have exactly two fixed points."
    );
}

}
