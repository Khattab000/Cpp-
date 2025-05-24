#include <iostream>

int foo(int x, int y)
{
	int z{ y };
	if (x > y)
	{
		z = x;
	}
	return z;
}

bool isLowerVowel(char c)
{
	switch (c)
	{
	case 'a':
	case 'e':
	case 'i':
	case 'o':
	case 'u':
		return true;
	default:
		return false;

	}
}

void compare(int x, int y)
{
	if (x > y)
	{
		std::cout << x << " is bigger than " << y << '\n';
	}
	else if (x < y)
	{
		std::cout << x << " is smaller than " << y << '\n';
	}
	else
	{
		std::cout << x << " is equal to " << y << '\n';
	}
}

void spam(int timesToPrint)
{
	for (int i{ 0 }; i < timesToPrint; ++i)
	{
		std::cout << "Spam! ";
	}
}

int main()
{

	// Statement Coverage is the term used to talk about how much percent of the function is tested by the test e.g
	foo(1, 0); // this covers 100 percent of the function bc every statement is being executed with this test

	foo(0, 1); // even tho its covered 100 percent it only covered 50 percent branch coverage, branch coverage being in this case the if statement being false thats why we do the second test


	isLowerVowel('a');
	isLowerVowel('b'); // with those two we got full branch coverage

	compare(1, 0);
	compare(0, 1);
	compare(0, 0); // 3 tests needed for full branch coverage

	// Its always recommended to aim for 100 percent branch coverage in your code 


	spam(0);
	spam(1);
	spam(2); // This is called loop coverage to test a loop we always check for 0 , 1 and 2 iterations if those work we know it works for every other number too
	return 0;
}