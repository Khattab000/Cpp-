#include <iostream>

bool isVowel(char x)
{
	switch (x)
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

// Preserving the test might be good to if you wanna retest again later on so you dont need to write the whole test again
// Lets modify the test bc now if we reuse it we might not remember what the right output is supposed to be
int testisVowel()
{
	if (!isVowel('a'))
	{
		return 1;
	}
	if (isVowel('b'))
	{
		return 2;
	}
	return 0;

	// with that if everything is fine it will just return 0 but if either one is broken it will return either 1 or 2 depending which one is broken 
}

int main()
{

	// This is called unit testing we test a small part of a code to make sure it works so this code below is just a temporary code so you delete if you tested it
	std::cout << isVowel('a') << '\n';
	std::cout << isVowel('b') << '\n';

	int result{ testisVowel() };
	if (result != 0)
	{
		std::cout << "testIsVowel() test " << result << " failed\n";
	}
	else
	{
		std::cout << "testisVowel() test " << result << " succeeded\n";
	}
	return 0;
}
// A better way to hi is to use assert which will cause the program to abort with an error message but we will cover that in the future