#include "cell.h"

#include <iostream>
#include <cmath>

using namespace std;
// Constructor, s is the State
Cell::Cell (int x, int y, int s){
    this->x = x;
    this->y = y;

    this->status_num = s;
}

// true if the cell has predators in it
bool Cell::has_predators(){
    return (status_num >= MA && status_num <= MD);
}

bool Cell::has_many_predators(){
    return (status_num >= MB && status_num <= MD);
}


bool Cell::has_many_prey(){
    return (status_num >= HC && status_num <= MC);
}

int Cell::get_status(){
    return status_num;
}

int Cell::get_x(){
    return x;
}
int Cell::get_y(){
    return y;
}

void Cell::calc_next_status(){
    // the number of neighboring cells that have many prey
    double r = 0.0;    
    // the number of cells that have many predators
    double s = 0.0;

    for (int i = 0; i < neighbors.length(); i++){
        Cell* n = neighbors[i];
        if(n->has_many_prey()) r += 1.0;
        if(n->has_many_predators()) s += 1.0;
    }


    switch(status_num){
        case(E){}
    }

    next_status += status_num + 1;
}

void Cell::step_status(){
    status_num = next_status;
}


void Cell::print_info(){
    cout << "(" << x << ","<< y <<  ")" << " : " << status_num << endl;
}

void Cell::set_status(int status){
    this-> status_num = status;
}

void Cell::add_neighbor(Cell * c){
    neighbors.push_back(c);
}
