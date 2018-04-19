#include "gameState.h"
#include <stdio.h>

int main() {
    gameState game;
    createGameState(&game);
    answerLowerCase(&game);
    addApostrophes(&game);
    printf("%s\n", game.correctGuesses);
    while ((game.hangmanStrikes < 7) && (!game.isEnd)) { 
        getGuess(&game);
        printf("%s\n%d\n", game.hangmanGuess, game.numberOfGuesses);
        testGuess(&game);
        printf("%s\nStrikes: %d of 7\nPreviously Guessed: %s\n", game.correctGuesses, game.hangmanStrikes, game.hangmanAlreadyGuessed);
        printHangman(game);
        isGameOver(&game);
        //printf("%d\n", game.isEnd);
    }
    if (game.isEnd == 1) {
        printf("Wow, you win!\nCongratulations on guessing %s\n", game.hangmanAnswer);
    }
    else {
        printf("Wow, you lose!\nCorrect answer was: %s\n", game.hangmanAnswer);
    }
}