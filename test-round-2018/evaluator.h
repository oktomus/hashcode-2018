#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "pizza.h"
#include "slices.h"

class Evaluator
{
public:
    Evaluator();

    bool valid(Pizza p, const Slices &s);
    std::size_t eval(Pizza p, const Slices &s);

    bool validSlice(const Pizza & p, Slices s, const Slices::Slice &slice);
};

#endif // EVALUATOR_H
