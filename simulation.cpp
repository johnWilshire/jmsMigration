/*
    John WIlshire, Dec, 2015
    Simulaton of Migration Model
    outlined in J. Maynard Smiths's "Models in Ecology" pg 75
*/

#include <iostream>
#include <vector>
#include "simulation.h"
#include "cell.h"

using namespace std;

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

            Cell* r = get_cell(mod((j + 1), width), i); //right
            Cell* l = get_cell(mod((j - 1), width), i); //left
            Cell* u = get_cell(j, mod((i + 1), width)); //up
            Cell* d = get_cell(j, mod((i - 1), width)); //down

            me->add_neighbor(r);
            me->add_neighbor(l);
            me->add_neighbor(u);
            me->add_neighbor(d);
        }
    }

}

/*
    prints a visual representation of the simulation.
*/
void Simulation::print_cells(){
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
            if (get_cell(i, j)->has_predators()){
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


int main(int argc, char* argv[]){
    int id = 0;
    cout << "id,age, cells_with_predators, ph, pp" << endl;
    for(double ph = 0.01; ph < 1.0; ph += 0.01){
        for(double pp = 0.01; pp < 1.0; pp += 0.01){
            Simulation s = {10, 10, ph, pp};
            for(int i = 0; i < 100; i++){
                cout << id << "," << s.get_age() << "," << s.cells_with_predators() 
                        << "," << ph <<","<< pp << endl;
                s.step_age();
            }
            id++;
        }
    }
    
    return 0;
}
