#include "pizza.h"

#include <cassert>

Pizza::Pizza(size_t rows, size_t columns, size_t min_ingredient, size_t max_cells) :
    m_rows(rows),
    m_columns(columns),
    m_min_ingredients(min_ingredient),
    m_max_slice_size(max_cells),
    m_pizza(rows * columns)
{
}

const Ingredient &Pizza::getIngredient(size_t r, size_t c) const
{
    assert(r < m_rows);
    assert(c < m_columns);
    return m_pizza[r * m_columns + c];
}

Ingredient &Pizza::getIngredient(size_t r, size_t c)
{
    assert(r < m_rows);
    assert(c < m_columns);
    return m_pizza[r * m_columns + c];
}

size_t Pizza::rows() const
{
    return m_rows;
}

size_t Pizza::columns() const
{
    return m_columns;
}

void Pizza::setIngredient(size_t r, size_t c, Ingredient s)
{
    m_pizza[r * m_columns + c] = s;
}

std::ostream &operator<<(std::ostream &os, const Pizza &p)
{
    for(size_t r = 0; r < p.m_rows; r++)
    {
        for(size_t c = 0; c < p.m_columns; c++)
        {
            Ingredient ig = p.getIngredient(r, c);
            if (ig == U)
                os << "U ";
            else if (ig == M)
                os << "M ";
            else if (ig == T)
                os << "T ";
            else
                os << "? ";
        }
        os << "\n";
    }

    return os;
}
