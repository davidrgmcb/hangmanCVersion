#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "wordList.h"


void trimEndOfString(char *hangmanAnswer) { //cleans newlines off the string getAnswer returns
    int ii = 0;
    while (hangmanAnswer[ii] != '\0') {
        if (hangmanAnswer[ii] == '\n') {
            hangmanAnswer[ii] = '\0';
            break;
        }
        ii++;
    }
}

void seedRandomizer() {  //seeds srand so that a different word is actually selected each time
    time_t startTime;
    srand((unsigned) time(&startTime));
}

void answerLowerCase(gameState *game) {
    for(int ii = 0; ii < game->answerLength; ii++) {
        game->hangmanAnswer[ii] = tolower(game->hangmanAnswer[ii]);
    }
}

void getAnswer(gameState *game) {
    seedRandomizer();
    wordList words;
    createEmptyWordList(&words);
    getWordList(&words);
    //listLength = wordListLength(words);
    //randomWordAddress = getRandomAddress(listLength);
    //printf("%d\n", randomWordAddress);
    getWord(words, game);
    trimEndOfString(game->hangmanAnswer);
    //answerLength = strlen(hangmanAnswer);
    printf("%s\n", game->hangmanAnswer);
    game->answerLength = strlen(game->hangmanAnswer);
    //answerLowerCase(game);
    fclose(words.wordListFile);
}//Once answer is determined wordlist is a drain, fclose and free seem prudent but valgrind is reporting unfreed memory when I free(words->possibleAnswers) so definitely need more idea what that free will entail

void createGameState(gameState *game) { //makes room to store guesses, sets a default value and an array to store already guessed letters
    getAnswer(game);
    game->hangmanStrikes = 0;
    game->hangmanGuess = malloc(1024);
    game->hangmanGuess[0] = 'a';
    game->hangmanCorrect = malloc(sizeof(char) * (game->answerLength));
    game->hangmanAlreadyGuessed = malloc(26);
    game->isEnd = (-1);
    for(int ii = 0; ii < game->answerLength; ii++) {
        game->hangmanCorrect[ii] = '_';
    }
    game->numberOfGuesses = 0;
}

void trimGuess(gameState game) {
    if ((int)strlen(game.hangmanGuess) > 1) {
        game.hangmanGuess[1] = '\0';
    } 
}

void getGuess(gameState game) {
    game.hangmanGuess = fgets(game.hangmanGuess, 1024, stdin);//gigantobuffer that gets hacked off immediately
    if (isalpha(game.hangmanGuess[0]) == 0) {
        printf("Please enter a letter, no numbers or symbols\n");
        getGuess(game);
    }
    trimGuess(game);
    game.hangmanAlreadyGuessed[game.numberOfGuesses] = game.hangmanGuess[0];
    game.numberOfGuesses++;
}

void testGuess(gameState game) {
    game.isGuessCorrect = 0;
    for (int letter = 0; letter < game.answerLength; letter++) {
        if (game.hangmanGuess[0] == game.hangmanAnswer[letter]) {
            game.hangmanCorrect[letter] = game.hangmanGuess[0]; //hangmanCorrect is a dynamically allocated char array that is declared with the answerLength size
            game.isGuessCorrect = 1; //a bool, may need to be more clever, not sure how far this value exists outside scope of this for loop
        }
    }
    if (game.isGuessCorrect == 0) { //doesn't work, not sure why yet
        game.hangmanStrikes++; //Like in python version, strikes is an int, this isn't incrementing for reasons I haen't been able to resole
    }
}

void addApostrophes(gameState game) {
    for (int letter = 0; letter < game.answerLength; letter++) {
        if (game.hangmanAnswer[letter] == '\'') {
            game.hangmanCorrect[letter] = '\''; //just slot in the apostrophes before the game even begins
        }
    }
}

void showCorrectGuesses(gameState game) {
    for (int letter = 0; letter <= game.answerLength; letter++) {
        printf("%c", game.hangmanCorrect[letter]);
        if (letter == game.answerLength) {
            printf("\n");
        }
    }
}

void getUnderlines(gameState game) {
    for (int letter = 0; letter <= game.answerLength; letter++) {
        game.hangmanCorrect[letter] = '_';
    }
}

void isGameOver(gameState game) {
    game.isEnd = strncmp(game.hangmanAnswer, game.hangmanCorrect, 1000);
}

int main() {
    //int numberOfGuesses = 0;//Just for testing, will go away
    gameState game;
    createGameState(&game);
    answerLowerCase(&game);
    //trimEndOfString(game.hangmanAnswer);
    getUnderlines(game);
    addApostrophes(game);
    while (game.hangmanStrikes <= 7) { //This is off by one somehow, will have to work that out
        getGuess(game);
        showCorrectGuesses(game);
        printf("%s\n", game.hangmanAnswer);
        printf("%s\n", game.hangmanGuess);
        printf("%d\n", game.hangmanStrikes);
        //int guessLength = strlen(game.hangmanGuess);
        //printf("%d\n", guessLength);
        testGuess(game);
        showCorrectGuesses(game);
        isGameOver(game);
        printf("%d\n", game.isEnd);//This keeps returning 0 before it ought to which doesn't trigger the break anyway, very odd
        if (game.isEnd = 0) {
            break;//not sure if this can ever break out of botht he while loop and the if, may have to restructure
        }
        //++numberOfGuesses;
    }
    //printf("%s\n", hangmanAnswer);
    //printf("%d\n", (int)strlen(hangmanAnswer));
    //printf("%s\n", hangmanAnswer);
    //printf("%d\n", (int)strlen(hangmanAnswer));
}

//TODO: Reject non alphabetical guesses
//TODO: Insert apostrophes automatically
//TODO: check guess finish
//Test answers with strcmp