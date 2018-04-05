
int listLength;
int randomWordAddress;
//put bottom two into gamestate, find way to excise top two

typedef struct {
char *hangmanGuess;
char *hangmanCorrect;
char *hangmanAlreadyGuessed;
int numberOfGuesses;
char *hangmanAnswer;
int answerLength;
}gameState;

//put these in a struct later,gameState maybe, also give them initialized values
