#include "fractal-renderer/groups/kleinian_group.h"

namespace groups {

KleinianGroup::KleinianGroup(
    const std::vector<math::MobiusTransformation>& generators
)
    : generators_(generators) {

    for (
        std::size_t generator_index = 0;
        generator_index < generators_.size();
        generator_index++
    ) {
        directed_generators_.push_back({
            generators_[generator_index],
            generator_index,
            false
        });

        directed_generators_.push_back({
            generators_[generator_index].inverse(),
            generator_index,
            true
        });
    }
}

const std::vector<math::MobiusTransformation>&
KleinianGroup::generators() const {
    return generators_;
}

const std::vector<DirectedGenerator>&
KleinianGroup::directedGenerators() const {
    return directed_generators_;
}

bool KleinianGroup::immediatelyCancels(
    const DirectedGenerator& previous_generator,
    const DirectedGenerator& next_generator
) const {
    bool same_original_generator =
        previous_generator.original_generator_index
        == next_generator.original_generator_index;

    bool opposite_direction =
        previous_generator.uses_inverse
        != next_generator.uses_inverse;

    return same_original_generator && opposite_direction;
}

}
