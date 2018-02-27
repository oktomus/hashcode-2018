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
        std::size_t r1;
        std::size_t c1;
        std::size_t r2;
        std::size_t c2;

        friend std::ostream & operator<<(std::ostream& os, const Slice & s);
    };

    std::vector<Slice> s;
};

#endif // SLICES_H
