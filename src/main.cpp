#include <iostream>
#include <vector>
#include "../include/Cell.h"
#include "../include/Field.h"
#include <random>
#include <tuple>
#include <cstdlib> // for system()
#include <iomanip> // for setw()
#include <ctime> // time for random seed

void PrintBanner();
std::tuple<int,int,float> Determine_difficulty();
void GetCellUpdate(Cell cell);
char GetUserCellInteraction();
int GetUserNumberSelection(int limit);
int getTerminalWidth();
void PlaceMines(std::vector<std::vector<Cell>>& field, int numMines);

int main (int argc, char* argv[]) {

    // create field
    PrintBanner();
    std::tuple<int,int,float> dimension = Determine_difficulty();
    float diff = std::get<2>(dimension);
    int rows = std::get<0>(dimension);
    int cols = std::get<1>(dimension);
    Field MyField(rows, cols);
    std::vector<std::vector<Cell>> vector = MyField.getVector();

    // distribute mines
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (dis(gen) < diff) {
                vector[i][j].setMine(true);
            } else {
                vector[i][j].setMine(false);
            }
        }
    }

    // center field
    int terminalWidth = getTerminalWidth();
    int fieldWidth = cols * 1; // Assuming each cell takes 2 characters (1 for symbol and 1 for space)
    int padding = (terminalWidth - fieldWidth) / 2;

    // game loop
    bool game_over = false;

    for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                
                // count adjacent Mines
                int adjacentMines = 0;           
                for (int k = i-1; k <= i+1; k++) {
                    if (k >= rows || k < 0) {continue;} // catching if it is on the margin

                    for (int l = j-1; l<= j+1; l++) {
                        if (l > cols || l < 0) {continue;} // catching
                        
                        if (vector[k][l].isMine()){adjacentMines++;}
                    }
                }

                // set adjacent mines
                vector[i][j].setAdjacentMines(adjacentMines);

            }
          
        }

    while (true) {

        // Clear the terminal
        std::cout << "\033[2J\033[H";
        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;

        // loop over cells
        for (int counts = 0; counts < 4; counts++){
            for (int i = 0; i < rows; i++) {
                if (counts==3){std::cout << std::setw(padding) << "";}
                for (int j = 0; j < cols; j++) {
                    
                    // reveal adjacent cells if no adjacent mines
                    if (vector[i][j].getAdjacentMines() == 0 && vector[i][j].isRevealed() && !vector[i][j].isMine()) {
                        
                        for (int k = i-1; k <= i+1; k++) {
                            if (k >= rows || k < 0) {continue;} // catching if it is on the margin
                            for (int l = j-1; l<= j+1; l++) {
                                if (l > cols || l < 0) {continue;} // catching
                                vector[k][l].setRevealed(true);
                            }
                        }
                    }

                    if (counts==3){std::cout << vector[i][j].getSymbol() << " ";}

                }
                if (counts==3){std::cout << std::endl;}
            }
        }


        // break out if game over
        if (game_over) {break;}

        // otherwise get entered value of the user
        int userRowSelection = GetUserNumberSelection(rows);
        int userColumnSelection = GetUserNumberSelection(cols);
        char userCellInteraction = GetUserCellInteraction();
        
        // act depending on user input
        // f
        if (userCellInteraction == 'f') {
            if (vector[userRowSelection][userColumnSelection].isFlagged()) {
                vector[userRowSelection][userColumnSelection].setFlagged(false);}
            else {
                vector[userRowSelection][userColumnSelection].setFlagged(true);
            }
            }

        // r
        if (userCellInteraction == 'r') {

            // reveal
            vector[userRowSelection][userColumnSelection].setRevealed(true);

            // if mine
            if (vector[userRowSelection][userColumnSelection].isMine()) {

                vector[userRowSelection][userColumnSelection].setExploded(true);
                std::cout << "You hit a mine! Game over." << std::endl;
                game_over = true;
            }
        }
    }

    return 0;
}















