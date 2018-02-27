#include "io.h"

#include <cassert>
#include <fstream>

void IO::read_pizza(const std::string &path, Pizza *out)
{
    std::ifstream reader(path);

    assert(reader.is_open());

    size_t R, C, L, H;
    reader >> R >> C >> L >> H;
    out = new Pizza(R, C, L, H);
    char ingredient;

    for(int r = R - 1; r >= 0; r--)
    {
        for(int c = C - 1; c >= 0; c--)
        {
            reader >> ingredient;
            assert(ingredient == 'M' || ingredient == 'T');
            if (ingredient == 'M')
                out->setIngredient(r, c, M);
            else
                out->setIngredient(r, c, T);
        }
    }

    reader.close();
}
