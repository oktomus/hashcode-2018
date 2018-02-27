#include "pizza.h"

#include <iostream>

int main()
{
    Pizza p(2, 5, 1, 3);

    p.setIngredient(1, 1, T);
    p.setIngredient(1, 2, T);
    p.setIngredient(0, 3, T);

    std::cout << p << std::endl;

    return 0;
}
