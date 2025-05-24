// Quiz 9 make sure invalid guesses, out of bounds guesses or valid guesses that have extra characters are handled

#include <iostream>
#include "Random.h" //https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/
#include <limits>
// Returns true if the user won, false if they lost
// We don't use the return value in this program, but it doesn't add complexity to have it, and may be useful in a future update
// (e.g. if we wanted to move the won/lost messages out of the function, or conditionalize other behavior based on won/lost)

void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//instead of std::cin.ignore(100,'\n') which only clears 100 extra input until the '\n' but we use the one that clears every extra input and we put it in a function for ease of use
}

bool clearFailedExtraction()
{
	// this replaces the if(std::cin.fail()) we used in another functions bc this now also included EOF
	if (!std::cin)
	{
		if (std::cin.eof()) // If the user entered an  EOF
		{
			std::exit(0); // Shut down the program with exit code 0 bc we want to shut down the program if someone uses an EOF bc thats how its mostly intended
		}
		std::cin.clear();
		ignoreLine();
		return true;
	}
	return false;
	// This and the if(std::cin.fail()) also handles case 4 where the user overflows the numeric value 
}

bool hasUnextractedInput()
{
	/*
	std::cin.eof() returns true if the last input reached the end of the input stream
	std::cin.peek() only looks at the the the next character without extraction it
	*/
	return !std::cin.eof() && std::cin.peek() != '\n';
	//returns true if std::cin has unextracted input on the current line false otherwise
}

int takeGuess(int min, int max)
{
	
	while (true)
	{
		int x{};
		std::cin >> x;
		if (clearFailedExtraction())
		{
			std::cout << "Invalid Input please try again\n";
			continue;
		}

		if (hasUnextractedInput())
		{
			ignoreLine();
			std::cout << "Invalid Input please try again\n";
			continue;
		}
		if (x < min)
		{
			std::cout << "The number that was typed in is below the range of numbers please type smth between " << min <<" and " << max << '\n';
			continue;
		}
		if (x > max)
		{
			std::cout << "The number that was typed in is above  the range of numbers please type smth between " << min << " and " << max << '\n';
			continue;
		}
		return x;

	}

	
}

bool playHiLo(int guesses, int min, int max)
{
	std::cout << "Let's play a game. I'm thinking of a number between " << min << " and " << max << ". You have " << guesses << " tries to guess what it is.\n";
	const int number{ Random::get(min, max) }; // this is the number the user needs to guess

	// Loop through all of the guesses
	for (int count{ 1 }; count <= guesses; ++count)
	{
		std::cout << "Guess #" << count << ": ";

		int guess{};
		guess = takeGuess(min,max);

		if (guess > number)
			std::cout << "Your guess is too high.\n";
		else if (guess < number)
			std::cout << "Your guess is too low.\n";
		else // guess == number, so the user won
		{
			std::cout << "Correct! You win!\n";
			return true;
		}
	}

	// The user lost
	std::cout << "Sorry, you lose. The correct number was " << number << '\n';
	return false;
}

bool playAgain()
{
	// Keep asking the user if they want to play again until they pick y or n.
	while (true)
	{
		char ch{};
		std::cout << "Would you like to play again (y/n)? ";
		std::cin >> ch;
		if (clearFailedExtraction())
		{
			std::cout << "Invalid Input please try again\n";
			continue;
		}
		
		if (hasUnextractedInput())
		{
			ignoreLine();
			std::cout << "Invalid Input please try again\n";
			continue;
		}
		switch (ch)
		{
		case 'y': return true;
		case 'n': return false;
		default:
			std::cout << "Invalid Input please try again\n";
		}
	}
}

int main()
{
	constexpr int guesses{ 7 }; // the user has this many guesses
	constexpr int min{ 1 };
	constexpr int max{ 100 };

	do
	{
		playHiLo(guesses, min, max);
	} while (playAgain());

	std::cout << "Thank you for playing.\n";

	return 0;
}