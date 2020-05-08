#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map

// make the following substitutions, as per Unreal's coding standards:
using int32 = int;							// int is a primitive type, so we don't need the std:: in front
FBullCowGame::FBullCowGame() { Reset(); }	// default constructor - calls the reset function to reset values at the start of each game

// BEST PRACTICE TIPS:
// it is common to have the getter function definitions at the top and in the layout shown below
// getter methods should always be accessors (ie. they should end in the keyword "const")
// functions that belong to a class are know as member functions.
// the const keyword only works for member functions


// get methods
int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}	
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}	// reads the word length from the current hidden word
bool FBullCowGame::IsGameWon() const {return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries {{3,4}, {4,7}, {5,10}, {6,16}, {7,20}};	// map the wordlength to max tries
	return WordLengthToMaxTries[MyHiddenWord.length()];	// parse hidden word length to get the max tries
}


void FBullCowGame::Reset()
{
	// run-time values for GetMaxTries and GetCurrentTry
	// constexpr int32 MAX_TRIES = 8;		// no longer required
	const FString HIDDEN_WORD = "ant";		// this must be an isogram
											// TODO allow the user to choose the word length
											// TODO create a map of words to be used
											// TODO create a text file with words to be used

	MyHiddenWord = HIDDEN_WORD;
	// MyMaxTries = MAX_TRIES;				// no longer required
	MyCurrentTry = 1;
	bGameIsWon = false;						// reset bGameIsWon to false
	return;
}


// check for possible errors
EGuessStatus FBullCowGame::CheckGuessVailidity(FString Guess) const
{
	if (!IsIsogram(Guess))								
	{
		return EGuessStatus::Not_Isogram;
	} 
	else if (!ISLowercase(Guess))						 
	{
		return EGuessStatus::Not_Lowercase;	
	}
	else if (Guess.length() != GetHiddenWordLength())	
	{
		return EGuessStatus::Wrong_Length;	
	}
	else 
		return EGuessStatus::OK;
}


// receives a VALID guess. Increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	
	MyCurrentTry++;
	FBullCowCount BullCowCount;									// set up a return variable	
	int32 WordLength = MyHiddenWord.length();					// assuming the same length as guess

	// loop through all the letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)	// MHWChar is an abreviation for MyHiddenWordCharacter
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)		// GChar is an abbreviation for GuessCharacter
		{		
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{					
				if (MHWChar == GChar)		// if they are in the same place
				{
					BullCowCount.Bulls++;	// increment bulls
				}
					 
				else
				{
					BullCowCount.Cows++;	// must be a cow
				}					
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}		
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}


bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) {return true;}
	
	// set up our map
	TMap<char, bool> LetterSeen;	
	
	// uses order n to test whether the word is an isogram (see Big O notation)
	for (auto Letter : Word)			// see range based for loops
	{
		Letter = tolower(Letter);		// handle mixed case (store only lowercase letters)
			// loop through all the letters of the word
			if (LetterSeen[Letter])	{	// if the letter is in the map
				return false;			// we do NOT have an isogram
			}
			else {
				LetterSeen[Letter] = true;	// add the letter to the map as seen
			}					
	}	
	return true;	// for example, in cases where /0 is entered
}


bool FBullCowGame::ISLowercase(FString Word) const
{
	TMap<char, bool> IsLowercase;	
	for (auto Letter : Word)	// loop through each letter of the word and check if the current letter is lowercase
	{ 
		if (!islower(Letter))	// if not a lowercase letter
		{
			return false;
		}			
	}
	return true;
}
