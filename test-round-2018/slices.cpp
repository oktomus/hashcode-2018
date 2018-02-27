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
