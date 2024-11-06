#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

class Game {
private:
    int N;                  
    int M;                  
    char currentPlayer;     
    std::vector<std::vector<char>> board;  

    bool checkRow(int row);      
    bool checkCol(int col);      
    bool checkDiagonal();        

public:
    Game(int size, int winCount);

    
    bool makeMove(int cell);

    
    std::string getBoard();

    bool checkDraw();

    bool checkWin();
};

#endif 