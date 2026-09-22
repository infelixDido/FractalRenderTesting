#pragma once

#include <cstddef>
#include <vector>

#include "fractal-renderer/math/mobius_transformation.h"

namespace groups {

struct DirectedGenerator {
    math::MobiusTransformation transformation;

    std::size_t original_generator_index;

    bool uses_inverse;
};

class KleinianGroup {
public:
    explicit KleinianGroup(
        const std::vector<math::MobiusTransformation>& generators
    );

    const std::vector<math::MobiusTransformation>& generators() const;

    const std::vector<DirectedGenerator>& directedGenerators() const;

    bool immediatelyCancels(
        const DirectedGenerator& previous_generator,
        const DirectedGenerator& next_generator
    ) const;

private:
    std::vector<math::MobiusTransformation> generators_;

    std::vector<DirectedGenerator> directed_generators_;
};

}
