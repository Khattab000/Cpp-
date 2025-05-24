#include <iostream>


int main()
{

	int sum{ 0 };

	for (int count{ 0 }; count < 10; ++count)
	{
		std::cout << "Enter a number to add, or 0 to exit: ";
		int num{};
		std::cin >> num;

		if (num == 0)
		{
			break;
		}
		sum += num;
	}

	std::cout << "The sum of all the numbers you entered is: " << sum << '\n';

	// break also commonly used to get out of an infinite loop e.g

	while (true)
	{
		std::cout << "Enter 0 to exit and any other integer to leave: ";
		int num{};
		std::cin >> num;

		if (num == 0)
		{
			break;
		}
	}

	std::cout << "Yeaahhh we out\n";

	// break can only be used in loops or switch statements
	// main difference of return and break is that break just terminates the loop or the switch statement its used in not the whole function where as return regardless if used in a loop or outside it terminates the whole funtion

	// There is also Continue here is how it works:

	for (int count{ 0 }; count <= 10; ++count)
	{
		if ((count % 4) == 0)
		{
			continue;    // basically continue just ends this current iteration but doesnt end the loop 
		}

		std::cout << count << '\n';
	}
	// this prints all numbers from one to 10 other then the one divisible by 4 
	//be careful tho if using continue with while loops bc of it possibly skipping certain parts of it e.g
#if 0
	int count{ 0 };
	while (count < 10)
	{
		if (count == 5)
		{
			continue;   // with that the loop now is infinite bc when we reach 5 it does the continue and ends this iteration skipping ++count so nothing changes so count will be at 5 forever
		}

		std::cout << count << '\n';
		++count;
	}
#endif


	// many argue if you should even use break and continue and in some cases it rly can help simplify certain programs e.g
#if 0
	int count{ 0 };
	bool keepLooping{ true };
	while (keepLooping)
	{
		std::cout << "Enter 'e' to exit this loop or any other character to continue: ";
		char ch{};
		std::cin >> ch;
		if (ch == 'e')
		{
			keepLooping = false;
		}
		else
		{
			++count;
			std::cout << "We've iterated " << count << " times\n";
		}
	}

	// so instead of using a bool to decide if we should keep looping we can use break e.g

	int count{ 0 };
	while (true)
	{
		std::cout << "Enter 'e' to exit this loop or any other character to continue: ";
		char ch{};
		std::cin >> ch;

		if (ch == 'e')
		{
			break;  // with that we didnt need the else statment and no need for the boolean variable
		}
		++count;
		std::cout << "We've iterated " << count << " times\n";
	}
#endif	


	// now to an example for continue might come handy:

	for (int count{ 0 }; count <= 10; ++count)
	{
		if ((count % 4) != 0)
		{
			std::cout << count << '\n';
		}
	}
	// so instead of that we can use continue e.g:

	for (int count{ 0 }; count <= 10; ++count)
	{
		if ((count % 4) == 0)
		{
			continue;
		}
		std::cout << count << '\n';
	}

	// Conclusion try using break, continue and early return if it simplifies your code
	return 0;
}