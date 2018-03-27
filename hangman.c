/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //randomizer seed
#include <ctype.h>

void seedRandomizer() {
    time_t startTime;
    srand((unsigned) time(&startTime));
}//takes the time and uses it to seed rand or else the words get pretty predictable.









/*
 * 
 * char enforceLowerCase(guess)
 * just takes guess and makes it equal itself in lower case. guess = tolower(guess); or somesuch maybe do this all in one like in python version*/
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


int main()
{
    while (hangmanStrikes < 7) 
    {
        getword();
        hangman();
    }
    
    return 0;
}*/