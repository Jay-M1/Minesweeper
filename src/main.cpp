#include <iostream>
#include <vector>
#include "../include/Cell.h"
#include "../include/Field.h"
#include <random>
#include <tuple>
#include <cstdlib> // for system()
#include <iomanip> // for setw()

void PrintBanner();
std::tuple<int,int> Determine_difficulty();
void GetCellUpdate(Cell cell);
char GetUserCellInteraction();
int GetUserNumberSelection(int limit);
int getTerminalWidth();

int main (int argc, char* argv[]) {

    // create field and distribute mines
    PrintBanner();
    std::tuple<int,int> dimension = Determine_difficulty();
    int rows = std::get<0>(dimension);
    int cols = std::get<1>(dimension);
    Field MyField(rows, cols);
    std::vector<std::vector<Cell>> vector = MyField.getVector();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            vector[i][j].setMine(dis(gen));
        }
    }

    int terminalWidth = getTerminalWidth();
    int fieldWidth = cols * 1; // Assuming each cell takes 2 characters (1 for symbol and 1 for space)
    int padding = (terminalWidth - fieldWidth) / 2;

    while (true) {
        // Clear the terminal
        std::cout << "\033[2J\033[H";
        std::cout << "\n\n\n\n\n\n\n\n\n" << std::endl;
        // display vector
        for (int i = 0; i < rows; i++) {
            std::cout << std::setw(padding) << "";
            for (int j = 0; j < cols; j++) {
                std::cout << vector[i][j].getSymbol() << " ";
            }
            std::cout << std::endl;
        }

        // get entered value of the user
        int userRowSelection = GetUserNumberSelection(rows);
        int userColumnSelection = GetUserNumberSelection(cols);
        char userCellInteraction = GetUserCellInteraction();
        
        // update cell
        if (userCellInteraction == 'r') {
            vector[userRowSelection][userColumnSelection].setRevealed(true);
            if (vector[userRowSelection][userColumnSelection].isMine()) {
                vector[userRowSelection][userColumnSelection].setExploded(true);
                // display vector
                for (int i = 0; i < rows; i++) {
                    std::cout << std::setw(padding) << "";
                    for (int j = 0; j < cols; j++) {
                        std::cout << vector[i][j].getSymbol() << " ";
                    }
                    std::cout << std::endl;
                }

                std::cout << "You hit a mine! Game over.\nPress any key to end the game" << std::endl;
                int end;
                std::cin >> end;
                break;
            }
        }
        else {
            vector[userRowSelection][userColumnSelection].setFlagged(true);
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

std::tuple<int,int> Determine_difficulty() {
    std::string difficulty;
    std::cout << "Please select a difficulty: \nBeginner, Advanced or Professional?" << std::endl;
    std::cin >> difficulty;

    if (difficulty == "Beginner") {
        std::cout << "Beginner: Spielfeld von 8 mal 8 (64) Feldern mit 10 Minen (Minendichte 15,6 %)." << std::endl;
        return std::make_tuple(8, 8);
    }
    else if (difficulty == "Advanced") {
        std::cout << "Advanced: Spielfeld von 16 mal 16 (256) Feldern mit 40 Minen (15,6 %)." << std::endl;
        return std::make_tuple(16, 16);
    }
    else if (difficulty == "Professional") {
        std::cout << "Professional: Spielfeld von 30 mal 16 (480) Feldern mit 99 Minen (20,6 %)." << std::endl;
        return std::make_tuple(30, 16);
    }
    else {
        std::cout << "\nInvalid input. Try again." << std::endl;
        Determine_difficulty();
    }
    return std::make_tuple(0, 0);
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
    char userenter = 'a';
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
            std::cout << "Invalid input. Try again.<\n" << std::endl;
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