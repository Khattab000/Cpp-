#include <iostream>


// now we talk about different ways of error handeling and its diffrent ways to do that


//First Way is Handling the error inside the function
void printIntDivision(int x, int y)
{
	// Here we do basically nothing its just a silent failure where if the use uses 0 then the programm doesnt do anything
	if (y != 0)
	{
		std::cout << x / y;
	}
}

void printIntDivision2(int x, int y)
{
	// In this case we tell the user what the problem is but here we ignore the problem and for functions where a return value is expected that might be not viable

	if (y != 0)
	{
		std::cout << x / y;
	}

	else
	{
		std::cout << "Error: Could not divide by zero\n";
	}
}

// We can also change the return type to return either true or false so the user can see if everything went fine through the return type e.g:
bool printIntDivisionBool(int x, int y)
{
	if (y == 0)
	{
		std::cout << "Error: could not divide by zero\n";
		return false;
	}
	std::cout << x / y;
	return true;
}

//well now we talk about error handling for functions that return normal values e.g:

constexpr double error_no_reciprocal{ 0.0 }; // we use 0.0 bc for the function its used in this value is impossible to get
// this is called a sentinel value and this only works if the function isnt able to naturally produce the value
double reciprocal(double x)
{
	if (x == 0.0)
	{
		return error_no_reciprocal;
	}
	return 1.0 / x;
}




// Now we talk about fatal errors in these cases you just want to terminate and return a non zero return but sometimes thats not possible or just too hard to achieve in these cases we use std::exit() e.g:

double doIntDivisionExit(int x, int y)
{
	if (y == 0)
	{
		std::cout << "Error: Could not divide by zero\n";
		std::exit(1); // exits with code 1 instead of 0 in error case
	}
	return x / y;
}


int main()
{
	int x{};
	std::cin >> x;
	

	std::cout << doIntDivisionExit(2, x) << '\n';

	/*
	In Conclusion Error handling is important but there is a better was called exception which we will cover in the future.

	Now we also mention if you should use std::cout or std::cerr/log files for error handling:
	- Use std::cout for all user facing text
	- For interactive programs use std::cout for normal facing error messages like "Your input is invalid"
	  but use std::cerr or logfiles for status or diagnostic informations that might be helpful for diagnosis issues but probably isnt interesting for normal users
	  like technical warning and errors (failed to connect to a service)
	- For a non interactive program (tool, service) use std::cerr for error output
	  only (could not open file x) makes it possible to be displayed separately from normal output
	- For any application type that are transactional in nature (e.g interactive web browser)
	  use logfiles to produce a transactionla log of events that can be reviewed 
	  later
	
	*/


	return 0;