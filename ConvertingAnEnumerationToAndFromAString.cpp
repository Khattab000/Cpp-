#include <iostream>
#include <string_view>
#include <optional>
#include <string>



enum Color
{
	black,  // 0
	red,    // 1
	blue,   // 2
};

constexpr std::string_view returnColor(Color color) //constexpr so we can use it in an constant expression and enums are constexpr too
{
	switch(color)
	{
	case black:
		return "black";
	case red:
		return "red";
	case blue:
		return "blue";
	default:
		return "unknown";
	}
	//reminder its fine to use std::string_view with C style literal in a function bc C style literaly stay until the end of the program so the C style literal that is viewed still exist after the function call
	
}

enum Pet
{
	whale,
	lion,
	monkey, 
	jellyfish,
};

constexpr std::string_view getPetName (Pet pet)
{
	switch (pet)
	{
	case whale:
		return "whale";
	case lion:
		return "lion";
	case monkey:
		return "monkey";
	case jellyfish:
		return "jellyfish";
	default:
		return "???";
	}
}

constexpr std::optional<Pet> getPetByString(std::string_view sv)  //std::string_view parameter to not make a copy for std::string 
{
	//if statements bc swithc doesnt work with std::string
	if (sv == "whale")
	{
		return whale;
	}
	if (sv == "lion")
	{
		return lion;
	}
	if (sv == "monkey")
	{
		return monkey;
	}
	if (sv == "jellyfish")
	{
		return jellyfish;
	}
	return{}; // bc we use std::optional we can return {} which basically means no value
}

int main()
{

	std::cout << red << '\n';   // this prints 1 even tho we want it  to print the name of the value so how do we do that ?
	//one way to do this is writing a function that returns the name of the value like with a switch statements e.g:
	Color shirt{ black };
	std::cout << "My shirt color is " << returnColor(black) << ".\n";
	std::cout << "My shirt color is " << returnColor(red) << ".\n";
	std::cout << "My shirt color is " << returnColor(static_cast<Color>(8)) << ".\n";
	//There are two better way tho first is teaching std::cout how to print enumerations and using arrays we cover both in later chapters 

	//so what happens when we want to use enumerators with std::cin e.g:
	Pet myPet{monkey};
#if 0
	std::cin >> myPet; // compile error std::cin doesnt know how to input the enumeration Pet
#endif
	//But we can do smth similar to std::cout where we create a switch function for it e.g:
	std::cout << "Input a pet (0 = whale, 1 = lion, 2 = monkey, 3 = jellyfish): ";
	int input{};
	std::cin >> input;
	if (input < 0 || input > 3)
	{
		std::cout << "You input a invalid number for a pet.\n";
	}
	else
	{
		Pet pet(static_cast<Pet>(input));
		std::cout << "Your pet is a " << getPetName(pet) << ".\n";
	}
	// a bit of an awkward solution but we will cover better ones in the future

	/*
	The above solution isnt quite what we wanted what if we want the user to input a string instead of inputting a number but this is connected to some challenges 
	bc we cant use std::string or std::string_view with switch statements only integral types and enums so we need to use if statments instead, and another issue 
	is what to do if its an invalid string ofc we can add an enumerator for invalid/error but the better choice is using std::optional e.g:
	*/ 
	std::cout << "Input your pet (whale, lion, monkey or jellyfish): ";
	std::string s {}; // we use std::string bc std::string_view doesnt work with std::cin >> 
	std::cin >> s;
	std::optional<Pet> pet2 { getPetByString(s) };
	if (!pet2)
	{
		std::cout << "Invalid pet was passed.\n";
	}
	else
	{
		std::cout << "Your pet is a " << getPetName(*pet2) << ".\n"; // dont forget if there is a value from std::optional<> then we need to use the dereference * operator to get it
	}
	//just like the input variant there is a better option by teaching std::cin to interact with enums we will cover that in a future chapter 


	return 0;
}