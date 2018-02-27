#include "pizza.h"

#include <iostream>

int main()
{
    Pizza p(2, 5, 1, 3);

    std::cout << p.getSlice(0, 0) << std::endl;
    p.setSlice(0, 0, 50);
    std::cout << p.getSlice(0, 0) << std::endl;
    std::cout << p.getSlice(1, 4) << std::endl;
    p.setIngredient(1, 1, T);
    p.setIngredient(1, 2, T);
    p.setIngredient(0, 3, T);
    std::cout << p << std::endl;
    return 0;
}