void PrintBanner() {
    std::cout << R"(88b           d88  88                                                                                                                      
888b         d888  ""                                                                                                                      
88`8b       d8'88                                                                                                                          
88 `8b     d8' 88  88  8b,dPPYba,    ,adPPYba,  ,adPPYba,  8b      db      d8   ,adPPYba,   ,adPPYba,  8b,dPPYba,    ,adPPYba,  8b,dPPYba, 
88  `8b   d8'  88  88  88P'   `"8a  a8P_____88  I8[    ""  `8b    d88b    d8'  a8P_____88  a8P_____88  88P'    "8a  a8P_____88  88P'   "Y8 
88   `8b d8'   88  88  88       88  8PP"""""""   `"Y8ba,    `8b  d8'`8b  d8'   8PP"""""""  8PP"""""""  88       d8  8PP"""""""  88         
88    `888'    88  88  88       88  "8b,   ,aa  aa    ]8I    `8bd8'  `8bd8'    "8b,   ,aa  "8b,   ,aa  88b,   ,a8"  "8b,   ,aa  88         
88     `8'     88  88  88       88   `"Ybbd8"'  `"YbbdP"'      YP      YP       `"Ybbd8"'   `"Ybbd8"'  88`YbbdP"'    `"Ybbd8"'  88         
                                                                                                       88                                  
                                                                                                       88                                  )" << std::endl;
    std::cout << "\n\n\n\n" << std::endl;
}

std::tuple<int,int,float> Determine_difficulty() {
    int difficulty;
    std::cout << "Please select a difficulty: \nBeginner (1), Advanced (2) or Professional (3)?" << std::endl;
    std::cout << "\n\nBeginner: Spielfeld von 8 mal 8 (64) Feldern mit 10 Minen (Minendichte 15,6 %)." << std::endl;
    std::cout << "\nAdvanced: Spielfeld von 16 mal 16 (256) Feldern mit 40 Minen (15,6 %)." << std::endl;
    std::cout << "\nProfessional: Spielfeld von 30 mal 16 (480) Feldern mit 99 Minen (20,6 %)." << std::endl;
    std::cin >> difficulty;

    if (difficulty == 1) {
        
        return std::make_tuple(8, 8, 0.156);
    }
    else if (difficulty == 2) {
        
        return std::make_tuple(16, 16, 0.156);
    }
    else if (difficulty == 3) {
        
        return std::make_tuple(30, 16, 0.206);
    }
    else {
        std::cout << "\nInvalid input. Try again." << std::endl;
        Determine_difficulty();
    }
    return std::make_tuple(0, 0, 0.0);
}

void GetCellUpdate(Cell cell){
    std::cout << "Cell is a mine: " << cell.isMine() << std::endl;
    std::cout << "Cell is flagged: " << cell.isFlagged() << std::endl;
    std::cout << "Cell is revealed: " << cell.isRevealed() << std::endl;
    std::cout << "Adjacent mines: " << cell.getAdjacentMines() << std::endl;
    std::cout << "\nCell ssymbol: " << cell.getSymbol() << std::endl;
}

char GetUserCellInteraction() {
    std::cout << "What do you want to do with that cell?" << std::endl;
    char userenter;
    while (true) {
        if (userenter == 'r' || userenter == 'f') {
            return userenter;
        }
        else {
            std::cout << "\nOptions:\nReveal: r, Flag: f" << std::endl;
            std::cin >> userenter;
        }
    }
}

int GetUserNumberSelection(int limit) {
    int input;
    while (true) {
        std::cout << "\nEnter the row, hit enter, then enter the cell number." << std::endl;
        std::cin >> input;
        input--;
        if (input >= 0 && input < limit) {
            return input;
        }
        else {
            std::cout << "Invalid input. Try again.\n" << std::endl;
        }
    }
}

int getTerminalWidth() {
    int width = 80; // Default width
    FILE* fp = popen("tput cols", "r");
    if (fp) {
        fscanf(fp, "%d", &width);
        pclose(fp);
    }
    return width;
}

void PlaceMines(std::vector<std::vector<Cell>>& field, int numMines) {
    int rows = field.size();
    int cols = field[0].size();
    int placedMines = 0;
    srand(time(0)); // Seed for random number generation

    while (placedMines < numMines) {
        int randRow = rand() % rows;
        int randCol = rand() % cols;

        if (!field[randRow][randCol].isMine()) {
            field[randRow][randCol].setMine(true);
            placedMines++;
        }
    }
}


