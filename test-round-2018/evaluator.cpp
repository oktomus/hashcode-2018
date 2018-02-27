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

        if(r1 < 0 || c1 < 0 || r2 >= p.m_rows || c2 >= p.m_columns)
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
