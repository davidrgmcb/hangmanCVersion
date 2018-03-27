#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wordList.h"

void trimEndOfString(char *hangmanAnswer) {
    int ii = 0;
    while (hangmanAnswer[ii] != '\0') {
        if (hangmanAnswer[ii] == '\n') {
            hangmanAnswer[ii] = '\0';
            break;
        }
        ii++;
    }
}

void seedRandomizer() {
    time_t startTime;
    srand((unsigned) time(&startTime));
}

void getAnswer() {
    seedRandomizer();
    wordList words;
    createEmptyWordList(&words);
    getWordList(&words);
    listLength = wordListLength(words);
    randomWordAddress = getRandomAddress(listLength);
    //printf("%d\n", randomWordAddress);
    hangmanAnswer = getWord(words, randomWordAddress);
    //answerLength = strlen(hangmanAnswer);
    printf("%s\n", hangmanAnswer);
    trimEndOfString(hangmanAnswer);
    fclose(words.wordListFile);
}//Once answer is determined wordlist is a drain, fclose and free seem prudent but valgrind is reporting unfreed memory when I free(words->possibleAnswers) so definitely need more idea what that free will entail

void getGuess() {
    hangmanGuess = fgets(hangmanGuess, 2, stdin);//fgets should protect against too much input but extra input seems to curently spill over so may need to hack off everything past first if making the game loop differently doesn't fix
}

/*void testGuess(hangmanGuess) {
    //hangmanGuessedCorrect = False;
    for (int letter = 0; i < (int)(sizeof(hangmanAnswer)); ++letter) {
        if hangmanGuess == hangmanAnswer[letter] {
            //hangmanCorrectGuesses[letter] = hangmanGuess; hangmanCorrectGuesses is I guess a dynamically allocated char array
            //hangmanGuessedCorrect = True; a bool, may need to be more clever, not sure how far this value exists outside scope of this for loop
        }
    }
    //if hangmanGuessedCorrect == False {
        //hangmanStrikes++; Like in python version, strikes is an int
}*/

int main() {
    /*hangmanGuess = malloc(2);//Move this inside of the gameState whenever that becomes a proper structure
    int numberOfGuesses = 0;//Just for testing, will go away
    getAnswer();
    while (numberOfGuesses <= 4) { //This is off by one somehow, will have to work that out
        getGuess();
        printf("%s\n", hangmanGuess);
        ++numberOfGuesses;
    }
    printf("%s\n", hangmanAnswer);
    printf("%d\n", (int)strlen(hangmanAnswer));*/
    getAnswer();
    printf("%s\n", hangmanAnswer);
    printf("%d\n", (int)strlen(hangmanAnswer));
}