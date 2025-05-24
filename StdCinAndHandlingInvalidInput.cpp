#include <iostream>
#include <limits> // for std::numeric_limits
#include <cstdlib> // for std::numeric_limits


// This function basically handles case 2
void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//instead of std::cin.ignore(100,'\n') which only clears 100 extra input until the '\n' but we use the one that clears every extra input and we put it in a function for ease of use
}


// Now we got a special case where if the user inputs an EOF these are specific to each OS for example on Windows ctrl + Z this might lead to some problems for example the next input not being read or the input before that being flushed here how to fix it e.g:
bool clearFailedExtraction()
{
	// this replaces the if(std::cin.fail()) we used in another functions bc this now also included EOF
	if (!std::cin)
	{
		if (std::cin.eof()) // If the user entered an  EOF
		{
			std::exit(0); // Shut down the program with exit code 0 bc we want to shut down the program if someone uses an EOF bc thats how its mostly intended
		}
		std::cin.clear();
		ignoreLine();
		return true;
	}
	return false;
	// This and the if(std::cin.fail()) also handles case 4 where the user overflows the numeric value 
}



// We should also consider handling extra input so instead of ignoring it sometimes its smarter to address them e.g:
bool hasUnextractedInput()
{
	/*
	std::cin.eof() returns true if the last input reached the end of the input stream
	std::cin.peek() only looks at the the the next character without extraction it
	*/
	return !std::cin.eof() && std::cin.peek() != '\n';
	//returns true if std::cin has unextracted input on the current line false otherwise
}



/*
The program below takes an input and we should handle each case if the user
decides to input smth invalid.

Case 1: Input extraction succeeds but its meaningless for the program e.g 'k' for the mathematical operation char
Case 2: Input extraction succeeds but the user inputs additional stuff e.g "*q hello" for the mathematical operation char
Case 3: Input extraction fails using 'q' for the numeric input
Case 4: Input extraction succeeds but the user overflows numeric value

We should cover each of these cases to make our program robust
*/


//Now to the final product part of the function is above below are the functions we used before which we modify now a bit 


double getDouble2()
{
	while (true)
	{
		std::cout << "Enter a decimal number: ";
		double x{};
		std::cin >> x;
		if (clearFailedExtraction()) // no need for !std::cin bc the function clearFailedExtraction() already checks for that
		{
			std::cout << "Oops that input was invalid please try again\n";
			continue;
		}
		if (hasUnextractedInput())
		{
			ignoreLine(); 
			continue;  
		}
		
		return x;

	}


}


char getOperator()
{
	//In here we handled case 1
	while (true)
	{
		std::cout << "Enter one of the following: +, -, *, or /: ";
		char op{};
		std::cin >> op;
		if (!clearFailedExtraction())
		{
			ignoreLine(); // we put that here bc the ignore line inside clearFailedExtraction is only called when the extraction fails not succeeds and this if statement is for succeeded extraction
		}

		switch (op)
		{
		case '+':
		case '-':
		case '*':
		case '/':
			return op;
		default: // response to failed extraction is handled here 
			std::cout << "invalid input please try again\n";
		}
	}
}



void printResult(double x, char operation, double y)
{
	std::cout << x << ' ' << operation << ' ' << y << " is ";
	switch (operation)
	{
	case '+':
		std::cout << x + y << '\n';
		return;
	case'-':
		std::cout << x - y << '\n';
		return;
	case'*':
		std::cout << x * y << '\n';
		return;
	case'/':
	{
		if (y == 0.0)
		{
			break;
		}
		std::cout << x / y << '\n';
		return;
	}
	}
	std::cout << "???\n"; // being robust means to even handle unexpected parameters as well even tho getOperator() makes sure its valid
}





#if 0



// Here another version of getDouble() but instead of ignoring extra input we address it
double getDouble2()
{
	while (true)
	{
		std::cout << "Enter a decimal number: ";
		double x{};
		std::cin >> x;

		/*
		This if(std::cin.fail) is for Case 3 checking if its a 
		invalid input this checks if the std::cin failed and went to 
		failure mode where it ignores all future input and in this case 
		puts you in a loop.
		If std::cin.fail() is true we put turn it back from
		failure mode with std::cin.clear() and remove the bad input from
		the buffer with ignoreLine();
		*/
		if (std::cin.fail()) // You could also write !std::cin is basically the same as std::cin.fail()
		{
			std::cin.clear();
			ignoreLine();
			continue;
		}
		if (hasUnextractedInput())   
		{
			ignoreLine(); // removes extraneous input
			continue;  // goes back to the top of the loop
		}
		/*
		instead of the two if statements here you also can be less strict if you dont mind extra junk after the input and ignoring it silently so instead you could do this inside of the while loop:

		std::cout << "Enter a decimal number: ";
		double x{};
		std::cin >> x;
		bool successfulInput{std::cin}; // is true if if input was successful
		std::cin.clear(); // in case it failed but dont worry doesnt do anything if it went through
		ignoreLine(); // removes extra input in the buffer

		if(successfulInput) // if not true we go back from the beginning
		   {
		     return x;
		   }

		*/
		return x;
	
	}

	
}



double getDouble()
{
	std::cout << "Enter a decimal number: ";
	double x{};
	std::cin >> x;

	ignoreLine(); // to handle case 2 so only one input is allowed and nothing after that is put in the buffer
	return x;
}

char getOperator()
{
	//In here we handled case 1
	while (true)
	{
		std::cout << "Enter one of the following: +, -, *, or /: ";
		char op{};
		std::cin >> op;
		if (std::cin.fail())
		{
			std::cin.clear();
			ignoreLine();
			continue;
		}

		if (hasUnextractedInput())
		{
			ignoreLine(); // removes extraneous input
			continue;  // goes back to the top of the loop
		}
		switch (op)
		{
			case '+':
			case '-':
			case '*':
			case '/':
				return op;
			default:
				std::cout << "invalid input please try again\n";
		}
	}
}

void printResult(double x, char operation, double y)
{
	std::cout << x << ' ' << operation << ' ' << y << " is ";
	switch (operation)
	{
	case '+':
		std::cout << x + y << '\n';
		return;
	case'-':
		std::cout << x - y << '\n';
		return;
	case'*':
		std::cout << x * y << '\n';
		return;
	case'/':
		std::cout << x / y << '\n';
		return;
	}
}

#endif

int main()
{
	double x{ getDouble2() };
	char operation{ getOperator() };
	double y{ getDouble2() };

	while (operation == '/' && y == 0.0)
	{
		std::cout << "The denominator cant be zero during division. Try again.\n";
		y = getDouble2();
	}

	printResult(x, operation, y);

	return 0;
}