/* The game logic
The game is a simple "guess the word" game based on "Mastermind"
*/

// * NB it is bad programming practice to use namespace in a header file *
// All values initialised to zero

#pragma once	//assures that anything that is imported is only imported once
#include <string>

// make the following substitutions, as per Unreal's coding standards:
using FString = std::string;
using int32 = int;		// int is a primitive type, so we don't need the std:: in front


struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0; 
};


enum EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
};


class FBullCowGame
{
public:
	FBullCowGame();	// constructor declaration

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessVailidity(FString) const;	

	void Reset();											
	FBullCowCount SubmitValidGuess(FString);			// counts bulls and cows and increases try number, assuming valid guess


// ^^ Please ignore this and focus on the interface above ^^
private:
	
	// compile-time values - see constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	// helper methods
	bool IsIsogram(FString) const;
	bool ISLowercase(FString) const;
};
