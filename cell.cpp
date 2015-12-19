#include "cell.h"

#include <iostream>
#include <cmath>

using namespace std;
// Constructor, s is the State
Cell::Cell ( int s){
    this->status = s;
}

// true if the cell has predators in it
bool Cell::has_predators(){
    return (status >= MA && status <= MD);
}

bool Cell::has_many_predators(){
    return (status >= MB && status <= MD);
}


bool Cell::has_many_prey(){
    return (status >= HC && status <= MC);
}

int Cell::get_status(){
    return status;
}

void Cell::calc_next_status(double ph, double pp){
    // the number of neighboring cells that have many prey
    double r = 0.0;    
    // the number of cells that have many predators
    double s = 0.0;

    for (int i = 0; i < (int)neighbors.size(); i++){
        Cell* n = neighbors[i];
        if(n->has_many_prey()) r += 1.0;
        if(n->has_many_predators()) s += 1.0;
    }

    double prob_prey_migration = 1.0 - pow((1.0 - ph), r);
    double prob_pred_migration = 1.0 - pow((1.0 - pp), s);
    double prob = rand() / (double)RAND_MAX;
    
    /*
    cout << "rand: "<< prob << endl;
    cout << "prob_pred_migration: "<< prob_pred_migration << endl;
    cout << "prob_prey_migration: "<< prob_prey_migration << endl;
    cout << "r: "<< r << " s: "<< s << endl;
    */
    // transitions
    switch(status){
        case E:
            if (prob < prob_prey_migration){
                next_status = HA;
            } else {
                next_status = E;
            }
            break;
        case HA:
            if (prob < prob_pred_migration){
                next_status = MA;
            } else {
                next_status = HB;
            }
            break;
        case HB:
            if (prob < prob_pred_migration){
                next_status = MA;
            } else {
                next_status = HC;
            }
            break;
        case HC:
            if (prob < prob_pred_migration){
                next_status = MA;
            } else {
                next_status = HC;
            }
            break;
        case MA:
            next_status = MB;
            break;
        case MB:
            next_status = MC;
            break;
        case MC:
            next_status = MD;
            break;
        case MD:
            next_status = E;
            break;
    }
}

void Cell::step_status(){
    status = next_status;
}

void Cell::add_neighbor(Cell * c){
    neighbors.push_back(c);
}
