#ifndef IO_H
#define IO_H

#include "pizza.h"

#include <string>

class IO
{
public:

    static void read_pizza(const std::string & path, Pizza * out);

};

#endif // IO_H
