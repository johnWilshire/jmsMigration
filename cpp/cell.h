/* a cell in the simulaton 
cells can be in one of 8 states specifying 
predator prey densities at the current time step.

The states are:
0 - E - empty
1 - HA - few prey
2 - HB - increasing prey
3 - HC - many prey
4 - MA - many prey, few predators
5 - MB - many prey, increasing predators
6 - MC - many prey, many predators
7 - MD - few prey, many predators

Each cell is connected to 4 orthogonal neighbors, this space is modulo so
in 
| a | b | c |
| d | e | f |
| g | h | i |

a is connected to g, d, b, c
f is connected to i, c, d, e
*/

#ifndef CELL_H
#define CELL_H NULL
#define E 0
#define HA 1
#define HB 2
#define HC 3
#define MA 4
#define MB 5
#define MC 6
#define MD 7

#include <vector>

using namespace std;

class Cell {
public:
    // constructor
    Cell (int s);
    
    bool has_predators();
    bool has_many_predators();
    
    bool has_many_prey();
    bool has_life();
    void add_neighbor(Cell * c);
    
    int get_status();

    // based off the cells neighbours gets the next step for this cell
    void calc_next_status(double ph, double pp);
    void step_status();

    void print_info();

private:
    vector<Cell *> neighbors;
    // the current status of the cell
    int status;

    // the status that the cell will be at the next time step
    int next_status;
};

#endif