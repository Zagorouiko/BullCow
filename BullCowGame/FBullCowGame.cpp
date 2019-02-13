#pragma once
#include "FBullCowGame.h"
#include <map>
#include <cctype>
#define TMap std::map

//DEFINE ALL PROPERTIES AND METHODS FROM THE HEADER HERE

FBullCowGame::FBullCowGame() {
	Reset();
}

//run time values
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,5}, {5,5}, {6,5} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; //^^Maps to first digit^^
}


bool FBullCowGame::IsIsoGram(FString Word) const {
	if (Word.length() <= 1) { return true; }
	
	TMap<char, bool> LetterSeen; //list of characters (word)

	for (auto Letter : Word) {    //single character (letter)
		Letter = tolower(Letter);

		if (LetterSeen[Letter]) { //if letter is in the word
			return false; //exit as false
		}
		else {
			LetterSeen[Letter] = true; //continue loop
		}
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const {

	if (Word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;

	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
		return true;
	}
}

void FBullCowGame::Reset() {
	bGameIsWon = false;
	MyCurrentTry = 1;
	MyHiddenWord = "planet"; //this MUST be an isogram
	return;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++; //<--IS ABLE TO ACCESS PRIVATE PROPERTIES FROM HEADER FILE

	FBullCowCount BullCowCount; //Set up a return value

	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++) {
		if (MyHiddenWord[i] == Guess[i]) {
			BullCowCount.Bulls += 1;
		}
		else {
			for (int32 j = 0; j < HiddenWordLength; j++) {
				if (MyHiddenWord[i] == Guess[j]) {
					BullCowCount.Cows += 1;
				}
			}
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) {

	if (!IsIsoGram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWord().length()) {
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}
