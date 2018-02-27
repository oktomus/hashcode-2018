#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "pizza.h"
#include "slices.h"

class Evaluator
{
public:
    Evaluator();

    bool valid(Pizza p, const Slices &s);
    int eval(Pizza p, const Slices &s);
};

#endif // EVALUATOR_H
