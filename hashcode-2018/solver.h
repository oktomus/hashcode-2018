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

    inline int ajoutPossible(const std::vector<int> &current_rides, const Ride &ride)
    {
        // ajout possible si la voiture n'est pas occupe avant la fin.



        return -1;
    }

    inline void resolve2()
    {
        // Main ALGORITHM
        std::srand(std::chrono::system_clock::now().time_since_epoch().count());

        int i, j;

        // Ordre des rides
        std::vector<int> ridesId;
        for(i=0;i<problem_data.nb_rides;++i)
            ridesId.push_back(i);
        std::random_shuffle(ridesId.begin(),ridesId.end());

        // Ordre des vehicules
        std::vector<int> vehiculesId;
        for(i=0;i<problem_data.nb_vehicules;++i)
            vehiculesId.push_back(i);

        for(i=0;i<problem_data.nb_rides;++i)
        {
            // Pour chaque ride prit dans un ordre aleatoire
            const Ride &ride = problem_data.rides.at(ridesId.at(i));

            std::random_shuffle(vehiculesId.begin(),vehiculesId.end());

            /*
            // On cherche une voiture assignable

            for(j=0;j<problem_data.nb_vehicules;++j)
            {
                const std::vector<int> &current_rides = vehicule_rides.at(vehiculesId.at(j));

                if(ajoutPossible(current_rides, ride) != -1)
                {
                    // si on peut ajouter alors on le fait
                    // vehicule_rides.at(vehiculesId.at(i))
                }
            }
            */
            // on assige un ride a un vehicule
            std::vector<int> r;
            r.push_back(ridesId.at(i));
            vehicule_rides.push_back(r);

            if(vehicule_rides.size()>=problem_data.nb_vehicules)
                return;
        }

        /*
        for(i=0;i<ridesId.size();++i)
            std::cout << ridesId.at(i) << " ";
        std::cout << std::endl;
        */
    }
};

#endif // SOLVER_H
