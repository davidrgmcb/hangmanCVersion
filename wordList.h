/** @file wordList.h
 * @brief Everything to do with the wordList struct where a random is selected from.
 * wordList.h prototypes functions in wordList.c that control the wordList struct
 * the size of its possible answers array and the copying of new words into it
 * as well as the copying of a random word into the gameState struct
 * @bug no known bugs, wordList not properly freed though.
 */

#include <stdlib.h>
#include <stdio.h>
#include "gameState.h"


#ifndef WORDLIST_H
#define WORDLIST_H

/** @brief Contains everything the wordlist needs to expand and track itself.
 * FILE pointer points to the file that will have words randomly pulled from.
 * char **possibleAnswers is an expandable malloced array of strings expanded
 * by expandArray. arraySize tracks the size of possibleAnswers so it is known
 * when to call expandArray. highestFilledArray tracks how much of possibleAnswers
 * is full and is compared to arraySize.*/
typedef struct {
FILE *wordListFile;
char **possibleAnswers;
int arraySize;
int highestFilledArrayAddress;
}wordList;

#define ARRAY_FILL_START 0
#define BASE_ARRAY_SIZE 10

/** @brief Constructor that puts in default values for a wordList struct.
 * Initializes highestFilled array address and arraySize then
 * mallocs possibleAnswers byased on araySize's initial value.
 * @param wordlist *words, gives default values to highestFilledArrayAddress and arraySize, mallocs possibleAnswers
 * @return Void
 */
void createEmptyWordList(wordList *words);

/** @brief Doubles the size of wordList.possibleAnswers when it's about to overflow.
 * Multiplies arraySize by 2 then reallocs possibleAnswers to match its size.
 * @param wordList *words, changes arraySize and possibleAnswers.
 * @return Void
 */
void expandArray(wordList *words);

/** @brief Checks if possibleWords needs expanding and adds a word to the possibleWords char** 
 *        at highestFilledArrayAddress stored in buffer from getWordList
 * Starts by comparing highestFilledArrayAddress to arraySize, if they are equal then expandArray
 * is called. Otherwise the string held in buffer is strduped to possibleWords{highestFilledArrayAddress].
 * @param wordList *words, adds words to char **possibleWords, char* buffer, copied into possibleWords.
 * @return Void
 */
void addWord(wordList *words, char *buffer);

/** @brief Returns the value of words.highestFilledArrayAddress.
 * @param wordList words, just returns the value of highestFilledArrayAddress.
 * @return int equal to highestFilledArrayAddress
 */
int wordListLength(wordList words);

/** @brief Copies a string at a randomly chosen address in the possibleAnswers array
 *        into the hangmanAnswer char * in gameState *game
 * Pretty direct one line strdup
 * @param wordList words, nothing altered just copied from, gameState *game, string copied into char* hangmanAnswer
 * @return Void
 */
void getWord(wordList words, gameState *game);

/** @brief opens a file and calls addWord to read from it and return a full list of every word.
 *         Presumes each line contains only one word seperated by newlines.
 * Starts by opening a file, by default it uses Linux default user dictionary.
 * Declares a char[256] called buffer to store a word temporarily. Calls addWord
 * until fgets returns a null pointer.
 * @param wordlist *words, increments highestFilledArrayAddress and sets the file for wordListFile
 * @return Void
 */
void getWordList(wordList *words);

/** @brief Loops through possibleAnswers freeing every address
 * Called in getAnswer in gameState.c to release all the malloced
 * memory for the wordList since it's no longer important.
 * @param wordList *words, frees all strings in possibleAnswers
 * @return Void
 */
void destroyWordList(wordList *words);

/** @brief Selects a random answer by seeking a random point in the file
 * Called in getAnswer if game.randomizationScheme is set to 1
 * Opens the wordListFile and seeks to the endof it.
 * Saves that value as an int and rewinds the file pointer to the beginning.
 * A random point in the file is then picked and saved in fileRand
 * which is then used as the offset for an fseek call from the beginning of the file.
 * The char at that point is saved in currentChar which is used to set up a loop
 * to seek backwards through the file until a newline is found and fgets the following
 * line. This solution once again presumes 1 word lines seperated by '\n' characters.
 * Once a valid position is found the resultant fgets is strduped to game.hangmanAnswer
 * wordListFile is closed in getAnswer.
 * @param wordList *words, opens wordListFile but otherwise uses little of it
 *        gameState *game, assigns hangmanAnswer.
 * @return Void
 */
void seekWord(wordList *words, gameState *game);

#endif
