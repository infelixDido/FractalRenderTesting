#pragma once
#include "mobius.h"
#include <complex>
#include <vector>

struct NamedTransform {
  math::Mobius transform;
  int inverse_index;
};

class KleinianGroup {
public:
  std::vector<NamedTransform> generators;

  KleinianGroup(math::Mobius A, math::Mobius B) {
    generators = {
        {A, 1},              // index 0, inverse at 1
        {A.getInverse(), 0}, // index 1, inverse at 0
        {B, 3},              // index 2, inverse at 3
        {B.getInverse(), 2}, // index 3, inverse at 2
    };
  }

  std::vector<std::complex<double>> generateLimitSet(int iterations) const;
};
