#include "evaluator.h"

#include <cassert>

Evaluator::Evaluator()
{

}

bool Evaluator::valid(Pizza p, const Slices &s)
{
    std::size_t n, i, j;
    std::size_t r1;
    std::size_t c1;
    std::size_t r2;
    std::size_t c2;
    std::size_t IT;
    std::size_t IM;

    for(n=0;n<s.s.size();++n)
    {
        IT = 0;
        IM = 0;

        r1 = s.s.at(n).r1;
        c1 = s.s.at(n).c1;
        r2 = s.s.at(n).r2;
        c2 = s.s.at(n).c2;

        if(r2 >= p.m_rows || c2 >= p.m_columns)
            return false;
        if(r1 >= r2 || c1 >= c2)
            return false;
        if((r2-r1)*(c2-c1) > p.m_max_slice_size)
            return false;

        for(i=r1;i<r2;++i)
        {
            for(j=c1;j<c2;++j)
            {
                if(p.getIngredient(i,j) == U)
                    return false;

                if(p.getIngredient(i,j) == T)
                    ++IT;
                if(p.getIngredient(i,j) == M)
                    ++IM;
                else
                    p.setIngredient(i,j,U);
            }
        }

        if(IT < p.m_min_ingredients || IM < p.m_min_ingredients)
            return false;
    }

    return true;
}

std::size_t Evaluator::eval(Pizza p, const Slices &s)
{
    if(!valid(p,s))
        return 0;

    std::size_t r1;
    std::size_t c1;
    std::size_t r2;
    std::size_t c2;

    std::size_t n = 0;

    for(n=0;n<s.s.size();++n)
    {
        r1 = s.s.at(n).r1;
        c1 = s.s.at(n).c1;
        r2 = s.s.at(n).r2;
        c2 = s.s.at(n).c2;

        n += (r2-r1)*(c2-c1);
    }

    return n;
}

bool Evaluator::validSlice(const Pizza & p, Slices s, const Slices::Slice &slice)
{
    /*
    s.s.push_back(slice);
    return valid(p,s);
    */

    std::size_t i,j,n;
    std::size_t IT = 0;
    std::size_t IM = 0;

    // check slice valid
    assert(slice.r1 < p.m_rows);
    assert(slice.c1 < p.m_columns);

    if(slice.r2 >= p.m_rows) return false;
    if(slice.c2 >= p.m_columns) return false;

    // Superficie
    size_t width = slice.c2 - slice.c1;
    size_t height = slice.r2 - slice.r1;

    for(i=slice.r1;i<=slice.r2;++i)
    {
        for(j=slice.c1;j<=slice.c2;++j)
        {
            if(p.getIngredient(i,j) == T)
                ++IT;
            if(p.getIngredient(i,j) == M)
                ++IM;
        }
    }

    if(IT < p.m_min_ingredients || IM < p.m_min_ingredients)
        return false;

    // check colision entre slice et s
    for(n=0;n<s.s.size();++n)
    {
        const Slices::Slice & other = s.s[n];

        // top left inside it
        if ((slice.r1 >= other.r1 && slice.r1 <= other.r2  &&
             slice.c1 >= other.c1 && slice.c1 <= other.c2 ) ||
                // Bottom right inside it
                (slice.r2 >= other.r1 && slice.r2 <= other.r2  &&
                 slice.c2 >= other.c1 && slice.c2 <= other.c2) ||
                // Top Right inside it
                (slice.r1 >= other.r1 && slice.r1 <= other.r2 &&
                 slice.c2 >= other.c1 && slice.c2 <= other.c2) ||
                // Bottom left inside it
                (slice.r2 >= other.r1 && slice.r2 <= other.r2 &&
                 slice.c1 >= other.c1 && slice.c1 <= other.c2))
            return false;
    }
    return true;
}
