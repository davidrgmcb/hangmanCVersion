#include "wordList.h"
#include <string.h>

void getWordList(wordList *words) {
    words->wordListFile = fopen("/usr/share/dict/words", "r");
    char buffer[256];
    while (fgets(buffer, 256, words->wordListFile) != NULL) {
        addWord(words, buffer);
        words->highestFilledArrayAddress++;
        }
}

void createEmptyWordList(wordList *words) {
    words->highestFilledArrayAddress = ARRAY_FILL_START; //Variable to track how full the array is, necessary given the unclear nature of what file will ofer that list
    words->arraySize = BASE_ARRAY_SIZE;
    words->possibleAnswers = malloc(sizeof(char*)*words->arraySize);
}//Constructs a struct to hold the list of words to be chosen from at random

void addWord(wordList *words, char *buffer) {
    if (words->highestFilledArrayAddress == words->arraySize) {
        expandArray(words);
    }
    words->possibleAnswers[words->highestFilledArrayAddress] = strdup(buffer);
}//Goes down wordList and copies at each newline into the array of possible words

void expandArray(wordList *words) {
    words->arraySize = (words->arraySize * 2);
    words->possibleAnswers = realloc(words->possibleAnswers, sizeof(char*) * words->arraySize);
}//Basic dynamic array resizing setup given the unknown nature of how long wordList can be

int wordListLength(wordList words) {
    return words.highestFilledArrayAddress;
}//Just a getter to allow the number of words currently in the list to be chosen from to be known

void getWord(wordList words, gameState *game) {
    game->hangmanAnswer = strdup(words.possibleAnswers[rand() % (words.highestFilledArrayAddress - 1)]);
}//gets a random word out of the wordlist and copies it into hangman answer in the game struct

void seekWord(wordList *words, gameState *game) {
    char buffer[256];
    words->wordListFile = fopen("/usr/share/dict/words", "r");
    fseek(words->wordListFile, 0, SEEK_END);
    int fileLength = ftell(words->wordListFile);
    rewind(words->wordListFile);
    int fileRand = rand() % fileLength -1;
    fseek(words->wordListFile, fileRand, SEEK_SET);
    char *currentChar = fgets(buffer, 2, words->wordListFile);
    while(*currentChar != '\n' || currentChar == NULL){
        fseek(words->wordListFile, -2, SEEK_CUR);
        currentChar = fgets(buffer, 2, words->wordListFile);
    }
    game->hangmanAnswer = strdup(fgets(buffer, 256, words->wordListFile));
    //printf("%s", game->hangmanAnswer);
}

void destroyWordList(wordList *words) {
    for(int ii = 0; ii < words->highestFilledArrayAddress; ii++) {
        free(words->possibleAnswers[ii]);
    }
}