#ifndef IO_H
#define IO_H

#include "pizza.h"
#include "slices.h"

#include <string>

class IO
{
public:

    static void read_pizza(const std::string & path, Pizza ** out);

    static void write_slices(const std::string & path, const Slices & slices);
};

#endif // IO_H
