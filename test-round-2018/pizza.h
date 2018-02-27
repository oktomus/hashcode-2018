#ifndef PIZZA_H
#define PIZZA_H

#include <vector>

enum Ingredient
{
    T, // Tomato
    M // Mushroom
};

typedef size_t Slice;

class Pizza
{
public:
    Pizza(size_t rows, size_t columns, size_t min_ingredient, size_t max_cells);

private:
    size_t m_rows; // Width
    size_t m_columns; // Height
    size_t m_min_ingredients; // Minimum number of ingredient per slice
    size_t m_max_slice_size; // Maximum number of cells for a slice

    std::vector<Ingredient> m_pizza;
    std::vector<Slice> m_slice;
};

#endif // PIZZA_H
