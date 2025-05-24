#include <iostream>
#include "constantsQuiz7.h"
#if 0
// Question #1 Fix the following program
int main()
{
	std::cout << "Enter a positve number: ";
	int num{};
	std::cin >> num;

	if (num < 0)
	{
		std::cout << "Negative number entered. Making positive.\n";
		num = -num;
	}

	std::cout << "You entered: " << num;
	return 0;
}
#endif

#if 0
// Question #2 Write constant.h
int main()
{
	std::cout << "How many students are in your class? ";
	int students{};
	std::cin >> students;

	if (students > Constants::maxClassSize)
	{
		std::cout << "There are too many students in this class";
	}
	else
	{
		std::cout << "This class isn't too large";
	}

	return 0;
}
#endif

// Question #3 Write function int accumulate(int x)
int accumulate(int x)
{
	static int y{0}; // could work without 0 but you rather put 0 to make sure that its initialized with it
	y += x;
	return y;
}

int main()
{
	std::cout << accumulate(4) << '\n'; // prints 4
	std::cout << accumulate(3) << '\n'; // prints 7
	std::cout << accumulate(2) << '\n'; // prints 9
	std::cout << accumulate(1) << '\n'; // prints 10

	return 0;
}