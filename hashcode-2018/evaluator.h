#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "data.h"
#include "solver.h"
#include "io.h"

#include <string>

class SolutionScore
{
public:
	bool valid;
	int score;
};

inline SolutionScore calculate_score(const DataSolution & solution)
{
	const DataContainer & problem_data = solution.problem_data;

	SolutionScore result;
	result.valid = false;
	result.score = 0;

	return result;
}

// Tests

inline void test_evaluator()
{
	bool success = success;

	std::cout << "BEGIN TEST_EVALUATOR\n";
    // Definition a la main du problem
    DataContainer problem_data;

    // Definition a la main de la solution
    DataSolution problem_solution(problem_data);
    // ...
    DataSolution non_working_solution(problem_data);
    // ...


    // Tests
    SolutionScore score = calculate_score(problem_solution);

	if (!score.valid)
	{
		success = false;
		std::cout << "  Correct solution should have valid score\n";
	}
	if (score.score != 10)
	{
		success = false;
		std::cout << "  Correct solution should have score of 10\n";
	}

    SolutionScore non_score = calculate_score(non_working_solution);

	if (score.valid)
	{
		success = false;
		std::cout << "  Wrong solution should have non valid score\n";
	}

	std::cout << "TEST_EVALUATOR: " << (success ? "OK": "FAIL") << "\n";
}

#endif // EVALUATOR_H
