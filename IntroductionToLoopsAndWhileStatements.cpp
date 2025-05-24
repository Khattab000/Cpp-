#include <iostream>


void printUpto(int outer)
{
	int inner{ 1 };
	while (inner <= outer)
	{
		std::cout << inner << ' ';
		++inner;
	}
}

// now we cover while loops
int main()
{
	int count{ 0 };
	while (count <= 100)  // instead of manually printing each number from 0 to 100 we can use a while loop // evaluates until condition is false and if the condition is false from the start it never evaluates in the first place
	{
		std::cout << count << ' ';
		++count; // we need that so it isn't an infinite loop
	}
	std::cout << "done!\n";

	// You can also make intentional infinite loops e.g
	while (true)
	{
		std::cout << "Loop again (y/n)?  ";
		char c{};
		std::cin >> c;

		if (c == 'n')
		{
			break;   // only way to exit a while loop is with a return, break, exit, goto statements or  exception thrown out
		}
	} // use while(true) for intentional infinite loops

	/*
	Also a way to cause unintentional infinite loops is when putting a semicolon after while like while (x > 1);  bc with; it thinks it only has a null statement regardless what is written below it
	this sometimes is used tho on purpose like if you wanna keep calling a function until its false e.g while(keepRunning()); with that we only call the function and run it until it returns false
	*/

	
	// Loop variables are the variables we usually use in a loop to count like i,j or k but also consider giving them more unique names like iii or count to make the code more readable and easier to search out
	// Also important keep Loop variables signed bc of possible overflow e.g while(x >=0) this will resolve in a infinite loop if the loop increments --x bc when we reach the last loop it will go into the negative but bc its unsigned it will overflow and make it positive again
	
	int counter{ 1 };
	while (counter <= 50)
	{
		if (counter < 10)
		{
			std::cout << '0';
		}

		std::cout << counter << ' ';

		if (counter % 10 == 0)
		{
			std::cout << '\n';
		}

		++counter;
	}

	// we can also use nested loops e.g

	int outer{ 1 };
	while (outer <= 5)
	{
		printUpto(outer);   // in this example we have an outer and inner loop first the outer loop executes one and then gets into the inner loop which executes until false and then we get back to outer
		std::cout << '\n';
		++outer;
	}

#if 0
	// the above code can also be written without the function but would look more confusing e.g:
	int outer2{ 1 };
	while (outer2 <= 5)
	{
		int inner2{ 1 };
		while (inner2 <= outer2)
		{
			std::cout << inner2 << ' ';
			++inner2;
		}
		std::cout << '\n';
		++outer2;
	} // does the exact same as above
#endif

	int outer2{ 5 };
	while (outer2 >= 1)
	{
		int inner2{ outer2 };
		while (inner2 >= 1)
		{
			std::cout << inner2-- << ' ';  // -- here so it prints first and then does the --
		}
		std::cout << '\n';
		--outer2;
	}
	char letter{ 'a' };
	while (letter <= 'z')
	{
		std::cout << letter << ' ' << static_cast<int>(letter) << '\n';
		++letter;
	}

	int numba{ 1 };

	while (numba <= 5)
	{
		int index{ 5 };
		while(index >= 1)
		{
			if (index <= numba)
			{
				std::cout << index << ' ';
			}
			else
			{
				std::cout << "  ";
			}
			--index;
		}
		std::cout << '\n';
		++numba;
	}


	return 0;
}