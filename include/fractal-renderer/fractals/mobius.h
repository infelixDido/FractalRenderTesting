#pragma once
#include <complex>

namespace math {

class Mobius {
  public:
    std::complex<double> a, b, c, d;

    Mobius(std::complex<double> a_, std::complex<double> b_, std::complex<double> c_, std::complex<double> d_) {
      std::complex<double> determinant = a_ * d_ - b_ * c_; 
      if (std::abs(determinant) < 1e-10) {
        std::cerr << "Invalid Mobius transform. ad - bc = 0" << std::endl;
      }
      a = a_;
      b = b_;
      c = c_;
      d = d_;
    }

    Mobius normalized() const {
        std::complex<double> normalization_factor = std::sqrt(a * d - b * c);
        return Mobius (
            a / normalization_factor,
            b / normalization_factor,
            c / normalization_factor,
            d / normalization_factor
        );
      }
    }
    
    Mobius getInverse() const {
      return Mobius(d, -b, -c, a);
    }

    Mobius compose_mobius_transforms(const Mobius& other) const {
      return Mobius(
          a * other.a + b * other.c,
          a * other.b + b * other.d,
          c * other.a + d * other.c.
          c * other.b + d * other.d
      );
    }
};

}
