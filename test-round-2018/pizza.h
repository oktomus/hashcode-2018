#ifndef PIZZA_H
#define PIZZA_H

#include <iostream>
#include <vector>

typedef std::size_t size_t;
typedef size_t Slice;

enum Ingredient
{
    U = 0,  // Undefined
    T = 1,  // Tomato
    M = 2   // Mushroom
};

class Cell
{
public:
    Cell();

    Ingredient type;
    Slice slice;
};

class Pizza
{
public:
    /**
     * @brief Pizza
     * @param rows R
     * @param columns C
     * @param min_ingredient L
     * @param max_cells H
     */
    Pizza(size_t rows, size_t columns, size_t min_ingredient, size_t max_cells);

    const Cell &getCell(size_t r, size_t c) const;
    Cell & getCell(size_t r, size_t c);
    Ingredient getIngredient(size_t r, size_t c) const;
    Slice getSlice(size_t r, size_t c) const;

    void setIngredient(size_t r, size_t c, Ingredient s);
    void setSlice(size_t r, size_t c, Slice s);

    friend std::ostream & operator<<(std::ostream& os, const Pizza & p);

private:
    size_t m_rows; // Width
    size_t m_columns; // Height
    size_t m_min_ingredients; // Minimum number of ingredient per slice
    size_t m_max_slice_size; // Maximum number of cells for a slice

    std::vector<Cell> m_pizza;
};

#endif // PIZZA_H
