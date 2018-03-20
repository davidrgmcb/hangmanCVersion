#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "wordList.h"


#define ARRAY_FILL_START 0
#define BASE_ARRAY_SIZE 10

void createEmptyWordList(wordList *words) {
    words->array_filled_num = ARRAY_FILL_START;
    words->array_size = BASE_ARRAY_SIZE;
    words->stringArray = malloc(sizeof(char*)*words->array_size);
}

void expandArray(wordList *words) {
    words->array_size = (words->array_size * 2);
    words->stringArray = realloc(words->stringArray, sizeof(char*) * words->array_size);
}

void addWord(wordList *words, char *buffer) {
    int temporary = strlen(buffer) + 1;
    char *temporaryString = malloc(sizeof(char) * temporary);
    strncpy(temporaryString, buffer, temporary);
    if (words->array_filled_num == words->array_size) {
        expandArray(words);
    }
    words->stringArray[words->array_filled_num] = strdup(temporaryString);
}

int wordListLength(wordList words) {
    return words.array_filled_num;
}

char * getWord(wordList words, int randomWordAddress) {
    return words.stringArray[randomWordAddress];
}

void getWordList(wordList *words) {
    words->wordListFile = fopen("/home/david/Desktop/hangmanCPort/wordList.txt", "r");
    char buffer[256];
    while (fgets(buffer, 256, words->wordListFile) != NULL) {
        addWord(words, buffer);
        printf("%d\n", words->array_size);
        printf("%s\n", words->stringArray[words->array_filled_num]);
        words->array_filled_num++;
        }
}

int main() {
    time_t startTime;
    srand((unsigned) time(&startTime));
    wordList words;
    createEmptyWordList(&words);
    getWordList(&words);
    int listLength = wordListLength(words);
    int randomWordAddress = rand() % (listLength - 7);
    printf("%d\n", randomWordAddress);
    //char *hangmanAnswer = getWord(words, randomWordAddress);
    //printf("%s\n", hangmanAnswer);
}

//use strdup, this soultion assigns the entire array pointers to the same thing. OBSOLETE

//why is it a bad idea to pass fgets to strdup? Dangerous when fgets returns a null pointer which it always does when it reaches the EOF. Useful behavior otherwise but in future don't make that one line.
//TODO: Read from file rather than stdin. DONE
//TODO: Add into .h file and have other things call it with getters and setters and such applied to the array