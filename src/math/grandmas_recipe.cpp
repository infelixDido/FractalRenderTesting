#include "fractal-renderer/groups/grandmas_recipe.h"

#include <complex>
#include <stdexcept>

namespace groups {

KleinianGroup createParabolicCommutatorGroupFromTraces(
    std::complex<double> generator_a_trace,
    std::complex<double> generator_b_trace
) {
    const std::complex<double> imaginary_unit(0.0, 1.0);

    /*
     * Let
     *
     *     T_a  = trace(A)
     *     T_b  = trace(B)
     *     T_ab = trace(AB)
     *
     * The trace identity is
     *
     * trace([A,B])
     * =
     * T_a^2 + T_b^2 + T_ab^2
     * - T_a T_b T_ab - 2.
     *
     * Grandma's recipe chooses
     *
     *     trace([A,B]) = -2,
     *
     * so T_ab satisfies
     *
     * T_ab^2
     * - T_a T_b T_ab
     * + T_a^2
     * + T_b^2
     * = 0.
     */

    std::complex<double> half_trace_product =
        generator_a_trace * generator_b_trace / 2.0;

    std::complex<double> trace_discriminant =
        half_trace_product * half_trace_product
        - generator_a_trace * generator_a_trace
        - generator_b_trace * generator_b_trace;

    /*
     * There are two quadratic roots.
     *
     * Grandma's recipe chooses one branch here.
     * The other branch gives the alternate normalization.
     */
    std::complex<double> product_trace =
        half_trace_product
        - std::sqrt(trace_discriminant);

    /*
     * This normalization point determines the concrete
     * representatives of the conjugacy class.
     */
    std::complex<double> normalization_point =
        (product_trace - 2.0) * generator_b_trace
        /
        (
            generator_b_trace * product_trace
            - 2.0 * generator_a_trace
            + 2.0 * imaginary_unit * product_trace
        );

    if (std::abs(normalization_point) < 1e-12) {
        throw std::runtime_error(
            "Grandma's recipe produced a degenerate normalization point."
        );
    }

    /*
     * Matrix for B:
     *
     *  1/2 [ T_b - 2i      T_b      ]
     *      [    T_b       T_b + 2i  ]
     */
    math::MobiusTransformation generator_b(
        (generator_b_trace - 2.0 * imaginary_unit) / 2.0,
        generator_b_trace / 2.0,
        generator_b_trace / 2.0,
        (generator_b_trace + 2.0 * imaginary_unit) / 2.0
    );

    /*
     * We first construct the matrix AB:
     *
     * [ T_ab / 2              (T_ab - 2)/(2 z_0) ]
     * [ (T_ab + 2) z_0 / 2    T_ab / 2           ]
     */
    math::MobiusTransformation product_ab(
        product_trace / 2.0,

        (product_trace - 2.0)
            / (2.0 * normalization_point),

        (product_trace + 2.0)
            * normalization_point / 2.0,

        product_trace / 2.0
    );

    /*
     * Since
     *
     *     AB B^{-1} = A,
     *
     * recover A from AB and B.
     */
    math::MobiusTransformation generator_a =
        product_ab.composeAfter(
            generator_b.inverse()
        );

    return KleinianGroup({
        generator_a,
        generator_b
    });
}

}
