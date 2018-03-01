#ifndef DATA_H
#define DATA_H

#include <vector>
#include <map>

class Ride
{
    int a, b; // Ligne, colonne
    int x, y; // Ligne, colonne
    int earliest;
    int finish;
};

class DataContainer
{
public:
	// Pas besoin de constructeurs

	// Les donnes du sujets
	// Nom des variables, minuscules avec underscore, ex: ingredients_pizza

    int hauteur; // R [0, R-1]
    int largeur; // C [0, C-1]
    int nb_vehicules; // F
    int nb_rides; // N
    int bonus; // B
    int temps_total; // T
    std::vector<Ride> rides; // [0, N-1]
};

#endif // DATA_H
