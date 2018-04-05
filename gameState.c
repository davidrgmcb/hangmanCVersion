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
    listLength = wordListLength(words);
    //randomWordAddress = getRandomAddress(listLength);
    //printf("%d\n", randomWordAddress);
    getWord(words, game);
    //answerLength = strlen(hangmanAnswer);
    printf("%s\n", game->hangmanAnswer);
    trimEndOfString(game->hangmanAnswer);
    game->answerLength = strlen(game->hangmanAnswer);
    //answerLowerCase(game);
    fclose(words.wordListFile);
}//Once answer is determined wordlist is a drain, fclose and free seem prudent but valgrind is reporting unfreed memory when I free(words->possibleAnswers) so definitely need more idea what that free will entail

void createGameState(gameState *game) { //makes room to store guesses, sets a default value and an array to store already guessed letters
    getAnswer(game);
    game->hangmanGuess = malloc(1024);
    game->hangmanGuess[0] = 'a';
    game->hangmanCorrect = malloc(sizeof(char) * (game->answerLength));
    game->hangmanAlreadyGuessed[26];
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
    trimGuess(game);
}

/*void testGuess(hangmanGuess) {
    //hangmanGuessedCorrect = False;
    for (int letter = 0; i < (int)(sizeof(hangmanAnswer)); ++letter) {
        if hangmanGuess == hangmanAnswer[letter] {
            //hangmanCorrectGuesses[letter] = hangmanGuess; hangmanCorrectGuesses is I guess a dynamically allocated char array that is declared with the hangmanAnswerLength size
            //hangmanGuessedCorrect = True; a bool, may need to be more clever, not sure how far this value exists outside scope of this for loop
        }
    }
    //if hangmanGuessedCorrect == False {
        //hangmanStrikes++; Like in python version, strikes is an int
}*/

int main() {
    //Move this inside of the gameState whenever that becomes a proper structure
    int numberOfGuesses = 0;//Just for testing, will go away
    gameState game;
    createGameState(&game);
    answerLowerCase(&game);
    while (numberOfGuesses <= 4) { //This is off by one somehow, will have to work that out
        getGuess(game);
        printf("%s\n", game.hangmanAnswer);
        printf("%s\n", game.hangmanGuess);
        int guessLength = strlen(game.hangmanGuess);
        printf("%d\n", guessLength);
        ++numberOfGuesses;
    }
    //printf("%s\n", hangmanAnswer);
    //printf("%d\n", (int)strlen(hangmanAnswer));
    trimEndOfString(game.hangmanAnswer);
    //printf("%s\n", hangmanAnswer);
    //printf("%d\n", (int)strlen(hangmanAnswer));
}