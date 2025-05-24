#undef NDEBUG // makes sure that assert is enabled even in the release build not needed tho/ use #define NDEBUG to disable assert instead if you are unsure if the IDE wont do it automatically
#include <iostream> 
#include <cmath> // for std::sqrt
#include <cassert> // for assert()



/*
In most cases you dont want assert in the release version of the program bc at this point your program should be thourougly tested
already and most IDES disable assert by default but just in case you can use 
#define NDEBUG to disable all assert() and #undef NDEBUG to enable all asserts its important to place it before any includes
*/


#if 0
void printDivision(int x, int y)
{
	if (y != 0)
	{
		std::cout << static_cast<double>(x) / y;
	}
	else
	{
		std::cerr << "Error: Could  not divide by zero\n";
	}
}
#endif

// this is called a pre condition where we check the condition first to even consider running otherwise it is bounced back to the user via return
void printDivision(int x, int y)
{
	if (y == 0)
	{
		std::cerr << "Error: Could  not divide by zero\n";
		return;// bounce back to the user so if an error is detected we just bounce it back
	}

	//Doing a bounce pattern decreases nesting and all test cases and handling of errors is upfront
	// We know now that y != 0 so we are good to go
	std::cout << static_cast<double>(x) / y;

	/*
	There is alos postcondition so its a condition that needs to be true after 
	the code executed and the last on is called Invariant is a condition
	that needs to be true while smth executes mostly used in loops
	*/
}


/*
There is tho a shortcut to using conditional statements to detect invalid
parameter along with printing the error and terminating the program its
called Assertion. This is an expression that is true unless there is a bug.
If it evaluates to true nothing happens but if it evaluates to false 
an error message is displayed and the program is terminated by std::abort.
The error message also gives a lot of information helping with debugging
*/




double caculateTimeUntilObjectHitsGround(double initialHeight, double gravity)
{
	assert(gravity > 0.0); // we need positive gravity so it reaches the ground
	//If the assert evaluates to false and calls std::abort you can click on retry to try debugging to examine the issue
	if (initialHeight <= 0.0)
	{
		return 0.0; // the object is on or below the ground
	}

	return std::sqrt((2.0 * initialHeight) / gravity);
}

/*
There is also smth called static_assert(condition, diagnostic message) which is checked in compile time rather then run time
which is good to save some memory  so no run time cost and the include cassert is not needed for it. The condition does have to be a constant
expression bc it evaluates in compile time. And static assert can be placed anywhere in the code file and unlike assert() its 
not deactivated in the release build.
e.g
*/
#if 0
static_assert(sizeof(long) == 8, "long must be 8 bytes"); // Here its a bit diffrents this string literal doesnt need to evaluate to anything unlike in assert() its basically a comment
static_assert(sizeof(double) >= 4, "int must be at least 4 bytes"); // this one is true but the one before is false so you cant even compile
#endif



//Now to the question should you use assert() or error handling :
double getInverse(double x)
{
	/*
	It depends:
	If you wanna detect programming errors in the code which is the programmers responsibility then use assert.
	If you need to make sure smth doesnt happen during the run time of the program use error handling.
	If you need to make sure smth doesnt happen but we want it to fail gracefully if it does then use both 
	*/
	assert(x != 0.0); // we also use both here bc the assert might be removed automatically so we are covered during and after we finished
	if (x == 0.0)
	{
		//smth for error handling like throwing an exception
	}
	return 1.0 / x;
}





int main()
{
#if 0
	std::cout << "Took " << caculateTimeUntilObjectHitsGround(100.0, 9.8); // This will trigger the assert bc the assert will evaluate to false


	//One trick you can use on assert is adding a string literal to make it more descriptive e.g
	assert(found && "Car could not be found in database"); // that works bc a string literal always evaluates to boolean true
	/*
	without the string literal we wouldnt be sure what exactly failed and we would have to look at the function or variable 'found'
	to see where the issue is but with the string literal the assertion output shows found && "Car could not be found in database"
	failes so its pretty clear and remember false && true == false 
	*/

	// You can also use string literals to show that the function fails bc of a feature that will or has to be implemented yet e.g
	assert(moved && "Need to handle case where student was just moved to another classroom");
	// With this helpful assertion message the developer knows how to implement it or what to do next 



#endif

	// Conclusion: Favor static_assert() over assert()

	// ALSO very important if you use assert(), bc it uses std::abort() no other actions like cleanup like closing the file or database will take place so make sure you use assert in ways where no corruption can occur
	return 0;
}