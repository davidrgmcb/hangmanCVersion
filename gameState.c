#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "wordList.h"


void trimEndOfString(gameState *game) {
    int ii = 0;
    while (game->hangmanAnswer[ii] != '\0') {
        if (game->hangmanAnswer[ii] == '\n') {
            game->hangmanAnswer[ii] = '\0';
            break;
        }
        ii++;
    }
}

void seedRandomizer() {
    time_t startTime;
    srand((unsigned) time(&startTime));
}

void getUnderlines(gameState *game) {
    for (int letter = 0; letter < game->answerLength; letter++) {
        game->correctGuesses[letter] = '_';
    }
    game->correctGuesses[game->answerLength] = '\0';
}

void answerLowerCase(gameState *game) { 
    for(int ii = 0; ii < game->answerLength; ii++) {
        game->hangmanAnswer[ii] = tolower(game->hangmanAnswer[ii]);
    }
}

void getAnswer(gameState *game) {
    seedRandomizer();
    wordList words;
    if(game->randomizationScheme == 0) {
        createEmptyWordList(&words);
        getWordList(&words);
        getWord(words, game);
        trimEndOfString(game);
        //printf("%s\n", game->hangmanAnswer); Reactivateable for testing purposes
        destroyWordList(&words);
        free(words.possibleAnswers);
    }
    else if(game->randomizationScheme == 1) {
        seekWord(&words, game);
        trimEndOfString(game);
    }
    game->answerLength = strlen(game->hangmanAnswer);
    fclose(words.wordListFile);
}//Once answer is determined wordlist is a drain, fclose and free seem prudent but valgrind is reporting unfreed memory when I free(words->possibleAnswers) so definitely need more idea what that free will entail

void createGameState(gameState *game) { //makes room to store guesses, sets a default value and an array to store already guessed letters
    game->randomizationScheme = 1;
    getAnswer(game);//getAnswer called here to avoid an issue where both needed each other to exist to complete construction
    game->hangmanStrikes = 0;
    game->hangmanGuess = malloc(1024);//healthy buffer size in case someone gets silly with how long their guess is
    game->hangmanGuess[0] = 'a';//safe default guess
    game->correctGuesses = malloc(sizeof(char) * (game->answerLength + 1));
    game->hangmanAlreadyGuessed = malloc(26);
    game->isEnd = 0;//Just exists for the function that tracks if the game is over
    getUnderlines(game);
    game->numberOfGuesses = 0;
}

void trimGuess(gameState *game) {
    if ((int)strlen(game->hangmanGuess) > 1) {
        game->hangmanGuess[1] = '\0';
    } 
}

void getGuess(gameState *game) {
    game->hangmanGuess = fgets(game->hangmanGuess, 1024, stdin);//gigantobuffer that gets hacked off immediately
    if (isalpha(game->hangmanGuess[0]) == 0) {//Rejects answers that aren't part of the alphabet
        printf("Please enter a letter, no numbers or symbols\n");
        getGuess(game);
    }
    trimGuess(game);
    for(int letter = 0; letter <= game->numberOfGuesses; letter++) {
        if (game->hangmanAlreadyGuessed[letter] == game->hangmanGuess[0]) {
            printf("You already guessed that.\n");
            return;
        }
    }
    game->hangmanAlreadyGuessed[game->numberOfGuesses] = game->hangmanGuess[0];//adds the guess to AlreadyGuessed, need to add something to disallow adding something that's already in there, could be dangerous
    game->hangmanAlreadyGuessed[game->numberOfGuesses + 1] = '\0';
    game->numberOfGuesses++;
}

void testGuess(gameState *game) {
    game->isGuessCorrect = 0;
    for (int letter = 0; letter < game->answerLength; letter++) {
        if (game->hangmanGuess[0] == game->hangmanAnswer[letter]) {
            game->correctGuesses[letter] = game->hangmanGuess[0]; 
            game->isGuessCorrect = 1;
        }
    }
    if (game->isGuessCorrect == 0) { 
        game->hangmanStrikes++; 
    }
}

void addApostrophes(gameState *game) {
    for (int letter = 0; letter < game->answerLength; letter++) {
        if (game->hangmanAnswer[letter] == '\'') {
            game->correctGuesses[letter] = '\''; //just slot in the apostrophes before the game even begins, since the player can't and shouldn't have to
        }
    }
}

void isGameOver(gameState *game) {
    for (int letter = 0; letter < game->answerLength; letter++) {
        if ((game->correctGuesses[letter]) != (game->hangmanAnswer[letter])) {
            return;
        }
    }
    game->isEnd = 1;
}

void printHangman(gameState game) {
    if (game.hangmanStrikes == 1) {
        printf("________\n|       |\n|       O\n");
    }
    else if (game.hangmanStrikes == 2) {
        printf("________\n|       |\n|       O\n|       |\n");
    }
    else if (game.hangmanStrikes == 3) {
        printf("________\n|       |\n|       O\n|     --|\n");
    }
    else if (game.hangmanStrikes == 4) {
        printf("________\n|       |\n|       O\n|     --|--\n");
    }
    else if (game.hangmanStrikes == 5) {
        printf("________\n|       |\n|       O\n|     --|--\n|      /\n");
    }
    else if (game.hangmanStrikes == 6) {
        printf("________\n|       |\n|       O\n|     --|--\n|      / \\\n");
    }
    else if (game.hangmanStrikes >= 7) {
        printf("________\n|       |\n|       O\n|     --|--\n|      / \\ \n\n He's dead Jim\n");
    }
}