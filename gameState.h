/** @file gameState.h
 * @brief Everything to do with player interactions with the game and player interactions.
 * 
 * This .h file prototypes the gameState struct and all of the associated functions that act on it. Essentially everything about the game
 * minus the core loop itself and the actual construction of a list to pick an answer from and the picking of that answer.
 * The struct containing possible answers and associated functions live in wordList.h and wordlist.c.
 * 
 * @author David McBurney
 * @bug None I'm aware of.
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

/** @struct gameState
 * @brief Struct containing all the information about player guesses and the correct answer.
 * A struct meant to essentially hold everything to do with the game as an onogoing concern. 
*/
typedef struct {
char *hangmanGuess; /**< Holds malloced char pointer to the current guess. */
char *correctGuesses; /**< Holds malloced char pointer to what has been guessed correctly so far. */
char *hangmanAlreadyGuessed; /**< Holds malloced char pointer to everything that has been guessed. */
char *hangmanAnswer; /**< Holds malloced char pointer to the answer itself. */
int numberOfGuesses; /**< Int to track the total number of unique guesses which is used to keep hangmanAlreadyGuessed up to date. */
int answerLength; /**< Int to track the length of the answer which is necessary for any loop that compares to the answer. */
int hangmanStrikes; /**< Int to track the number of strikes which increments until it reaches a point where it stops the main loop, ending in a player loss.*/
int isGuessCorrect; /**< Int that acts as a bool, set in isGuessCorrect to decide whether to increment hangmanStrikes. */
int isEnd; /**< Int that acts as a bool, stays 0 unless set to 1 by isGameOver signalling player victory */
int randomizationScheme; /**< Currently sets whether to use getAnswer or seekAnswer, could be expanded with more randomization schems I suppose*/
}gameState;

/** @brief Loops through string and replaces newline character with string termination.
 * Takes in a gameState pointer and returns void.
 * Function is a simple loop that replaces any newline('\n') with a termination character('\0').
 * Called when the answer is first obrained from the wordList in getAnswer.
 * (Work out what this does if it encounters no newline)
 * Currently needs debugging.
 * @param gameState *game, specifically acts on char *hangmanAnswer, terminating the string at first newline
 * @return Void
 */
void trimEndOfString(gameState *game);

/** @brief Seeds the random number generator for selecting hangmanAnswer
 * Requires time.h
 * Assigns a seed for rand based on time since Unix Epoch.
 * Called in getAnswer, really shouldn't be called twice.
 * Entire program's built to run once and exit, if you want more hangman run it again.
 * @param Void
 * @return Void
 */
void seedRandomizer();

/** @brief Loops through correctGuesses and sets every address before
 *         the terminating character to underscores.
 * Another simple loop function that takes a gameState pointer and returns void.
 * This one loops through game->correctGuesses to the length of answerLength
 * and assings an underscore for each letter. This is called in createGameState
 * so it can be in place just long enough to be replaced by user guesses.
 * @param gameState *game, acts on char *correctGuesses, converting its contents to underscores
 * @return Void
 */
void getUnderlines(gameState *game);

/** @brief Loops through hangmanAnswer and applies tolower to every address.
 * Requires ctype.h
 * Another loop that takes a gameState pointer and returns void.
 * This one loops through each letter in hangmanAnswer and ensures they're lowercase.
 * This ensures that the player isn't caught off guard by case issues.
 * This one is called in the main game loop to make sure no other alterations are waiting to be made to hangmanAnswer.
 * @param gameState *game, acts on char *hangmanAnswer calling tolower on every address
 * @return Void
 */
void answerLowerCase(gameState *game);

/** @brief Creates a wordList to get a random word to assign to hangmanAnswer
 *         then calls the functions to make it useable for the game.
 * Yet another one that takes in a gameState pointer and returns void.
 * Lot more going on with this one. It's called by createGameState
 * but it in turn calls createWordList from wordList.c/h and calls everything
 * to do with picking a random word and assigning that value to hangmanAnswer.
 * These are better described in wordList.h but in short:
 * createWordList makes a bunch of default values for wordList, 
 * getWordList assigns every newline seperated word in the given file to an expanding char**,
 * getWord uses rand and modulo to get a random valid array address then strdups whatever's there to hangmanAnswer,
 * trimEndOfString is described above,
 * answerLength is then assigned now that the final length of the answer should be known.
 * finally the wordList file is closed.
 * @param gameState *game, acts on char *hangmanAnswer
 * @return Void
 */
