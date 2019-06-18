#pragma once

#include "FBullCowGame.h"
#include <map> 

// to make the syntax Unreal friendly
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {	return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,18} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}



FBullCowGame::~FBullCowGame()
{
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "donkey"; // this MUST be an isogram
	
	
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))	// if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (Guess.length() != GetHiddenWordLength())	// the guess length is wrong
	{	
		return  EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{	 
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all the letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; ++MHWChar) {
		// compare letters against the guess word
		for (int32 GChar = 0; GChar < WordLength; ++GChar) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				// if they are in the same place
				if (MHWChar == GChar)
					BullCowCount.Bulls++;
				else
					BullCowCount.Cows++;
			}

		}
	}
	if (BullCowCount.Bulls == WordLength)
		bGameIsWon = true;
	else
		bGameIsWon = false;
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 words as isograms
	if (Word.length() < 2) return true;

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word){

		Letter = tolower(Letter);
		if (LetterSeen[Letter]) // if the letter is in the map/dictionary
			return false; // we do NOT have an isogram
		else
			LetterSeen[Letter] = true; // add the letter to the map as seen
	}
	

	return true; // for example in cases where /0 is entered
}
