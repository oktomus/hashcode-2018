#include "pizza.h"

#include <cassert>

Cell::Cell() :
    type(M),
    slice(0)
{

}

Pizza::Pizza(size_t rows, size_t columns, size_t min_ingredient, size_t max_cells) :
    m_rows(rows),
    m_columns(columns),
    m_min_ingredients(min_ingredient),
    m_max_slice_size(max_cells),
    m_pizza(rows * columns)
{
}

const Cell &Pizza::getCell(size_t r, size_t c) const
{
    assert(r < m_rows);
    assert(c < m_columns);
    return m_pizza[r * m_columns + c];
}

Cell &Pizza::getCell(size_t r, size_t c)
{
    assert(r < m_rows);
    assert(c < m_columns);
    return m_pizza[r * m_columns + c];
}

Ingredient Pizza::getIngredient(size_t r, size_t c) const
{
    return getCell(r, c).type;
}

Slice Pizza::getSlice(size_t r, size_t c) const
{
    return getCell(r, c).slice;
}

void Pizza::setSlice(size_t r, size_t c, Slice s)
{
    getCell(r, c).slice = s;
}

void Pizza::setIngredient(size_t r, size_t c, Ingredient s)
{
    getCell(r, c).type = s;
}

std::ostream &operator<<(std::ostream &os, const Pizza &p)
{
    for(size_t r = 0; r < p.m_rows; r++)
    {
        for(size_t c = 0; c < p.m_columns; c++)
        {
            Ingredient ig = p.getIngredient(r, c);
            if (ig == M)
                os << "M ";
            else
                os << "T ";
        }
        os << "\n";
    }

    return os;
}
