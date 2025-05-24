#include <iostream>
#include <cmath> // for function sqrt()


void printCats(bool skip)
{
	if (skip)
	{
		goto end;  // example for forward jumping
	}

	std::cout << "cats\n";
end:
	; // null statement bc statement label needs to be  associated with a statement
}


// this time we cover goto statements which makes you able to jump to wherever you want in the code if there is a statement label (goto can jump forwards or backwards) e.g
int main()
{
	double x{};

tryAgain:   // similar to case labels we call those statement labels they are used with goto statements so we can chose where to jump
	std::cout << "Enter a non-negative number: ";
	std::cin >> x;

	if (x < 0.0)
	{
		goto tryAgain; // this is a goto statement and it jumps to tryAgain when the condition is met / goto has function scope so goto and the statement labels need to be in the same function
	}

	std::cout << "The square root of " << x << " is " << std::sqrt(x) << '\n';

	printCats(true);
	printCats(false);
#if 0
	goto skip;  // this is illegal bc its not  allowed to jump forward above initializations bc this would skip int x{5}; but jumping backwards above initialization is fine
	int x{ 5 };
skip:
	x += 3;
#endif

	// Conclusion try to avoid goto as much as possible bc most of the time there are cleaner solutions like loops or if statements, here a small example of a good usage of goto if you try to leave a nested loop but not the whole function:

	for (int i = 1; i < 5; ++i)
	{
		for (int j = 1; j < 5; ++j)
		{
			std::cout << i << " * " << j << " is " << i * j << '\n';

			if (i * j % 9 == 0)
			{
				std::cout << "Found product divisible by 9. Ending early\n";
				goto end;
			}
		}
		std::cout << "Incrementing first Factor.\n";
	}
end:
	std::cout << "And we're done.\n";

	return 0;
}
