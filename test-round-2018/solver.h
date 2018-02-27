#ifndef SOLVER_H
#define SOLVER_H

#include "evaluator.h"
#include "pizza.h"
#include "slices.h"

class Solver
{
public:
    Solver(Pizza & pizza);

    Slices cut_pizza() const;

    Pizza & m_pizza;
    size_t m_L;
    size_t m_H;
};

#endif // SOLVER_H
