#include "evaluator.h"

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

bool Evaluator::validSlice(Pizza p, Slices s, const Slices::Slice &slice)
{
    /*
    s.s.push_back(slice);
    return valid(p,s);
    */

    std::size_t i,j,n;
    std::size_t IT = 0;
    std::size_t IM = 0;

    // check slice valid

    if(slice.r2 >= p.m_rows || slice.c2 >= p.m_columns)
        return false;
    if(slice.r1 >= slice.r2 || slice.c1 >= slice.c2)
        return false;
    if((slice.r2-slice.r1)*(slice.c2-slice.c1) > p.m_max_slice_size)
        return false;

    for(i=slice.r1;i<slice.r2;++i)
    {
        for(j=slice.c1;j<slice.c2;++j)
        {
            if(p.getIngredient(i,j) == U)
                return false;
            if(p.getIngredient(i,j) == T)
                ++IT;
            if(p.getIngredient(i,j) == M)
                ++IM;
        }
    }

    if(IT < p.m_min_ingredients || IM < p.m_min_ingredients)
        return false;

    std::size_t rect1x, rect1y, rect1w, rect1h;
    std::size_t rect2x, rect2y, rect2w, rect2h;

    rect1x = slice.r1;
    rect1y = slice.c1;
    rect1w = slice.r2 - slice.r1;
    rect1h = slice.c2 - slice.c1;

    // check colision entre slice et s
    for(n=0;n<s.s.size();++n)
    {
        rect1x = s.s.at(n).r1;
        rect1y = s.s.at(n).c1;
        rect1w = s.s.at(n).r2 - s.s.at(n).r1;
        rect1h = s.s.at(n).c2 - s.s.at(n).c1;

        if (rect1x < rect2x + rect2w &&
           rect1x + rect1w > rect2x &&
           rect1y < rect2y + rect2h &&
           rect1h + rect1y > rect2y)
            return false;
    }
    return true;
}
