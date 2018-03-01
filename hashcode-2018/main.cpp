#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <map>
#include <fstream>
#include <cassert>
#include <limits>
#include <algorithm>
#include <sstream>

#include "data.h"
#include "evaluator.h"
#include "io.h"
#include "solver.h"

int main()
{
	// Definir le working path de QT sur : data/hashcode-2018

	// Tests
    /*
	test_reader();
	std::cout << "\n";
    test_export();
    std::cout << "\n";
    */
	test_evaluator();
	std::cout << "\n";

	// Input data files
    std::vector<std::string> fichiers = {
        "a_example.in",
        "b_should_be_easy.in",
        "c_no_hurry.in",
        "d_metropolis.in",
        "e_high_bonus.in"
    };

	// Number of generation per file
	std::vector<std::size_t> iterations =
	{
        10000,
        10000,
        10000,
        10000,
        10000
    };

	assert(fichiers.size() == iterations.size());

    for(std::size_t i = 0; i < fichiers.size(); i++)
    {
		std::string fichier = fichiers[i];
        std::string output_path = fichier.substr(0, fichier.find_last_of('.')) + ".out";
        std::string fail_output_path = fichier.substr(0, fichier.find_last_of('.')) + ".out.fail";

		// Import
		DataContainer problem_data;
        read_input_file(fichier, problem_data);

		// Resolve iterations times
		std::size_t problem_iterations = iterations[i];

		SolutionScore last_score;

		std::cout << "[" << fichier << "]:\n";

		for(std::size_t j = 0; j < problem_iterations; j++)
		{
			DataSolution problem_solution(problem_data);
            problem_solution.resolve3();

			SolutionScore score = calculate_score(problem_solution);

            // Debug du score et validite
            /*
			std::cout << "  [Iteration " << j << "]: " <<
                (score.valid ? "OK " : "FAIL ")
                << ", SCORE= " << score.score << '\n';
            */

			// Export if better or first
			if (j == 0 ||
			    (score.valid && !last_score.valid) ||
			    (score.valid && score.score > last_score.score))
			{
				last_score = score;
				export_solution_file(output_path, problem_solution);
                std::cout << "  -> Exported to " << output_path << " "
                          << score.score << std::endl;
			}
		}

		std::cout << "[" << fichier << "]: " <<
                (last_score.valid ? "OK " : "FAIL ")
                << ", BEST_SCORE= " << last_score.score << '\n';
    }

    return 0;
}
