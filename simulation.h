#ifndef SIMULATON_H
#define SIMULATION_H

#include "cell.h"
#include <iostream>
#include <vector>

using namespace std;
class Simulation {
public:
    //constructor
    // x, y are the witdth and height of the model
    // ph is the prob that migration by the prey will occur
    // pp is the pron that migration by the predator will occur

    Simulation(int width, int height, double ph, double pp);

    int cells_with_predators();

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


    // a vector of all the cells in the sumulation
    vector<Cell> cells;

    // private methods

    int mod (int a, int b);
};

#endif