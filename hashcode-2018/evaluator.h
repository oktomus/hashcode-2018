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
    result.valid = true;
    result.score = 0;

    // Test validity
    const std::vector<std::vector<int>> & vehicule_rides = solution.vehicule_rides;

    // Compute score
    // Pour chaque vehicule
    for (int v = 0, n = vehicule_rides.size(); v < n; ++v)
    {
        const std::vector<int> & rides = vehicule_rides[v];
        // Pour chaque ride assigné
        for (int ri = 0, rn = rides.size(); ri < rn; ++ri)
        {
            const int ride_index = rides[ri];
            const Ride & ride = problem_data.rides[ride_index];

            // Simulation check
            if (ride.sim_end == -1 || ride.sim_start == -1)
            {
                std::cout << "    [CheckFail] Ride " << ride_index << " is assigned but never simulate\n";
                result.valid = false;
                return result;
            }

            if (ride.sim_start < ride.earliest)
            {
                std::cout << "    [CheckFail] Ride " << ride_index << " start before its earliest\n";
                result.valid = false;
                return result;
            }

            if (ride.sim_end >= problem_data.temps_total)
            {
                std::cout << "    [CheckFail] Ride " << ride_index << " end after simulation\n";
                result.valid = false;
                return result;
            }

            const int distance = abs(ride.a - ride.x) + abs(ride.b - ride.y);
            // Distance compute ok
            if (ride.sim_end - ride.sim_start + 1 != distance)
            {
                std::cout << "    [CheckFail] Ride " << ride_index << " simulation doesn't match with distance\n";
                result.valid = false;
                return result;
            }

            // Test if doesn' overlap with previous one
            if (ri > 0)
            {
                const int previous_ride_index = rides[ri - 1];
                const Ride & previous = problem_data.rides[previous_ride_index];

                const int rides_distance = abs(ride.a - previous.x) + abs(ride.b - previous.y);

                if (ride.sim_start < previous.sim_end)
                {
                    std::cout << "    [CheckFail] Ride " << ride_index << " start before its previous ride " << previous_ride_index << " ends\n";
                    result.valid = false;
                    return result;
                }

                const int times_distance = ride.sim_start - previous.sim_end;

                if (times_distance <= rides_distance)
                {
                    std::cout << "    [CheckFail] Ride " << ride_index << " start before arryving at its previous ride " << previous_ride_index << "\n";
                    result.valid = false;
                    return result;
                }
            }

            // Test if finished on time
            if (ride.sim_end < ride.finish)
            {
                result.score += distance;
                // Test if we have bonus
                if (ride.sim_start == ride.earliest)
                {
                    result.score += problem_data.bonus;
                }
            }
        }
    }

	return result;
}

// Tests

