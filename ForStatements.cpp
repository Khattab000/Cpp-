#include <iostream>
#include <cstdint> // for fixed width integers

std::int64_t pow(int base, int exponent)
{
	std::int64_t total{ 1 };

	for (int i{ 0 }; i < exponent; ++i)
	{
		total *= base;
	}
	return total;
}

int sumTo(int value)
{
	int sum{0};
	for (int i{ 1 }; i <= value; ++i)
	{
		sum += i;
	}
	return sum;
}

#if 0
// first version
void fizzbuzz(int max)
{
	for (int i{ 1 }; i <= max; ++i)
	{
		if (i % 3 == 0 && i % 5 == 0)  // check that first  so you dont need to add != 0 to the other one to make sure the other one might be true
		{
			std::cout << "fizzbuzz\n";
		}
		else if (i % 3 == 0)
		{
			std::cout << "fizz\n";
		}
		else if (i % 5 == 0)
		{
			std::cout << "buzz\n";
		}
		
		else
		{
			std::cout << i << '\n';
		}
	}
}
#endif


void fizzbuzz(int max)
{
	for (int i{ 1 }; i <= max; ++i)
	{
		bool printed{ false };

		if (i % 3 == 0)
		{
			std::cout << "fizz";
			printed = true;
		}
		if (i % 5 == 0)
		{
			std::cout << "buzz";
			printed = true;
		}
		if (i % 7 == 0)
		{
			std::cout << "pop";  // we use compound words and dont use else so it checks each if and use printed to change from false to true so the last if knows if a word was printed so it doesnt print
			printed = true;
		}


		if (!printed)
		{
			std::cout << i;
		}

		std::cout << '\n';
	}
}



int main()
{
	for (int i{ 1 }; i <= 10; ++i)  // ofc you can also decrement by using --i or increment by more than one e.g i+=2
	{
		std::cout << i << ' ';
	}
	std::cout << '\n';

	std::cout << pow(7, 20) << '\n';

	// examples and problems for != in for loops e.g
#if 0
	for (int i{ 0 }; i < 10; ++i)
	{
		std::cout << i;
	}

	for (int i{ 0 }; i != 10; ++i)  // basically the same as above but main diffrence tho is that it wont terminate if somehow it jumps above 10 so in some cases i < 10 might be a better choice
	{
		std::cout << i;
	}


	// here we show why != can be problematic you might wanna avoid it :

	for (int i{ 0 }; i < 10; ++i)
	{
		std::cout << i;
		if (i == 9)
		{
			++i;
		}
	}
	for (int i{ 0 }; i != 10; ++i)
	{
		std::cout << i;
		if (i == 9)
		{
			++i;
		}
	}// so with this i!=10 is never false so the loop never terminates so try to avoid != in for loops
#endif

	// A lot of times people do the mistake where the counter is off by one e.g

	for (int i{ 1 }; i < 5; ++i) // the intention was it to print 1 2 3 4 5 so we forgot to use <= instead of <
	{
		std::cout << i << ' ';
	}
	std::cout << '\n';


	// you can also omit certain aspects of an for loop like the init statement or the increment e.g
	int k{ 0 }; // important variables only used in a loop should be only defined in the scope of the loop
	for (; k < 10;) // basically behaves like a while loop
	{
		std::cout << k << ' ';
		++k;
	}
	std::cout << '\n';

	// while(true) == for(;;)  but prefer while(true)

	

	// in some cases you want to use multiple counters which you can do e.g

	for (int j{ 0 }, l{ 9 }; j < 10; ++j, --l)  // one of the few cases where using the comma operator for multiple variables and statements is acceptable
	{
		std::cout << j << ' ' << l << '\n';
	}


	//You can also use nested for loops e.g
	for (char c{ 'a' }; c <= 'e'; ++c)
	{
		std::cout << c;
		for (int o{ 0 }; o < 3; ++o)
		{
			std::cout << o;
		}
		std::cout << '\n';
	}
	// Conclusion prefer for loops when there is an obvious loop variable if not prefer while loops

	//small quiz:

	for (int m{ 0 }; m <= 20; m+=2)
	{
		std::cout << m << ' ';
	}
	std::cout << '\n';

	std::cout << sumTo(5) << '\n';

	fizzbuzz(150);
	return 0;
}