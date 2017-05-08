#include "FBullCowGame.h"
#include <map>
#define TMap std::map

int32 FBullCowGame::GetLevel() { return MyCurrentLevel; }
int32 FBullCowGame::GetCurrentTry() const {	return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const{return bGameWon;}

int32 FBullCowGame::GetMaxTries() const {	
	TMap<int32, int32> WordLengthToMaxTries{ {3,5},{4,5},{5,5},{6,5} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}
FBullCowGame::FBullCowGame() {
	Reset();
}
FString FBullCowGame::SelectHiddenWord(void) const
{
	TMap <int32, FString> HiddentWordList{ { 1,"ant" },{ 2,"tiger" },{ 3,"planet" } };
	return HiddentWordList[MyCurrentLevel];
}
void FBullCowGame::Reset()
{	
	const FString HIDDEN_WORD = SelectHiddenWord();// this MUST be an isogram
	MyCurrentLevel++;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameWon = false;

	return;
}


//receives a VALID guess, increments turn, and returns count. 
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();//assuming same length as guess

	//loop through all letters in the hidden word
	

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		//compare letters against guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//if they match tehn
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				
				if (MHWChar == GChar) { //if they're in the same place
					//increment bulls
					BullCowCount.Bulls++;
				}	
				//else
				else {
					//must be a cows
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (WordLength == BullCowCount.Bulls) {
		bGameWon = true;
	}
	else {
		bGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1){ return true;}//treat 0 and 1 letter word as isograms

	TMap<char, bool> LetterSeen;//setup our map
	for (auto Letter : Word)//loop through all the letters of the word
	{
		Letter = tolower(Letter);//handle mixed case
		if (LetterSeen[Letter]) {//if the letter is in the map
			return false;//we do Not have an isogram
		}
		else {//otherwise 
			LetterSeen[Letter] = true;//add the letter to the map as seen
		}
	}

	return true;// for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) 
		{
			return false;
		}
	}
	return true;
}




EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!(IsIsogram(Guess)))//if the guess isn't an isogram, 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!(IsLowercase(Guess)))
	{//if the guess isn't all lowercase,
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length()!=GetHiddenWordLength())
	{//if the guess length is wrong
		return EGuessStatus::Wrong_Length;
	}
	else
	{//otherwise
		return EGuessStatus::OK;
	}

}

