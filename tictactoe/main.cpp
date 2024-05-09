#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphic.h"
#include "defs.h"
#include "logic.h"

using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void processClick(int x, int y, Tictactoe& game, Graphics& graphics) {
    int clickedCol = (x - BOARD_X) / CELL_SIZE;
    int clickedRow = (y - BOARD_Y) / CELL_SIZE;
    if (!game.isCellMarked(clickedRow, clickedCol)) {
        game.move(clickedRow, clickedCol);
        graphics.render(game);
        game.displayResult();
    }
}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    Tictactoe game;
    bool playAgain = true;
    char choice;

    while (playAgain) {
        game.init();
        graphics.render(game);

        int x, y;
        SDL_Event event;
        bool quit = false;
        while (!quit) {
            SDL_PollEvent(&event);
            switch (event.type) {
                case SDL_QUIT:
                     quit = true;
                     playAgain = false;
                     break;
                case SDL_MOUSEBUTTONDOWN:
                     SDL_GetMouseState(&x, &y);
                     processClick(x, y, game, graphics);
                     if (game.gameState != IN_PROGRESS) {
                         game.displayResult();
                         waitUntilKeyPressed();
                         quit = true;
                     }
                     break;
            }
            SDL_Delay(100);
        }

        if (playAgain) {
            cout << "Choi lai (y/n): ";
            cin >> choice;
            playAgain = (choice == 'y');
        }
    }

    graphics.quit();
    return 0;
}
