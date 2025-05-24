#include <iostream>

int main()
{
	std::cout << "Input 2 numbers:";
	int x{};
	int y{};
	std::cin >> x >> y;
	int selection{};
#if 0
	while (selection < 1 || selection > 4)
	{
		std::cout << "Please make a selection what should happen to the first and second number: \n";
		std::cout << "1) Addition\n";
		std::cout << "2) Subtraction\n";
		std::cout << "3) Multiplication\n";
		std::cout << "4) Division\n";
		std::cin >> selection;
	} // doing that is a bit overcomplicated so we use a do while statement e.g 
#endif

	do
	{
		std::cout << "Please make a selection what should happen to the first and second number: \n";
		std::cout << "1) Addition\n";
		std::cout << "2) Subtraction\n";
		std::cout << "3) Multiplication\n";
		std::cout << "4) Division\n";
		std::cin >> selection;
	} 
	while (selection < 1 || selection > 4);  
	// regardless of the condition the "do" will always evaluates at least once first and after that the condition is checked
	// important note tho if you initialize anything in the do block it will be destroyed before even reaching the condition so keep that in mind 
	// Conclusion favor normal while loops to do while 

	switch (selection)
	{
	case 1:
		std::cout << x + y;
		break;
	case 2:
		std::cout << x - y;
		break;
	case 3:
		std::cout << x * y;
		break;
	case 4:
		std::cout << x / y;
		break;
	}

	return 0;
}