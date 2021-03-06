#include "evaluator.h"
#include "slices.h"
#include "solver.h"

#include <algorithm>
#include <utility>

Solver::Solver(Pizza &pizza) :
    m_pizza(pizza),
    m_L(pizza.m_min_ingredients),
    m_H(pizza.m_max_slice_size)
{
}

Slices Solver::cut_pizza() const
{
    Slices result;

    Slices::Slice candidate;
    Evaluator ev;

    // Generate primitves possibilities
    std::vector<std::pair<int, int>> candidates;
    /*
    for(int h = m_H-1; h > m_pizza.m_min_ingredients; --h)
    {
        for(int width = h; width >= 1; --width)
        {
            int height = (h / width)-1;
            if (width * height > m_H) continue;
            //if(width * height < 2 * m_pizza.m_min_ingredients) continue;
            candidates.push_back({width, height});
            if (width != height)
                candidates.push_back({height, width});
        }
    }
    */
    for(size_t width = 0; width <= m_H; ++width)
    {
        for(size_t height = 0; height <= m_H; ++height)
        {
            if ((width + 1) * (height + 1) > m_H) continue;
            if((width + 1) * (height + 1) < 2 * m_pizza.m_min_ingredients) continue;
            candidates.push_back({width, height});
        }
    }

    std::sort(candidates.begin(), candidates.end());

    // Debug candidates
    std::cout << "H: " << m_H << "\n";
    std::cout << "L: " << m_L << "\n";
    std::cout << "Candidate slices : \n";
    for(size_t s = 0; s < candidates.size(); s++)
    {
        std::cout << candidates[s].first << ", " << candidates[s].second << "\n";
    }
    std::cout << "\n";

    // For each empty place
    for(size_t r = 0; r < m_pizza.m_rows; ++r)
    {
        candidate.r1 = r;
        for(size_t c = 0; c < m_pizza.m_columns; ++c)
        {
            candidate.c1 = c;
            // Test each primitive
            for(int p = candidates.size() - 1; p >= 0; p--)
            {
                candidate.c2 = c + candidates[p].first;
                candidate.r2 = r + candidates[p].second;
                // Add candidate
                if (ev.validSlice(m_pizza, result, candidate))
                {
                    result.s.push_back(candidate);
                    c = candidate.c2 + 1;
                }
            }
        }
    }

    return result;
}
