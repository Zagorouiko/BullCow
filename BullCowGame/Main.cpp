/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

//function prototypes as outside a class, these aren't in the header file so they're here
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintOut(FText Guess);
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGAME;  //Instantiate a new game, which we reuse across plays

//Entry point
int32 main() {

	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0; // exit the application

}

//Plays single game to completion
void PlayGame() {

	BCGAME.Reset();
	int32 MaxTries = BCGAME.GetMaxTries();

	while (!BCGAME.IsGameWon() && BCGAME.GetCurrentTry() <= MaxTries) {		
			
			FText Guess = GetValidGuess();
			PrintOut(Guess);
					
			FBullCowCount BullCowCount = BCGAME.SubmitValidGuess(Guess);

			std::cout << "Bulls = " << BullCowCount.Bulls;
			std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

void PrintIntro() {
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGAME.GetHiddenWord().length();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

//Get Guess
FText GetValidGuess() {
	
	EGuessStatus Status = EGuessStatus::Invalid_Status; //initializes the variable, just a placeholder
	FText Guess = ""; //declared outside so "return guess" can be outside the loop therefore each case will be able to fire if needed

	//While loop runs once initially, then runs again if the while is true. Exits if false
	do {
		int32 CurrentTry = BCGAME.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " out of " << BCGAME.GetMaxTries() << "\nEnter Your Guess:";
		
		getline(std::cin, Guess);


		EGuessStatus Status = BCGAME.CheckGuessValidity(Guess);
		//Catches if error
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "\nPlease Enter a " << BCGAME.GetHiddenWord().length() << " letter word.\n";
			break; // so code underneath doesn't run
		case EGuessStatus::Not_Lowercase:
			std::cout << "\nPlease Enter all lower case.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "\nPlease Enter a word without repeating letters.\n ";
			break;
		default: //Assume guess is valid
			return Guess;
			break;
		}
	} while (Status != EGuessStatus::OK);
}

//Print out
void PrintOut(FText Guess) {
	std::cout << "Your guess was: " << Guess << std::endl;
}

bool AskToPlayAgain() {

	std::cout << "Do you want to play again? y/n ";
	FText Response = "";
	getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGAME.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}


