#include <iostream>

int main()
{
	/*
	You can put if Statements inside other if Statements which
	is called nested if Statements, but you need to be careful
	that the else statement is associated with the correct if
	statement. So using blocks {} is a good idea to avoid 
	confusion. e.g
	*/

	std::cout << "Please enter a number: ";
	int x{};
	std::cin >> x;

	if (x >= 0)
	{
		if (x <= 20)
		{
			std::cout << "x is between 0 and 20\n";
		}
		else
		{
			std::cout << "x is greater than 20\n";
		}
	}
	else
	{
		std::cout << "x is negative\n";
	}

	// You can also flatten the above code to prevent nested if statements e.g

	if (x < 0)
	{
		std::cout << "x is negative\n";
	}
	else if (x <= 20)
	{
		std::cout << "x is between 0 and 20\n";
	}
	else
	{
		std::cout << "x is greater than 20\n";
	}

	// Another way to flatten nested if statements is using multiple logcial operators to check multiple conditions e.g

	std::cout << "Enter another number: ";
	int y{};
	std::cin >> y;

	if (x > 0 && y > 0)  // logical AND
	{
		std::cout << "Both numbers are positive\n";
	}
	else if (x > 0 || y > 0)  // logical OR
	{
		std::cout << "One of the numbers are positive\n";
	}
	else
	{
		std::cout << "None of the numbers are positve";
	}


	//Null statements ar expression statements that consist of only a semicolon e.g
	if(x > 10)
	{
		;  // does nothing but ; required
	}

	/*
	Be careful tho if you use it e.g
	if(nuclearCodesActivated()); // you might mistakingly put semi colons here and with that it became a null statement
	   blowUpTheWorld()  // this gets executed every time bc of the mistake bc its not part of the if statement
	*/
	/*
	  Other languages like Python use the keyword pass instead of a semicolon and we can mimic that bc using pass 
	  makes it easier to find places where we put put null statements which mostly are placeholders e.g

	  #define PASS

	  void foo(int x, int y)
	  {
	    if (x > y)
		{
		  PASS;  //bc the PASS gets stripped out by the preprocessor the semicolon is interpreted as a null statement
		}
		else
		{
		  PASS;
		}
	  }

	  int main()
	  {
	    foo(4,7);
		return 0;
	  }
	*/

	/*
	 Lastly a common mistake people do in if statements is using the assignment operator = instead of equality operator == e.g

	 if(x = 0)  // uff we mistakingly used = instead of == so this if statement will always be false bc 0 is boolean for false
	   {
	     std::cout << "x is 0\n";   
	   }
	 else
	   {
	     std::cout << "x is not 0\n";
	   }
	*/

	return 0;
}