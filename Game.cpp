#include "Game.h"

Game::Game(int size, int winCount) : N(size), M(winCount), currentPlayer('X') {
    board.resize(N, std::vector<char>(N));
    int numCell = 1;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++i)
        {
            board[i][j] += numCell;
            numCell++;
        }
}

bool Game::makeMove(int cell) {
    int x = (cell - 1) / N;
    int y = (cell - 1) % N;
    if (x >= 0 && x < N && y >= 0 && y < N && board[x][y] != 'X' && board[x][y] != 'O') {
        board[x][y] = currentPlayer;
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        return true;
    }
    return false;
}

std::string Game::getBoard() {
    std::string boardState;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            boardState += board[i][j];
            if (j < N - 1) boardState += '|';
        }
        boardState += '\n';
        if (i < N - 1) boardState += std::string(N * 2 - 1, '-') + '\n';
    }
    return boardState;
}


bool Game::checkDraw() {
    
    for (int i = 0; i < N; ++i) 
        for(int j = 0; j < N; ++j)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;

    return true;
}


bool Game::checkWin() {
    for (int i = 0; i < N; ++i) {
        if (checkRow(i) || checkCol(i)) return true;
    }
    return checkDiagonal();
}

bool Game::checkRow(int row) {
    int maxCount = 0;
    int currentCount = 0;
    char lastChar = ' ';

    for (int col = 0; col < N; ++col) {
        if (board[row][col] == lastChar) 
        {
            currentCount++;
        }
        else {
            maxCount = std::max(maxCount, currentCount);
            currentCount = 1; 
        }
        lastChar = board[row][col];
    }
    maxCount = std::max(maxCount, currentCount);  

    return maxCount >= M;
}

bool Game::checkCol(int col) {
    int maxCount = 0;
    int currentCount = 0;
    char lastChar = ' ';

    for (int row = 0; row < N; ++row) {
        if (board[row][col] == lastChar) {
            currentCount++;
        }
        else {
            maxCount = std::max(maxCount, currentCount);
            currentCount = 1; 
        }
        lastChar = board[row][col];
    }
    maxCount = std::max(maxCount, currentCount); 

    return maxCount >= M;
}

bool Game::checkDiagonal() {
    int maxCount = 0;

    
    for (int startRow = 0; startRow <= N - M; ++startRow) {
        for (int startCol = 0; startCol <= N - M; ++startCol) {
            int currentCount = 0;
            char lastChar = ' ';
            for (int i = 0; i < M; ++i) {
                if (board[startRow + i][startCol + i] == lastChar) {
                    currentCount++;
                }
                else {
                    currentCount = 1;
                }
                lastChar = board[startRow + i][startCol + i];
            }
            maxCount = std::max(maxCount, currentCount);
        }
    }

    
    for (int startRow = 0; startRow <= N - M; ++startRow) {
        for (int startCol = M - 1; startCol < N; ++startCol) {
            int currentCount = 0;
            char lastChar = ' ';
            for (int i = 0; i < M; ++i) {
                if (board[startRow + i][startCol - i] == lastChar) {
                    currentCount++;
                }
                else {
                    currentCount = 1;
                }
                lastChar = board[startRow + i][startCol - i];
            }
            maxCount = std::max(maxCount, currentCount);
        }
    }

    return maxCount >= M;
}
