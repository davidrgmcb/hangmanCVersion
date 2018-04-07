
//put bottom two into gamestate, find way to excise top two

typedef struct {
char *hangmanGuess;
char *hangmanCorrect;
char *hangmanAlreadyGuessed;
int numberOfGuesses;
char *hangmanAnswer;
int answerLength;
int hangmanStrikes;
int isGuessCorrect;
int isEnd;
}gameState;

//put these in a struct later,gameState maybe, also give them initialized values
