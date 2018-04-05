#include "wordList.h"
#include <string.h>

void getWordList(wordList *words) {
    words->wordListFile = fopen("/usr/share/dict/words", "r");
    char buffer[256];
    while (fgets(buffer, 256, words->wordListFile) != NULL) {
        addWord(words, buffer);
        //printf("%d\n", words->arraySize);
        //printf("%s\n", words->possibleAnswers[words->highestFilledArrayAddress]);
        words->highestFilledArrayAddress++;
        }
}//opens a file and calls addWord to read from it and return a full list of every word presuming each line contains only one

void createEmptyWordList(wordList *words) {
    words->highestFilledArrayAddress = ARRAY_FILL_START; //Variable to track how full the array is, necessary given the unclear nature of what file will ofer that list
    words->arraySize = BASE_ARRAY_SIZE;
    words->possibleAnswers = malloc(sizeof(char*)*words->arraySize);
}//Constructs a struct to hold the list of words to be chosen from at random

void addWord(wordList *words, char *buffer) {
    int temporary = strlen(buffer) + 1;
    char *temporaryString = malloc(sizeof(char) * temporary);
    strncpy(temporaryString, buffer, temporary);
    if (words->highestFilledArrayAddress == words->arraySize) {
        expandArray(words);
    }
    words->possibleAnswers[words->highestFilledArrayAddress] = strdup(temporaryString);
}//Goes down wordList and copies at each newline into the array of possible words

void expandArray(wordList *words) {
    words->arraySize = (words->arraySize * 2);
    words->possibleAnswers = realloc(words->possibleAnswers, sizeof(char*) * words->arraySize);
}//Basic dynamic array resizing setup given the unknown nature of how long wordList can be

int wordListLength(wordList words) {
    return words.highestFilledArrayAddress;
}//Just a getter to allow the number of words currently in the list to be chosen from to be known

void getWord(wordList words, gameState *game) {
    int answer = rand() % (words.highestFilledArrayAddress - 1);
    game->hangmanAnswer = strdup(words.possibleAnswers[answer]);
}//gets a random word out of the wodlist and copies it into hangman answer in the game struct