#include <iostream>

void blowUpWorld()
{
	std::cout << "Kabooooom!!!\n";
}

int getValue()
{
	return 5;
}

int main()
{
#if 0
	std::cout << "Enter an integer: ";
	int x{};
	std::cin >> x;

	// One of the most common semantic errors are conditional ones, here we used  >= instead of >
	if (x >= 5) // if we type in 5 it says 5 is greater than 5
	{
		std::cout << x << " is greater than 5\n";
	}

	// here another example the loop never starting bc of the semantic error
	for (int count{ 1 }; count > x; ++count)
	{
		std::cout << count << ' ';
	}
	std::cout << '\n';


	// Another common semantic error are accidental infinite loops e.g

	for (unsigned int count{ 5 }; count >= 0; --count)
	{
		if (count == 0)
		{
			std::cout << "blastoff! ";
		}
		else
		{
			std::cout << count << ' ';
		}
		std::cout << '\n';
		// this is infinite bc  we use >= instead of > making it overflow or change unsigned to signed
	}


	// Another loop related semantic error is off by one error e.g
	// This one loops one to few times so we only get 1 2 3 4 instead of 1 2 3 4 5
	for (int count{ 1 }; count < 5; ++count)
	{
		std::cout << count << ' ';
	}
	std::cout << '\n';

	// Another common semantic error is incorrect operator precedence

	int x{ 5 };
	int y{ 7 };

	if (!x > y) // bc ! has a higher precedence than > , we get a semantic error use () to avoid that
	{
		std::cout << x << " is not greater than " << y << '\n';
	}
	else
	{
		std::cout << x << " is not greater than " << y << '\n';
	}


	// Another common semantic erro are precision issues with floating point types e.g

	float f{ 0.123456789f }; //bc of lack of precision only 0.123457 is saved and that might lead to errors
	std::cout << f << '\n';
	// thats why its not recommended using == and != with floating point numbers bc it can be prpblematic

	double d{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 };

	if (d == 1.0)
	{
		std::cout << "equal\n";
	}

	else
	{
		std::cout << "not equal\n"; // this will execute bc of rounding errors 
	}

	// Another common error is accidentaly doing integer division instead of floating point division e.g:

	int x{ 5 };
	int y{ 3 };

	std::cout << x << " divided by " << y << " is: " << x / y << '\n'; // this will give an in accurate result
	// we could have used static_cast to convert int to double for an accurate result
#endif

	//Another common semantic error are accidental null statements e.g:
	std::cout << "Should we blow up the world again? (y/n): ";
	char c{};
	std::cin >> c;

	if (c == 'y'); // Accidental null statement bc of ;
	blowUpWorld(); // so this will always execute bc not part of if statement
	
	// Another version of that is not using compound statetement e.g:
	if (c == 'y')
		std::cout << "Okay, here we go...\n"; // This is part of if statement
	    
	blowUpWorld(); // Will always execute bc for multiple statement in an if statement compound statements are needed


	
	// Another common semantic error is using assignemnt instead of equality insided of a conditional e.g:

	if (c = 'y') // this should be == not =
	{
		blowUpWorld(); // will always execute bc c = 'y' evaluates to a non zero value so its always true
	}


	// And the last common semantic error is to forget the function call operator when calling a function e.g:

	std::cout << getValue << '\n'; // we forgot () for the function call so instead of 5 this prints either 1 or some other adress value in hex
	// using functions without the function call operator generally returns the functions pointer holding its adress


	return 0;
}