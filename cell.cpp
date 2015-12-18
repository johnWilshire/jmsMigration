#include "cell.h"

#include <iostream>

using namespace std;
// Constructor, s is the State
Cell::Cell (int x, int y, int s){
    this->x = x;
    this->y = y;

    this->status_num = s;
}

// true if the cell has predators in it
bool Cell::has_predators(){
    return (status_num > 4 && status_num < 8);
}

int Cell::get_status(){
    return status_num;
}



void Cell::set_neiborhood(Cell* neighbors){
    cout << "setting neighbors" <<  endl;
    //this->neighbors = neighbors;
}
