#include <iostream>

int getUserInput()
{
	int input{};
	std::cin >> input;
	return input;
}


int main()
{

	std::cout << "How many bananas did you eat today ? ";
	if (int iBananasEaten{ getUserInput() }; iBananasEaten <= 2)  
	{//looking into cppreference shows us that we can in fact add a optional variable definition (also called init statement) before the condition in an if statement
		std::cout << "Yummy!\n";
	}
	else // if a optional variable definition (also called init statement) is put in the if statement it will also appear on the else so regardless if true or false it will intialize
	{
		std::cout << "Tooo much !\n";
	}

	std::string decree{ "Everyone is equal but some are more equal then others" };
	decree.erase(17); // normally its (17,5)  17 being the index number where it should start and 5 being how many char it should erase but if you dont give it anything other then the index it will just delete everything with the index and after
	std::cout << decree << '\n';


	std::string str{ "I saw a red car yesterday." };

	str.replace(8, 3, "blue"); //8 is the index , 3 is the range and "blue" is the replacement

	std::cout << str << '\n'; // I saw a blue car yesterday.


	return 0;
}