void getAnswer(gameState *game);

/** @brief Constructoer for gameState struct, initializes most of what's in the struct.
 * Takes a gameState pointer and returns void.
 * This calls the aforementioned getAnswer and then mallocs and assigns
 * all the char pointers in the gameState struct.
 * The only thing in that struct not given a default value here
 * is isGuessCorrect which is only assigned in testGuess.
 * These default values should be fine in case something goes horribly
 * wrong and the entire thing somehow runs without a guess but otherwise should go unused.
 * Otherwise they're just logically initiating countup ints at 0.
 * getUnderlines is also called here.
 * @param gameState *game, assigns int hangmanStrikes, numberOfGuesses and, isEnd, 
 *        mallocs char *CorrectGuesses, and char *hangmanAlreadyGuessed, calls
 *        function that assigns char *hangmanAnswer
 * @return Void
 */
void createGameState(gameState *game);

/** @brief Makes the second address in hangmanGuess into a termination character.
 * Takes in a gameState pointer and returns void.
 * This does much the same thing as trimEndOfString except it does it to guess.
 * In this case a valid guess is only 1 character so the termination is assighend to hangmanGuess[1].
 * This is of course contingent on hangmanGuess having a length > 1
 * @param gameState *game, acts on char *hangmanGuess by ensuring its size is < 2
 * @return Void
 */
void trimGuess(gameState *game);

/** @brief Takes in a guess from terminal input and ensures it's valid 
 *         adding it to hangmanAlreadyGuessed if it's new.
 * Takes in a gameState pointer and returns void.
 * Takes in player input via fgets with a big buffer. to aoid someone accidentally overflowing it.
 * If the player tries to enter anything other than a letter it returns a message asking for one
 * and then calls the function again from the top.
 * It then checks if the guess has been used before and exits if it has to make sure the
 * hangmanAlreadyGuessed array's 26 possible entries can't overflow.
 * If the guess is new it adds it to the hangmanAlreadyGuessed array and increments
 * numberOfGuesses.
 * @param gameState *game, assigns to char *hangmanGuess
 * @return Void
 */
void getGuess(gameState *game);

/** @brief Checks if the entered guess is correct and sets isGuessCorrect
 *         to determine if hangmanStrikes needs incrementing.
 * Function starts by setting isGuessCorrect to 0 and then loops through
 * comparing hangmanAnswer to hangmanGuess[0], if they ever match the function
 * inserts the match into the same address in the corretGuesses array and sets
 * isGuessCorrect to 1.
 * If isGuessCorrect is still 0 once the loop is done hangmanStrikes is 
 * incremented.
 * @param gameState *game, alters char *correctGuesses, can increment hangmanStrikes
 *        sets isGuessCorrect
 * @return Void
 */
void testGuess(gameState *game);

/** @brief Loops through correctGuesses and adds any apostrophes in the same
 *         address as hangmanAnswer.
 * Another simple loop through the hangmanAnswer and correctGuesses arrays
 * this is to aoid having to throw out anything with an apostrophe and 
 * roll a new word.
 * @param gameState *game, changes char *correctGuesses
 * @return Void
 */
void addApostrophes(gameState *game); 

/** @brief Tests if hangmanAnswer and correctGuesses are equal and sets isEnd
 *         to 1 if they're equal, ending the primary while loop.
 * Loops through hangmanAnswer and corectGuesses until answerLength addresses
 * and returns if there's a discrepancy.
 * If there are none it sets isEnd to 1 forcing the main loop to end.
 * @param gameState *game, can set isEnd to 1
 * @return Void
 */
void isGameOver(gameState *game);

/**@brief Prints the actual hangman.
 * Takes in game to test the value of hangmanStrikes.
 * Prints an increasingly complete hangman the more strikes
 * there are. Prints the full hangman and a lame joke at 7.
 * @param gameState game, not a pointer, checks but doesn't modify hangmanStrikes.
 * @return Void
 */
void printHangman(gameState game);

#endif
