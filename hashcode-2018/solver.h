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

    inline int ajoutPossible(const std::vector<int> &current_rides, Ride &ride)
    {
        // ajout possible si la voiture n'est pas occupe avant la fin.
        // en first ?

        ride.sim_start = ride.earliest;
        ride.sim_end = ride.sim_start + abs(ride.a - ride.x) + abs(ride.b - ride.y) - 1;

        if(ride.sim_end <= problem_data.rides.at(current_rides.at(0)).sim_start)
            return 0;

        // au milieu ?

        // en last ?

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

        // on assigne le premier ride random
        for(i=0;i<problem_data.nb_rides;++i)
        {
            // Pour chaque ride prit dans un ordre aleatoire
            Ride &ride = problem_data.rides.at(ridesId.at(i));
            std::random_shuffle(vehiculesId.begin(),vehiculesId.end());

            // on assige un ride a un vehicule
            std::vector<int> r;
            r.push_back(ridesId.at(i));
            vehicule_rides.push_back(r);
            ride.sim_start = ride.earliest;
            ride.sim_end = ride.sim_start + abs(ride.a - ride.x) + abs(ride.b - ride.y) - 1;
            if(vehicule_rides.size()>=problem_data.nb_vehicules)
                break;
        }
        // on essaye d'ajouter les ride restants
        for(;i<problem_data.nb_rides;++i)
        {
            // Pour chaque ride prit dans un ordre aleatoire
            Ride &ride = problem_data.rides.at(ridesId.at(i));
            std::random_shuffle(vehiculesId.begin(),vehiculesId.end());

            // on cherche une voiture a qui l'assigner
            for(j=0;j<problem_data.nb_vehicules;++j)
            {
                std::vector<int> current_rides;
                current_rides = vehicule_rides.at(vehiculesId.at(j));
                // si assignable
                int x = ajoutPossible(current_rides,ride);
                if(x != -1)
                {
                    // on ajoute (sinon next)
                    (vehicule_rides.at(vehiculesId.at(j))).insert((vehicule_rides.at(vehiculesId.at(j))).begin()+x, ridesId.at(i));
                    continue;
                }
            }
        }
    }

    inline void resolve3()
    {
       // Main ALGORITHM
        std::srand(std::chrono::system_clock::now().time_since_epoch().count());

        int i, j;

        // Ordre des rides
        std::vector<int> ridesId;
        for(i=0;i<problem_data.nb_rides;++i)
            ridesId.push_back(i);
        std::random_shuffle(ridesId.begin(),ridesId.end());

        vehicule_rides.resize(problem_data.nb_vehicules);

        int choix_vehicule;

        while(ridesId.size() > 0)
        {
            // Pour chaque ride prit dans un ordre aleatoire
            int rand_id = random_int(0, ridesId.size() - 1);
            int ride_id = ridesId.at(rand_id);
            Ride &ride = problem_data.rides.at(ride_id);

            choix_vehicule = -1;
            // Prendre un vehiculle dispo
            for(int v = 0; v < vehicule_rides.size(); ++v)
            {
                const std::vector<int> & rides_for_this_vehicle = vehicule_rides[v];

                if (rides_for_this_vehicle.size() == 0)
                {
                    choix_vehicule = v;
                    ride.sim_start = ride.earliest;
                    ride.sim_end = ride.sim_start + abs(ride.a - ride.x) + abs(ride.b - ride.y) - 1;
                    break;
                }

                const int last_ride_id = rides_for_this_vehicle[rides_for_this_vehicle.size() - 1];
                const Ride & last_ride = problem_data.rides[last_ride_id];

                int time_distance = ride.earliest - last_ride.sim_end;
                int euc_distance = abs(last_ride.x - ride.a) + abs(last_ride.y - ride.b);

                if (time_distance > euc_distance)
                {
                    choix_vehicule = v;
                    ride.sim_start = std::max(ride.earliest, last_ride.sim_end + euc_distance + 1);
                    ride.sim_end = ride.sim_start + abs(ride.a - ride.x) + abs(ride.b - ride.y) - 1;
                    break;
                }
            }

            ride.sim_done += 1;

            if (choix_vehicule == -1)
            {
                // On oublie ce ride
                if(ride.sim_done >= 10)
                {
                    ridesId.erase(ridesId.begin() + rand_id);
                }
            }
            else
            {
                // on assige un ride a un vehicule
                vehicule_rides[choix_vehicule].push_back(ride_id);
                ridesId.erase(ridesId.begin() + rand_id);

            }
        }
    }
};

#endif
