#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "pizza.h"

class Evaluator
{
public:
    Evaluator();

    int eval(const Pizza &p);
};

#endif // EVALUATOR_H
