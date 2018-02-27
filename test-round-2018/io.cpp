#include "io.h"

#include <cassert>
#include <fstream>

void IO::read_pizza(const std::string &path, Pizza **out)
{
    std::ifstream reader(path);

    assert(reader.is_open());

    size_t R, C, L, H;
    reader >> R >> C >> L >> H;
    *out = new Pizza(R, C, L, H);
    char ingredient;

    for(size_t r = 0; r < R; ++r)
    {
        for(size_t c = 0; c < C; ++c)
        {
            reader >> ingredient;
            assert(ingredient == 'M' || ingredient == 'T');
            if (ingredient == 'M')
                (*out)->setIngredient(r, c, M);
            else
                (*out)->setIngredient(r, c, T);
        }
    }

    reader.close();
}

void IO::write_slices(const std::string &path, const Slices &slices)
{
    std::ofstream writer(path);

    assert(writer.is_open());

    writer << slices.s.size() << "\n";

    for(size_t i = 0; i < slices.s.size(); ++i)
    {
        const Slices::Slice & sl = slices.s[i];
        writer << sl.r1 << " " << sl.c1 << " " << sl.r2 << " " << sl.c2 << "\n";
    }

    writer.close();

}
