#include <iostream>

#if 0
// small example for simple algorithm and this algorithm is labeled as stateful bc it retains some information across calls unlike stateless which doesnt and which relies on us giving it information
int plusOne()
{
	static int s_counter{ 3 };  // static so the variable only initializes once and retains its value

	++s_counter;
	return s_counter;
}

// Programs use PRNGs (Pseudo random number generators to generate a sequence of numbers whose properties simulate a sequence of random number (dont use this  below example) e.g:

unsigned int LCG16()
{
	static unsigned int s_value{ 0 };   // this here is called the seed value and depending on that the sequence of numbers will change so if we wanna have diffrent numbers we could for example change that to 7 instead of 0
	s_value = 8253729 * s_value + 2396403;
	return s_value % 32768;

	// We modify the s_value using large constants and internal overflow to make it hard to predict and with that we generate the next number in the sequence 
	// even tho the result seems random it rly isnt and it pretty similar to our plusOne() function so thats why this algorithm isnt rly recommended
}
#endif

// now we make a version were the user is asked to provide a seed and from there the numbers are generated e.g:

static unsigned int g_value{ 0 }; // make it global outside of a function so multiple functions can use it 

void seeding (unsigned int seed)  // with that function we ask the user for a seed
{
	g_value = seed;
}

unsigned int LCG16()
{
	g_value = 8253729 * g_value + 2396403;
	return g_value % 32768;
}

void printTenTimes()
{
	for (int i{ 1 }; i <= 10; ++i)
	{
		std::cout << LCG16() << '\t';
	}
}

int main()
{
#if 0
	std::cout << plusOne() << '\n';
	std::cout << plusOne() << '\n';
	std::cout << plusOne() << '\n';

	for (int i{ 1 }; i <= 100; ++i)
	{
		std::cout << LCG16() << '\t'; // like newline but horizontal instead of vertical
		if (i % 10 == 0)
		{
			std::cout << '\n';
		}
	}
#endif

	std::cout << "Input a positive number as a seed to generate some numbers: ";
	int seed{};
	std::cin >> seed;
	seeding(seed);
	printTenTimes(); // if we provide the same seed number we always get the some outcome



	//There are many different versions of PRNG and each has its ups and downs so chose depending what you need
	/*
	In C++ we can also use the randomization library which we access by #include <random> and there are 6 big PRNG families there to chose from but recommended is only
	mt19937 and mt19937_64 (Mersenne Twister ) which we will cover in the next chapter but the only issue with that is it might be predictable to cover that too you might wanna
	use 3rd Partly libraries recommended are Xoshiro and Wyrand Families for non cryptographic PRNGs and Chacha family for cryptographic non predictable PRNGS
	*/
	return 0;
}
