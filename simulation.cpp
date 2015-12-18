/*
    John WIlshire, Dec, 2015
    Simulaton of Migration Model
    outlined in J. Maynard Smiths's "Models in Ecology" pg 75
*/

#include <iostream>
#include <vector>
#include <typeinfo>
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
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int status = ((i + j) % 2 == 0) ? 1 : 0;
            cells.push_back(Cell {i, j, status});
        }
    }

    // set the neighbourhood of the cells

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


void Simulation::print_cells(){
    cout << "_";
    for (int j = 0; j < width; j++) cout << "__";
    cout << endl;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            cout << "|";
            cout << get_cell(j, i)->get_status();
        }
        cout << "|" << endl;
    }
    cout << endl;

}

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
            get_cell(j, i)->calc_next_status();
        }
    }

    for(int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            get_cell(j, i)->step_status();
        }
    }
    
    age++;
}

// s
Cell* Simulation::get_cell(int x, int y){
    return &cells[y*width +  x];
}


int main(){
    Simulation s = {10, 10, 0.1, 0.1};
    cout << "num has_predators " << s.cells_with_predators() << endl;
    cout << "age: " << s.get_age() << endl;
    s.print_cells();
    s.step_age();
    s.print_cells();
    s.get_cell(1,1)->print_info();
    return 0;
}
