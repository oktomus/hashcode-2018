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
    return result;
}
