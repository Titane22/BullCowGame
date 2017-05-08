/*This is the console executable,that makes  use of the BullCow class
This acts as the view in a MVC pattern , and is responsible for all 
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"


using FText = std::string;

void EndGame();
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;//instantiate a new Game, which we re-use acriss plays

// the entry point for our application
int32 main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		if (BCGame.GetLevel()!=4) {
			bPlayAgain = AskToPlayAgain();
		}
		else {
			EndGame();
			break;
		}
	}
	while (bPlayAgain);
	
	return 0; // exit the application
}


// introduce the game
void PrintIntro()
{
	if (BCGame.IsGameWon()) {
		std::cout << "\n\n";
	}
	
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "This Level is " << BCGame.GetLevel() << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}


void PlayGame()
{	
	BCGame.Reset();
	int32 MaxTries=BCGame.GetMaxTries();
	// loop asking for guesses while the game is NOT won
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		//Submit valid guess to the game , and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl << std::endl;
		
	}
	PrintGameSummary();
}

//loop continually untill the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status=EGuessStatus::Invalid_Status;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		// get a guess from the player

		std::cout << "Try." << CurrentTry << " of " << BCGame.GetMaxTries() ;
		std::cout<< ". Enter your guess: ";
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << "letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lower case letters.\n";
		default:
			//assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
void PrintGameSummary() {
	if (BCGame.IsGameWon()) 
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else 
	{
		std::cout << "Better luck next time!\n";
	}
}
void EndGame() {
	std::cout << "Congratulations!!! You cleared all Level~!\n";
}