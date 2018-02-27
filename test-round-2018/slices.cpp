#include "slices.h"

Slices::Slices()
{

}

std::ostream &operator<<(std::ostream &os, Slices::Slice &s)
{
    os << s.r1 << " ";
    os << s.c1 << " ";
    os << s.r2 << " ";
    os << s.c2 << " ";
    os << std::endl;

    return os;
}

bool Slices::Slice::contains(const std::size_t &r, const std::size_t &c) const
{
    return r >= r1 && r <= r2 && c >= c1 && c <= c2;
}
