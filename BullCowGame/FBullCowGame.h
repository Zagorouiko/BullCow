/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>

//DECLARE ALL PROPERTIES AND METHODS HERE


//Make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

//Strongly typed Enum (has class), Able to make multiple enums with the same types (ex: OK)
enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	//Constructor
	FBullCowGame();

	//Getters
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	FString GetHiddenWord() const;
	bool IsGameWon() const;
	

	//Methods, here parameters don't need names, only in the declaration in the ccp file
	FBullCowCount SubmitValidGuess(FString);
	EGuessStatus CheckGuessValidity(FString);
	

	void Reset();

	//Compile time values
private:
	//Set by constructor
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	//Helper methods
	bool IsIsoGram(FString) const;
	bool IsLowerCase(FString) const;
};