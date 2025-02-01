#include "../include/Cell.h"

Cell::Cell() : mine(false), revealed(false), flagged(false), adjacentMines(0) {}

bool Cell::isMine() const {
    return mine;
}

bool Cell::isRevealed() const{
    return revealed;
}

bool Cell::setRevealed(bool revealed) {
    this->revealed = revealed;
    return revealed;
}

bool Cell::isFlagged() const {
    return flagged;
}

void Cell::setFlagged(bool flagged) {
    this->flagged = flagged;
}

int Cell::getAdjacentMines() const {
    return adjacentMines;
}

void Cell::setAdjacentMines(int adjacentMines) {
    this->adjacentMines = adjacentMines;
}

void Cell::setMine(bool mine) {
    this->mine = mine;
}

void Cell::isExploded() {
    this->exploded = false;
}

void Cell::setExploded(bool exploded) {
    this->exploded = exploded;
}

char Cell::getSymbol() const {
    if (flagged && !revealed) {
        return 'F';
    }
    else if (revealed && mine || exploded) {
        return 'X';
    }
    else if (!revealed) {
        return '#';
    }
    else {
        return '0' + adjacentMines;
    }
    
}