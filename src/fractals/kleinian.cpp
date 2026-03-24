#include "fractal-renderer/fractals/mobius.h"

namespace math {

void generateLimitSet(const Mobius& currentW, int depth, int lastIdx, std::vector<Mobius>& generators) {
  if (depth >= MAX_DEPTH) {
    // Send to shader to draw seed point with stored matrix
    // drawPointWithShader();
    return;
  }

  for (int i = 0; i < 4; ++i) {
      // Skip the inverse of the last move to prevent backtracking
      // (This assumes 0/1 and 2/3 are inverse pairs)
      if (depth > 0 && i == (lastIdx ^ 1)) continue;

      // Compose the new word: NewW = currentW * Generator[i]
      Mobius nextW = currentW.compose(generators[i]);
      
      // Recurse deeper
      generateLimitSet(nextW, depth + 1, i, generators);
  }
}

}
