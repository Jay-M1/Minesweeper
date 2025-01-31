#ifndef FIELD_H
#define FIELD_H
#include <vector>
#include "Cell.h"

class Field {

public:
    Field();
    Field(int rows, int cols);
    void setRows(int rows);
    int getRows() const;
    void setCols(int cols);
    int getCols() const;
    void setVector();
    std::vector<std::vector<Cell>> getVector() const;

private:
    int rows;
    int cols;
    std::vector<std::vector<Cell>> vector;

};

#endif