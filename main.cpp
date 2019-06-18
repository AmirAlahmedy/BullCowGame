/*
	This acts as the view in an MVC pattern.
*/
#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include "FBullCowGame.h"


// to make the syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // Instantiate a new game, reuse across plays

int main() 
{

	do {
		PrintIntro();
		PlayGame();
	} 
	while (AskToPlayAgain());

	return 0;
}

void PrintIntro() 
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "           }   {           ___ " << std::endl;
	std::cout << "           (o o)          (o o) " << std::endl;
	std::cout << "   /--------\\ /            \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL  |O              O| COW  | \\ " << std::endl;
	std::cout << " *  |-----  |                |---,--|  * " << std::endl;
	std::cout << "    ^       ^                ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}


// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking guesses while the game is not won
	// and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){

		FText Guess = GetValidGuess(); 


		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// print number of bulls and cows.
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	FText Guess = "";

	do {
		int32 CurrentTry = BCGame.GetCurrentTry();

		// Get a guess from the user.
		std::cout << CurrentTry << " of " <<BCGame.GetMaxTries() <<". " << "Enter your guess: ";
		std::getline(std::cin, Guess);

		// transform the guessed word to lowercase
		std::transform(Guess.begin(), Guess.end(), Guess.begin(), ::tolower);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram.\n\n";
		default:
			// assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get a valid guess
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	getline(std::cin, Response);

	return tolower(Response[0]) == 'y' ? true:false;
}

void PrintGameSummary()
{	
	if (BCGame.IsGameWon())
		std::cout << "WELL DONE YOU WON!\n";
	else
		std::cout << "Better luck next time!\n";
	return;
}
