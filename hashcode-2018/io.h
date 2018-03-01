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
    int i;
    Ride ride;

	if (!reader.is_open())
	{
		std::cout << "Can't open file for reading at: " << filename << std::endl;
		exit(2);
	}

	// reader >> output.something...

    reader >> output.hauteur;
    reader >> output.largeur;
    reader >> output.nb_vehicules;
    reader >> output.nb_rides;
    reader >> output.bonus;
    reader >> output.temps_total;

    for(i=0;i<output.nb_rides;++i)
    {
        reader >> ride.a;
        reader >> ride.b;
        reader >> ride.x;
        reader >> ride.y;
        reader >> ride.earliest;
        reader >> ride.finish;
        ride.sim_end = -1;
        ride.sim_start = -1;
        output.rides.push_back(ride);
    }

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

    // const DataContainer & data_problem = problem_solution.problem_data;

	// solution.something >> writer ...

    if((int)problem_solution.vehicule_rides.size() != problem_solution.problem_data.nb_vehicules)
        std::cout << "-- WARNING -- : - OUTPUT 1 -" << std::endl;

    std::size_t i, j;

    for(i=0;i<problem_solution.vehicule_rides.size();++i)
    {
        const std::vector<int> &ptrRides = problem_solution.vehicule_rides.at(i);

        writer << ((int)ptrRides.size()) << " ";

        for(j=0;j<ptrRides.size();++j)
        {
            writer << ptrRides.at(j) << " ";
        }

        writer << std::endl;
    }

    writer.close();
}

// Tests

inline void test_reader()
{
    std::cout << "BEGIN TEST_READER\n";
    std::string file = "a_example.in";
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

inline void test_export()
{
    std::cout << "BEGIN TEST_EXPORT\n";
    std::string file = "a_example.out.test";
    std::string file_in = "a_example.in";

    DataContainer problem_data;
    read_input_file(file_in, problem_data);

    DataSolution problem_solution(problem_data);

    std::vector<int> tmp;
    tmp.push_back(0);
    problem_solution.vehicule_rides.push_back(tmp);
    tmp.clear();
    tmp.push_back(2);
    tmp.push_back(1);
    problem_solution.vehicule_rides.push_back(tmp);

    export_solution_file(file, problem_solution);

    bool success = true;

    /*
    if (problem_data.something != expected)
    {
        std::cout << "  Fail on pizza ingredients\n";
        success = false;
    }
    */

    std::cout << "TEST_EXPORT: " << (success ? "OK": "FAIL") << "\n";
}

#endif // IO_H
