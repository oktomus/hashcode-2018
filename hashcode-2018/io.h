#ifndef IO_H
#define IO_H

#include "data.h"
#include "solver.h"

#include <cassert>
#include <fstream>
#include <iostream>

inline void read_input_file(const std::string &filename, DataContainer & output)
{
    std::ifstream reader(filename.c_str());

	if (!reader.is_open())
	{
		std::cout << "Can't open file for reading at: " << filename << std::endl;
		exit(2);
	}

	// reader >> output.something...

    reader.close();
}

inline void export_solution_file(const std::string & filename, const DataSolution & problem_solution)
{
    std::ofstream writer(filename.c_str());

	if (!writer.is_open())
	{
		std::cout << "Can't open file for writing at: " << filename << std::endl;
		exit(2);
	}

	const DataContainer & data_problem = problem_solution.problem_data;

	// solution.something >> writer ...

    writer.close();
}

// Tests

inline void test_reader()
{
	std::cout << "BEGIN TEST_READER\n";
	std::string file = "exemple.in";
	DataContainer problem_data;

	read_input_file(file, problem_data);

	bool success = true;

	/*
	if (problem_data.something != expected)
	{
		std::cout << "  Fail on pizza ingredients\n";
		success = false;
	}
	*/

	std::cout << "TEST_READER: " << (success ? "OK": "FAIL") << "\n";
}

#endif // IO_H
