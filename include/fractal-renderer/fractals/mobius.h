#pragma once
#include <complex>

namespace math {

class Mobius {
  public:
    std::complex<double> a, b, c, d;

    std::complex<double> apply_mobius_transform(std::complex<double> z) {
      return (a * z + b) / (c * z + d);
    }

    Mobius compose_mobius_transforms(Mobius& inner_mobius_transform) {
      return Mobius(
        a * inner_mobius_transform.a + b * inner_mobius_transform.c,
        a * inner_mobius_transform.b + b * inner_mobius_transform.d,
        c * inner_mobius_transform.a + d * inner_mobius_transform.c.
        c * inner_mobius_transform.b + d * inner_mobius_transform.d
      );
    }
};

}
