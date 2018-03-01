#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //randomizer seed
#include <ctype.h>

int hangmanStrikes = 0; //This is at least simple, increment this up every time they screw up
char *guess;
FILE *wordListFile; // 2D resizing array of resizeable char arrays?
char *answer;
char *randomWordList[];

//func to remove last non \0 character from string
//func that resizes an array
//

char getWord()
{
    wordListFile = fopen("/usr/share/dict/words", "r");
    //while fgets(randomWordList, 
    //
    fclose(wordListFile);
}

//type? checkGuess(guess)
//{
    /* probably a for loop through array 1, printing matches into array, easier said than done but at least their lengths are known and they match.
//}*/

/*
 * 
 * char enforceLowerCase(guess)
 * just takes guess and makes it equal itself in lower case. guess = tolower(guess); or somesuch*/
/*
 * void addToGuessed(arrayOfGuessedLetters)
 * append to end of array, start at n = 0 and incrementt value of n, could be lazy and make the array sized 26 or could get fancy and make it expanding
 * */
 /*
  * void missedGuess takes in a boolean that if true causes nothing and if false increments hangmanStrikes
  * to be paired with type? checkGuess(guess) which will set boolean to false, loop through, change any address that matches the guessed letter in the correct answer array,
  * and set that boolean to true, then call void missedGuess*/
  /*
   * 

void hangman()
{
    guess = malloc(2);
    printf("Please enter a guess\n");
    guess = fgets(guess, sizeof(guess + 1), stdin); // change fgets fgetc?
    hangmanStrikes++;
    free (guess);
}

int main()
{
    while (hangmanStrikes < 7) 
    {
        getword();
        hangman();
    }
    
    return 0;
}