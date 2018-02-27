#include "pizza.h"

Pizza::Pizza(size_t rows, size_t columns, size_t min_ingredient, size_t max_cells) :
    m_rows(rows),
    m_columns(columns),
    m_min_ingredients(min_ingredient),
    m_max_slice_size(max_cells),
    m_pizza(rows * columns),
    m_slice(rows * columns)
{

}
