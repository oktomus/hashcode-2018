#include "evaluator.h"
#include "slices.h"
#include "solver.h"

Solver::Solver(Pizza &pizza) :
    m_pizza(pizza),
    m_L(pizza.m_min_ingredients),
    m_H(pizza.m_max_slice_size)
{
}

Slices Solver::cut_pizza() const
{
    Slices result;

    Slices::Slice candidate;
    Evaluator ev;


    // For each empty place
    for(size_t r = 0; r < m_pizza.m_rows; ++r)
    {
        candidate.r1 = r;
        for(size_t c = 0; c < m_pizza.m_columns; ++c)
        {
            candidate.c1 = c;
            // Generate primitives
            for(size_t width = m_H; width >= 1; --width)
            {
                size_t height = 1 / width;
                candidate.c2 = c + width;
                candidate.r2 = r + height;
                // Add candidate
                if (ev.validSlice(m_pizza, result, candidate))
                {
                    result.s.push_back(candidate);
                }
            }
        }
    }

    return result;
}
