#ifndef SOLVER_H
#define SOLVER_H

#include "data.h"

#include <limits>
#include <algorithm>

inline int random_int(const int & min, const int & max)
{
	static std::uniform_int_distribution<int> randomize(0, 100);
    static std::default_random_engine generator;
	static bool first = true;

	if (first)
	{
        generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
		first = false;
	}

	if (randomize.a() != min || randomize.b() != max)
	{
		randomize = std::uniform_int_distribution<int>(min, max);
	}

	return randomize(generator);

}

class DataSolution
{
public:
	DataSolution(DataContainer & input_data) :
	    problem_data(input_data)
	{
	}

	// Les donnes du sujets
	// Nom des variables, minuscules avec underscore, ex: ingredients_pizza

	DataContainer & problem_data; // Ne pas modifier les data des bases si possible

    std::vector<std::vector<int>> vehicule_rides; // [0, F-1]

	// Methodes

	inline void resolve()
	{
		// Main ALGORITHM
	}
};

#endif // SOLVER_H
