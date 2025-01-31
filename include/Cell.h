#ifndef CELL_H
#define CELL_H

class Cell {
public:
    Cell();
    bool isMine() const; // const = this function does not modify a variable of the object
    bool isRevealed() const;
    bool setRevealed(bool revealed);
    bool isFlagged() const;
    void setFlagged(bool flagged);
    int getAdjacentMines() const;
    void setAdjacentMines(int adjacentMines);
    void setMine(bool mine);
    void isExploded();
    void setExploded(bool exploded);
    char getSymbol() const;

private:
    bool mine = false;
    bool revealed = false;
    bool flagged = false;
    int adjacentMines = 0;
    bool exploded = false;
};

#endif