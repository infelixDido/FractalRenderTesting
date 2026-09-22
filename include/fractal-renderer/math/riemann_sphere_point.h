#pragma once

#include <cmath>
#include <complex>
#include <optional>
#include <stdexcept>

namespace math {

class RiemannSpherePoint {
public:
    explicit RiemannSpherePoint(std::complex<double> affine_coordinate)
        : homogeneous_numerator_(affine_coordinate),
          homogeneous_denominator_(1.0, 0.0) {}

    RiemannSpherePoint(
        std::complex<double> homogeneous_numerator,
        std::complex<double> homogeneous_denominator
    )
        : homogeneous_numerator_(homogeneous_numerator),
          homogeneous_denominator_(homogeneous_denominator) {
        normalize();
    }

    static RiemannSpherePoint infinity() {
        return RiemannSpherePoint(
            std::complex<double>(1.0, 0.0),
            std::complex<double>(0.0, 0.0)
        );
    }

    std::complex<double> homogeneousNumerator() const {
        return homogeneous_numerator_;
    }

    std::complex<double> homogeneousDenominator() const {
        return homogeneous_denominator_;
    }

    std::optional<std::complex<double>> affineCoordinate() const {
        constexpr double infinity_tolerance = 1e-12;

        if (std::abs(homogeneous_denominator_) < infinity_tolerance) {
            return std::nullopt;
        }

        return homogeneous_numerator_ / homogeneous_denominator_;
    }

private:
    std::complex<double> homogeneous_numerator_;
    std::complex<double> homogeneous_denominator_;

    void normalize() {
        double magnitude = std::sqrt(
            std::norm(homogeneous_numerator_)
            + std::norm(homogeneous_denominator_)
        );

        if (magnitude == 0.0) {
            throw std::invalid_argument(
                "A Riemann sphere point cannot have homogeneous coordinates [0:0]."
            );
        }

        homogeneous_numerator_ /= magnitude;
        homogeneous_denominator_ /= magnitude;
    }
};

}
