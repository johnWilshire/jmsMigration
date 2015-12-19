/*
    John WIlshire, Dec, 2015
    Simulaton of Migration Model
    outlined in J. Maynard Smiths's "Models in Ecology" pg 75
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "simulation.h"
#include "cell.h"


using namespace std;

int main(int argc, char* argv[]){
    int iterations = 100;
    
    double start = 0.01;
    double end = 1.0;
    double step = 0.01;

    string filename = "100_100_";
    
    // open files
    ofstream predator_means;
    ofstream predators_ts; // time series
    ofstream life_means;
    
    predator_means.open(filename + "_predator_means.csv");
    predators_ts.open(filename + "_predators_ts.csv");
    life_means.open(filename + "_life_means.csv");

    // headers
    predator_means << "id,mean_predators,ph,pp"<< endl;
    life_means << "id,mean_life,ph,pp"<< endl;
    predators_ts << "id,age,cells_with_predators,ph,pp"<< endl; 

    int id = 0;
    for(double ph = start; ph < end; ph += step){
        cout << ph*100.0 << "% done " << endl;
        for(double pp = start; pp < end; pp += step){
            Simulation s = {10, 10, ph, pp};
            double sum_predators = 0;
            double sum_life = 0;
            for(int i = 0; i < iterations; i++){
                int with_predators = s.cells_with_predators();
                int with_life = s.cells_with_life();
                predators_ts << id << "," << s.get_age() << "," << with_predators
                        << "," << ph <<","<< pp << endl;
                sum_predators += (double)with_predators;
                sum_life += (double)with_life;
                s.step_age();
            }
            predator_means << id << "," << sum_predators/(double)iterations << "," << ph << "," << pp << endl;
            life_means << id << "," << sum_life/(double)iterations << "," << ph << "," << pp << endl;
            id++;
        }
    }
    
    return 0;
}


/*
    Constructor:
    width of the simulation
    height of the simulaton
    invasion probability parameter for prey
    invasion probability parameter for predators
*/
Simulation::Simulation(int w, int h, double ph, double pp)
{
    age = 0;

    this->width = w;
    this->height = h;

    this->pp = pp;
    this->ph = ph;

    // inst all cells
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int status = ((i + j) % 2 == 0) ? HA : E;
            if (status == E) status = (i % 5 == 0) ? MA : E;
            cells.push_back(Cell { status });
        }
    }

    // connect each cell to its four closest 
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            Cell* me = get_cell(j,i);

            me->add_neighbor(get_cell(mod((j + 1), width), i)); //right
            me->add_neighbor(get_cell(mod((j - 1), width), i)); //left
            me->add_neighbor(get_cell(j, mod((i + 1), width))); //up
            me->add_neighbor(get_cell(j, mod((i - 1), width))); //down
        }
    }
}

/*
    prints a visual representation of the simulation.
*/
void Simulation::print_cells () {
    cout << "_";
    for (int j = 0; j < width; j++) cout << "___";
    cout << endl;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            cout << "|";
            cout << symbols[get_cell(j, i)->get_status()];
        }
        cout << "|" << endl;
    }
    cout << endl;
}

// returns the number of cells with predators (MA..MD).
int Simulation::cells_with_predators(){
    int count = 0;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (get_cell(j, i)->has_predators()){
                count++;
            }
        }
    }
    return count;
}

// returns the number of cells that are alive (!E).
int Simulation::cells_with_life(){
    int count = 0;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (get_cell(j, i)->has_life()){
                count++;
            }
        }
    }
    return count;
}

// returns the current age of the model
int Simulation::get_age(){
    return age;
}


// % doesnt work when you want negative numbers
int Simulation::mod(int a, int b){
    return (a % b + b) % b;
}

// steps the models age forward through time by 1 unit
void Simulation::step_age(){
    for(int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            get_cell(j, i)->calc_next_status(ph, pp);
        }
    }
    for(int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            get_cell(j, i)->step_status();
        }
    }
    age++;
}

// returns a pointer the cell at (x, y)
Cell* Simulation::get_cell(int x, int y){
    return &cells[y*width +  x];
}