#ifndef CELL_H
#define CELL_H


// a cell in the model
class Cell {
public:
    // constructor
    Cell (int x, int y, int s);
    bool has_predators();
    void set_neiborhood(Cell* neighbors);

    int get_status();

private:
    Cell* neighbors[];
    int x, y;
    int status_num;
};

#endif