inline void test_evaluator()
{
    bool success = true;

	std::cout << "BEGIN TEST_EVALUATOR\n";
    // Definition a la main du problem
    DataContainer problem_data;

    problem_data.hauteur = 3;
    problem_data.largeur = 4;
    problem_data.nb_vehicules = 2;
    problem_data.nb_rides = 3;
    problem_data.bonus = 2;
    problem_data.temps_total = 10;

    Ride r1, r2, r3;
    r1.a = 0; r1.b = 0; r1.x = 1; r1.y = 3; r1.earliest = 2; r1.finish = 9;
    r2.a = 1; r2.b = 2; r2.x = 1; r2.y = 0; r2.earliest = 0; r2.finish = 9;
    r3.a = 2; r3.b = 0; r3.x = 2; r3.y = 2; r3.earliest = 0; r3.finish = 9;

    problem_data.rides = {r1, r2, r3};

    // Definition a la main de la solution
    DataSolution problem_solution(problem_data);

    {
        std::cout << "  [T1]\n";
        // Not matching distance with simulation
        problem_solution.vehicule_rides = {
            {0}, {}
        };

        problem_data.rides[0].sim_start = 0;
        problem_data.rides[0].sim_end = 8;
        SolutionScore score = calculate_score(problem_solution);

        if (score.valid)
        {
            success = false;
            std::cout << "    [X] should not have valid score\n";
        }
    }

    {
        std::cout << "  [T2]\n";
        // Not matching simulation and earliest
        problem_solution.vehicule_rides = {
            {0}, {}
        };

        problem_data.rides[0].sim_start = 0;
        problem_data.rides[0].sim_end = 5;
        SolutionScore score = calculate_score(problem_solution);

        if (score.valid)
        {
            success = false;
            std::cout << "    [X] should not have valid score\n";
        }
    }

    {
        std::cout << "  [T3]\n";
        // Correct + bonus
        problem_solution.vehicule_rides = {
            {0}, {}
        };

        problem_data.rides[0].sim_start = 2;
        problem_data.rides[0].sim_end = 5;
        SolutionScore score = calculate_score(problem_solution);

        if (!score.valid)
        {
            success = false;
            std::cout << "    [X] should have valid score\n";
        }

        if (score.score != 4 + 2)
        {
            success = false;
            std::cout << "    [X] wrong score " << 6 << " != " << score.score << "\n";
        }
    }
    {
        std::cout << "  [T4]\n";
        // Correct + not bonus
        problem_solution.vehicule_rides = {
            {0}, {}
        };

        problem_data.rides[0].sim_start = 3;
        problem_data.rides[0].sim_end = 6;
        SolutionScore score = calculate_score(problem_solution);

        if (!score.valid)
        {
            success = false;
            std::cout << "    [X] should have valid score\n";
        }

        if (score.score != 4)
        {
            success = false;
            std::cout << "    [X] wrong score " << 4 << " != " << score.score << "\n";
        }
    }
    {
        std::cout << "  [T5]\n";
        // One ride but out of simulation bounds
        problem_solution.vehicule_rides = {
            {0}, {}
        };

        problem_data.rides[0].sim_start = 6;
        problem_data.rides[0].sim_end = 10;
        SolutionScore score = calculate_score(problem_solution);

        if (score.valid)
        {
            success = false;
            std::cout << "    [X] should not have valid score\n";
        }
    }
    {
        std::cout << "  [T6]\n";
        // Two OK rides
        problem_solution.vehicule_rides = {
            {0}, {1}
        };
        problem_data.rides[0].sim_start = 2;
        problem_data.rides[0].sim_end = 5;
        problem_data.rides[1].sim_start = 0;
        problem_data.rides[1].sim_end = 1;
        SolutionScore score = calculate_score(problem_solution);
        if (!score.valid)
        {
            success = false;
            std::cout << "    [X] should have valid score\n";
        }
        if (score.score != 4 + 2 + 2 + 2)
        {
            success = false;
            std::cout << "    [X] wrong score " << 10 << " != " << score.score << "\n";
        }
    }
    {
        std::cout << "  [T7]\n";
        // Three OK rides
        problem_solution.vehicule_rides = {
            {0}, {2, 1}
        };
        problem_data.rides[0].sim_start = 2;
        problem_data.rides[0].sim_end = 5;
        problem_data.rides[2].sim_start = 0;
        problem_data.rides[2].sim_end = 1;
        problem_data.rides[1].sim_start = 3;
        problem_data.rides[1].sim_end = 4;
        SolutionScore score = calculate_score(problem_solution);
        if (!score.valid)
        {
            success = false;
            std::cout << "    [X] should have valid score\n";
        }
        if (score.score != 2 + 4 + 2 + 2 + 2)
        {
            success = false;
            std::cout << "    [X] wrong score " << 12 << " != " << score.score << "\n";
        }
    }
    {
        std::cout << "  [T7]\n";
        // Three rides with 2 overlapping rides
        problem_solution.vehicule_rides = {
            {0}, {2, 1}
        };
        problem_data.rides[0].sim_start = 2;
        problem_data.rides[0].sim_end = 5;
        problem_data.rides[2].sim_start = 0;
        problem_data.rides[2].sim_end = 1;
        problem_data.rides[1].sim_start = 2;
        problem_data.rides[1].sim_end = 3;
        SolutionScore score = calculate_score(problem_solution);
        if (score.valid)
        {
            success = false;
            std::cout << "    [X] should not have valid score\n";
        }
    }

    //problem_solution.

    DataSolution non_working_solution(problem_data);

	std::cout << "TEST_EVALUATOR: " << (success ? "OK": "FAIL") << "\n";
}

#endif // EVALUATOR_H
