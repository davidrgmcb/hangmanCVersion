#include <stdlib.h>
#include <stdio.h>
#include "gameState.h"

typedef struct {
FILE *wordListFile;
char **words;
char **possibleAnswers;
int arraySize;
int highestFilledArrayAddress;
}wordList;

#define ARRAY_FILL_START 0
#define BASE_ARRAY_SIZE 10

void createEmptyWordList(wordList *words);

void expandArray(wordList *words);

void addWord(wordList *words, char *buffer);

int wordListLength(wordList words);

int getRandomAddress (int listLength);

void getWord(wordList words, gameState *game);

void getWordList(wordList *words);
