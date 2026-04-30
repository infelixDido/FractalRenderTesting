#include "fractal-renderer/fractals/kleinian.h"

std::vector<std::complex<double>> generateLimitSet(int maxDepth) const {
  std::vector<std::complex<double>> points;

  // Each element of the queue is a (transform, last_index) pair
  // representing the word built up so far
  std::queue<std::pair<Mobius, int>> queue;

  // Seed the queue with each generator
  for (int i = 0; i < generators.size(); i++) {
    queue.push({generators[i].transform, i});
  }

  std::complex<double> seed = 0.0;

  for (int depth = 0; depth < maxDepth; depth++) {
    int levelSize = queue.size();
    for (int i = 0; i < levelSize; i++) {
      auto [current, last_index] = queue.front();
      queue.pop();

      points.push_back(current.apply(seed));

      // Extend the word by each generator, skipping the inverse of the last
      for (int j = 0; j < generators.size(); j++) {
        if (j == generators[last_index].inverse_index)
          continue;
        queue.push({current.compose(generators[j].transform), j});
      }
    }
  }

  return points;
}
