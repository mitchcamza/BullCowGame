/*	This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern and it is responsible for all user interaction.
For game logic, see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// make the following substitutions, as per Unreal's coding standards:
using FText = std::string;	// makes a substitution between FText and std::string
using int32 = int;			// int is a primitive type, so we don't need the std:: in front


// function prototypes, as functions are outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

// create an instance of FBullCowGame to be used accross plays (create a new game each time)
FBullCowGame BCGame;


// the entry point for our game
int main()
{
	bool bPlayAgain = false;
	do 
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();

	} while (bPlayAgain);	 
	
	return 0;	// exit the application
}


void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}


// plays a single game to completion
void PlayGame()
{
	// make use of the reset method to set default values for MyMaxTry and MyCurrentTry
	BCGame.Reset();

	// sets MaxTries via the GetMaxTries method
	int MaxTries = BCGame.GetMaxTries();
	
	// ask the player to guess the word
	// loop for number of turns, asking for guesses while 
	// the game is NOT won and that there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)	
	{
		// get guess and print the guess back to them
		FText Guess = GetValidGuess();	

		// submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}


// loop continuously, until the user enters a valid guess
FText GetValidGuess()	
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;	// set the status to invalid by default
	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ": Enter your guess: ";		
		std::getline(std::cin, Guess);

		// create an enum to check the guess validity
		Status = BCGame.CheckGuessVailidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n\n";
			break;
		default:
			// assuming the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);	// keep looping until we get no errors

	return Guess;
}


void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations! You guessed the word correctly!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
	return;
}


bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText response = "";
	std::getline(std::cin, response);
	std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;

	// get response from user and ignore all, but the first character
	return (response[0] == 'y') || (response[0] == 'Y');
}
