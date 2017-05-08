/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind*/


#pragma once
#include <string>

//to make syntax Unreal freindly
using FString = std::string;
using int32 = int;


struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};
enum EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase

};

class FBullCowGame {
public:
	FBullCowGame();//constructor
	int32 GetLevel() ;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength()const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(); 
	// counts bulls & cows, and increases try # assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

// ^^ Please try and ignore this and focus on the interface above ^^
private:
	int32 MyCurrentLevel = 0;
	int32 MyCurrentTry=1;
	FString MyHiddenWord;
	bool bGameWon;

	FString SelectHiddenWord(void)const;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};