#ifndef SLICES_H
#define SLICES_H

#include <iostream>
#include <vector>

class Slices
{
public:
    Slices();

    class Slice
    {
        public:
        Slice();
        std::size_t i1;
        std::size_t j1;
        std::size_t i2;
        std::size_t j2;
    };
};

#endif // SLICES_H
