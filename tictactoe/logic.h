#ifndef LOGIC_H
#define LOGIC_H

#define BOARD_SIZE 3
#define EMPTY_CELL ' '
#define O_CELL 'o'
#define X_CELL 'x'

enum GameState {
    IN_PROGRESS,
    PLAYER_O_WON,
    PLAYER_X_WON,
    DRAW
};

struct Tictactoe {
    char board[BOARD_SIZE][BOARD_SIZE];
    char nextMove = O_CELL;
    GameState gameState = IN_PROGRESS;

    void init() {
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++) board[i][j] = EMPTY_CELL;
        gameState = IN_PROGRESS;
    }

    bool isCellMarked(int row, int column) {
        return board[row][column] != EMPTY_CELL;
    }

    void move(int row, int column) {
        if (row >= 0 && row < BOARD_SIZE && column >= 0 && column < BOARD_SIZE && !isCellMarked(row, column))
        {
            board[row][column] = nextMove;
            nextMove = (nextMove == O_CELL) ? X_CELL : O_CELL;
            gameState = checkGameState();
        }
    }

    GameState checkGameState() {
        for (int row = 0; row < BOARD_SIZE; ++row) {
            if (board[row][0] != EMPTY_CELL &&
                board[row][0] == board[row][1] &&
                board[row][0] == board[row][2]) {
                return (board[row][0] == O_CELL) ? PLAYER_O_WON : PLAYER_X_WON;
            }
        }
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[0][col] != EMPTY_CELL &&
                board[0][col] == board[1][col] &&
                board[0][col] == board[2][col]) {
                return (board[0][col] == O_CELL) ? PLAYER_O_WON : PLAYER_X_WON;
            }
        }
        if (board[0][0] != EMPTY_CELL &&
            board[0][0] == board[1][1] &&
            board[0][0] == board[2][2]) {
            return (board[0][0] == O_CELL) ? PLAYER_O_WON : PLAYER_X_WON;
        }
        if (board[0][2] != EMPTY_CELL &&
            board[0][2] == board[1][1] &&
            board[0][2] == board[2][0]) {
            return (board[0][2] == O_CELL) ? PLAYER_O_WON : PLAYER_X_WON;
        }
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                if (board[i][j] == EMPTY_CELL)
                    return IN_PROGRESS;

        return DRAW;
    }
    void displayResult() {
        if (gameState == PLAYER_O_WON) {
            std::cout << "Player O won!" << std::endl;
        } else if (gameState == PLAYER_X_WON) {
            std::cout << "Player X won!" << std::endl;
        } else if (gameState == DRAW) {
            std::cout << "It's a draw!" << std::endl;
        }
    }
};

#endif // LOGIC_H
