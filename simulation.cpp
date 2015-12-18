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

Simulation::Simulation(int w, int h, double ph, double pp)
{
    age = 0;

    this->width = w;
    this->height = h;

    this->pp = pp;
    this->ph = ph;
    cout << "width:\t" << width << "\theight:\t" << height << endl;
    cout << "pp:\t" << pp << "\tph:\t" << ph << endl;
    // inst all cells
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            int status = ((i + j) % 2 == 0) ? 0 : 1;
            cells.push_back(Cell {i, j, status});
        }
    }

    // set the neightb
}


void Simulation::print_cells(){
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            cout << "|";
            cout << get_cell(i,j)->get_status();
        }
        cout << "|"<< endl;
    }

}

int Simulation::cells_with_predators(){
    int count = 0;
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
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

// steps the models age forward through time by 1 unit
void Simulation::step_age(){
    age++;
}

// s
Cell* Simulation::get_cell(int x, int y){
    return &cells[x*width +  y];
}


int main(){
    Simulation s = {5, 5, 0.1, 0.1};
    cout << "num has_predators " << s.cells_with_predators() << endl;
    cout << "age: " << s.get_age() << endl;
    s.print_cells();
    return 0;
}
