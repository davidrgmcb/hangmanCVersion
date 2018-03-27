#include <stdlib.h>
#include <stdio.h>

typedef struct {
FILE *wordListFile;
char **words;
char **possibleAnswers;
int arraySize;
int highestFilledArrayAddress;
}wordList;

char *hangmanGuess;
int listLength;
int randomWordAddress;
char *hangmanAnswer;//put these in a struct later,gameState maybe, also give them initialized values

#define ARRAY_FILL_START 0
#define BASE_arraySize 10

void createEmptyWordList(wordList *words);

void expandArray(wordList *words);

void addWord(wordList *words, char *buffer);

int wordListLength(wordList words);

int getRandomAddress (int listLength);

char * getWord(wordList words, int randomWordAddress);

void getWordList(wordList *words);
