#include "io.h"
#include "pizza.h"
#include "solver.h"
#include "slices.h"

#include <cassert>
#include <iostream>

#define CHECKPIZZA_ON_LOAD

int main(int argc, const char * argv[])
{
    assert(argc == 2);
    std::string pizza_path = argv[1];

    // Load pizza
    Pizza * pizza = 0;
    IO::read_pizza(pizza_path, &pizza);
    assert(pizza);

    // Check pizza
#ifdef CHECKPIZZA_ON_LOAD
    std::cout << *pizza << std::endl;
    assert(pizza->rows() > 0);
    assert(pizza->columns() > 0);

    for(int r = pizza->rows() - 1; r >= 0; --r)
    {
        for(int c = pizza->columns()  -1; c >= 0; --c)
        {
            assert(pizza->getIngredient(r, c) != U);
        }
    }
#endif

    Solver solver(*pizza);

    Slices slices = solver.cut_pizza();

    // Save slices
    std::string pout = pizza_path.substr(0, pizza_path.find_last_of('.')) + ".out";
    IO::write_slices(pout, slices);

    return 0;
}
