/*
    John WIlshire, Dec, 2015
    Simulaton of Migration Model
    outlined in J. Maynard Smiths's "Models in Ecology" pg 75
*/

#ifndef SIMULATION_H
#define SIMULATION_H

#include "cell.h"
#include <iostream>
#include <vector>

using namespace std;
class Simulation {
public:
    /*
        Constructor:
        width of the simulation
        height of the simulaton
        invasion probability parameter for prey
        invasion probability parameter for predators
    */
    Simulation(int width, int height, double ph, double pp);

    int cells_with_predators();
    int cells_with_life();

    int get_age();
    void step_age();

    void print_cells();

    // returns the cell at the specified coordinates
    Cell* get_cell(int x, int y);

private:
    // vars
    // the dimensions of the simulation
    int width, height;

    double pp, ph;

    // int specifying the number of timesteps taken
    int age;

    // the symbols that are printed in print_cells co-orsponding to different states
    string symbols[8] = {
    "  ",
    "HA",
    "HB",
    "HC",
    "MA",
    "MB",
    "MC",
    "MD"
    };

    // a vector of all the cells in the sumulation
    vector<Cell> cells;

    // private methods

    int mod (int a, int b);
};

#endif