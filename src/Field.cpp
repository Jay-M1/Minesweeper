#include "../include/Field.h"

Field::Field() : rows(0), cols(0) {}

Field::Field(int rows, int cols) : rows(rows), cols(cols) {
    setVector();
}

void Field::setRows(int rows) {
    this->rows = rows;
}

int Field::getRows() const {
    return rows;
}

void Field::setCols(int cols) {
    this->cols = cols;
}

int Field::getCols() const {
    return cols;
}

void Field::setVector() {
    std::vector<std::vector<Cell>> vector(rows, std::vector<Cell>(cols));
    this->vector = vector;
}

std::vector<std::vector<Cell>> Field::getVector() const {
    return vector;
}