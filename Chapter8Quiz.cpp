#undef NDEBUG // Make sure that assert triggers even if we compile in release mode

#include <cassert> // for assert
#include <iostream>
#include <cmath> // only needed for std::sqrt() but instead of i <= sqrt(x) we used i * i <= x bc the latter is faster
#include "Random.h"
#include <utility> // used for std::swap()
#if 0
// Question 1 modify the program so the ball falls for as many seconds as needed

// Gets tower height from user and returns it

namespace Constants
{
	constexpr double gravity{ 9.8 };
}

double getTowerHeight()
{
	std::cout << "Enter the height of the tower in meters: ";
	double towerHeight{};
	std::cin >> towerHeight;
	return towerHeight;
}

// Returns the current ball height after "seconds" seconds
double calculateBallHeight(double towerHeight, int seconds)
{
	

	// Using formula: s = (u * t) + (a * t^2) / 2
	// here u (initial velocity) = 0, so (u * t) = 0
	const double fallDistance{ Constants::gravity * (seconds * seconds) / 2.0 };
	const double ballHeight{ towerHeight - fallDistance };

	// If the ball would be under the ground, place it on the ground
	if (ballHeight < 0.0)
		return 0.0;

	return ballHeight;
}

// Prints ball height above ground
void printBallHeight(double ballHeight, int seconds)
{
	if (ballHeight > 0.0)
		std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters\n";
	else
		std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
}

// Calculates the current ball height and then prints it
// This is a helper function to make it easier to do this
void calculateAndPrintBallHeight(double towerHeight)
{
	int seconds{ 0 };
	double ballHeight{};
	do
	{
		ballHeight = calculateBallHeight(towerHeight, seconds);
		printBallHeight(ballHeight, seconds);
		++seconds;
	} while (ballHeight > 0.0);
}

int main()
{
	const double towerHeight{ getTowerHeight() };

	calculateAndPrintBallHeight(towerHeight);

	return 0;
}
/*
Alternative Solution: 

double calculateAndPrintBallHeight(double towerHeight, int seconds)
{
	const double ballHeight{ calculateBallHeight(towerHeight, seconds) };
	printBallHeight(ballHeight, seconds);

	return ballHeight;
}

int main()
{
	const double towerHeight{ getTowerHeight() };

	int seconds { 0 };
	while (calculateAndPrintBallHeight(towerHeight, seconds) > 0.0)
	{
		++seconds;
	}

	return 0;
}
*/
#endif

#if 0

// Question 2
bool isPrime(int x)
{
	if (x <= 1)
	{
		return false;
	}
	if (x == 2 )
	{
		return true;
	}
	if (x % 2 == 0)
	{
		return false;
	}


	for (int i{ 3 }; i * i <= x; i+=2)  // we use  i * i 
	{
		if (x % i == 0)
		{
			return false;
		}
	}
	return true;
	// write this function using a for loop
}

int main()
{
	assert(!isPrime(0)); // terminate program if isPrime(0) is true
	assert(!isPrime(1));
	assert(isPrime(2));  // terminate program if isPrime(2) is false
	assert(isPrime(3));
	assert(!isPrime(4));
	assert(isPrime(5));
	assert(isPrime(7));
	assert(!isPrime(9));
	assert(isPrime(11));
	assert(isPrime(13));
	assert(!isPrime(15));
	assert(!isPrime(16));
	assert(isPrime(17));
	assert(isPrime(19));
	assert(isPrime(97));
	assert(!isPrime(99));
	assert(isPrime(13417));

	std::cout << "Success!\n";

	return 0;
}
#endif

int main()
{
	while (true)
	{
		std::cout << "Lets play a game of Hi-Low please input two numbers so i can pick a number between the 2: ";
		int min{};
		int max{};
		std::cin >> min >> max;
		if (min > max)
		{
			std::swap(min, max);
		}
		int randomNumber{ Random::get(min, max) };
		int Guess{};
		int guessCounter{ 1 };
		for (; guessCounter <= 7; ++guessCounter)
		{
			std::cout << "Guess #" << guessCounter << ": ";
			std::cin >> Guess;

			if (Guess > randomNumber)
			{
				std::cout << "Your guess is to high\n";
			}
			else if (Guess < randomNumber)
			{
				std::cout << "Your guess is to low\n";
			}
			else
			{
				std::cout << "Correct you win !!!!!!!\n";
				break;
			}
			
		}
		if (guessCounter > 7)
		{
			std::cout << "Sorry you lose!! the correct number was: " << randomNumber << '\n';
		}
		
		char answer{};
		while (answer != 'y')
		{
			std::cout << "Would you like to play again y/n: ";
			std::cin >> answer;
			if (answer == 'n')
			{
				return 0;
			}
		}
	}
	return 0;
}

/*
Alternatively even if answer is correct you can do that try using more functions , switch statements and constexpr:

#include <iostream>
#include "Random.h" // https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/

// Returns true if the user won, false if they lost
// We don't use the return value in this program, but it doesn't add complexity to have it, and may be useful in a future update
// (e.g. if we wanted to move the won/lost messages out of the function, or conditionalize other behavior based on won/lost)
bool playHiLo(int guesses, int min, int max)
{
	std::cout << "Let's play a game. I'm thinking of a number between " << min << " and " << max << ". You have " << guesses << " tries to guess what it is.\n";
	const int number { Random::get(min, max) }; // this is the number the user needs to guess

	// Loop through all of the guesses
	for (int count{ 1 }; count <= guesses; ++count)
	{
		std::cout << "Guess #" << count << ": ";

		int guess{};
		std::cin >> guess;

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

		switch (ch)
		{
		case 'y': return true;
		case 'n': return false;
		}
	}
}

int main()
{
	constexpr int guesses { 7 }; // the user has this many guesses
	constexpr int min     { 1 };
	constexpr int max     { 100 };

	do
	{
		playHiLo(guesses, min, max);
	} while (playAgain());

	std::cout << "Thank you for playing.\n";

	return 0;
}
*/