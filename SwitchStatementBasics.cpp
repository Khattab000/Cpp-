#include <iostream>


// To avoid chaining multiple if statements which might be difficult and inefficient you could use switch statements

void printDigitName(int x)
{
	if (x == 0)
	
		std::cout << "zero";
	
	else if (x == 1)
	
		std::cout << "one";
	
	else if (x == 2)
	
		std::cout << "two";
	
	else if (x == 3)
	
		std::cout << "three";
	
	else
	
		std::cout << "Unknown";
	

} // small reminder terinaries also exist as a if statement replacement like return x==0 ? 5 : 7
// to much work and the number passed will be evaluated multiple times depending what was picked which is inefficient so use switch statements instead e.g

void printDigitNameSwitch(int x)
{
	switch (x)
	{
	case 1: // case condition should be the same type or at least convertable to the given variable
	
		std::cout << "One";
		return;
	
	case 2:
	
		std::cout << "Two"; // depending what input or number given it jumps directly to the case without evaluating the cases before or after
		return;
	
	case 3:
	
		std::cout << "Three";
		return;
	
	default: // is optional but recommended
	
		std::cout << "Unkown";
		return;
	
	}
	// if none of the cases match and no default is given then the switch statement is just skipped
	std::cout << "\nHi\n"; // this will never execute bc each case has a return we will solve that by using break
} // The condition in a switch statement needs to be an integral type for the reason of trying to be as optimized as possible

void printDigitNameBreak(int x)
{
	switch (x)
	{
	case 1:
	
		std::cout << "one";
		break; // unlike return this doesnt end the whole function just the switch statement itself
	
	case 2:
	
		std::cout << "two";
		break;
	
	default:
	
		std::cout << "Unkown";
		break;
	
	}
	std::cout << "\nNow you see me\n";
	//unlike with return where you couldnt see this statement now you can with break
}   // its always recommended to use break in a swtich statement or a return statement depending what you want to do

// You could also use curly braces {} for each case but if you do keep in mind that what is written in the case has limited scope then
int main()
{
	printDigitName(2);
	std::cout << '\n';

	printDigitNameSwitch(5);
	std::cout << '\n';

	printDigitNameBreak(2);
	std::cout << '\n';
	return 0;
}
/*
Conclusion: use switch statements if you check for equality with a enumarated integral type
but if checking for bool or to be more flexible like seeing whats
bigger or smaller or what range or multiple conditions at once then use
if-else statement
*/