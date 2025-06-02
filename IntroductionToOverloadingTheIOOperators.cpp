#include <iostream>
#include <string_view>
#include <optional>
#include <limits>
#include <string>

//In a prior lesson we showed an example to us enumeration with cout and cin and also make it write the name of the value:

enum Color
{
	black,
	red,
	blue,
};


constexpr std::string_view getColorName(Color color)
{
	switch (color)
	{
	case black:
		return "black";
	case red:
		return "red";
	case blue:
		return "blue";
	default:
		return "???";
	}
}



/*
This way works but there is two downsides with that: 
- We need to remember the name of the function created to get the enumerator name
- Add clutter to our output statement by needing to call the function

So lets teach  cout how to work with the enumerated type so we can just do std::cout << shirt :


Remember function overloading ? its basically the same instead we write a function with the the word operator and the operator right beside it, for example operator+ 
as its name and and the parameter with the two operands, where one of them HAS to be a user defined type otherwise we get a compile error.
And set the return type to whatever typer makes sense and with the retunrn statement return the result of the operation so when the compiler encounters this operation it will 
first look if there is any overloaded operators that fit before using the standard. So for std::cout << the operator is << and std::cout is the left operand which is of the 
type std::ostream then the operation happens and then std::cout is returned again with the result and this way we can chain multiple << bc the left operand needs to be 
std::cout to work e.g:
*/


std::ostream& operator<< (std::ostream& out, Color color) // we use references & to avoid copies /std::ostream is the type of std::cout and std::cerr
{
	out << getColorName(color); // with this we taught std::cout how to work with the enumerated type Color by calling the function getColorName() which basically is the logic behind it 
	// the reason we use "out" as a parameter instead of just using std::cout is because in case someone used std::cerr with our enumerated type so it works otherwise it would just do std::cout again even tho std::cerr was used 
	return out; //out is returned to chain more << if neeeded 
	//you  can also make it even shorter by writing return out << getColorName(color);
}

//so we covered output but what about input with std::cin this ofc is also possible e.g:

constexpr std::optional<Color> getColorFromString(std::string_view sv)
{
	if (sv == "black")
	{
		return black;
	}
	if (sv == "red")
	{
		return red;
	}
	if (sv == "blue")
	{
		return blue;
	}
	return {};
}

std::istream& operator>> (std::istream& in, Color& color) //std::istream is the type of std::cin / this time Color& bc we want the >> operator to change the the color that was passed not a copy of it
{ // this time color is an in and out parameter bc the parameter is used in the function and will be changed too
	std::string s{};
	in >> s;  // get input from the user 
	std::optional<Color> match{ getColorFromString(s)};
	if (match)
	{
		color = *match; // assigns match to color we use * derference bc match type is std::optional
		return in; // for chaining multiple >> 
	}
	//if we didnt find a matcht the input must have been invalid
	in.setstate(std::ios_base::failbit); //yeah we gonna cover that in the future this sets input stream to fail stated 
	
	color = {}; //on an extraction failure the >> operator does zero initialization instead so we do that here too

	return in;

}

int main()
{
	//Thats how we did output before
	Color shirt{ black };
	std::cout << "Your shirt is " << getColorName(black) << ".\n";
	//After operation overloading
	Color shirt2{ red };
	std::cout << "Your shirt is " << shirt2 << ".\n";  // with operator overloading we dont need to call the function anymore bc this works

	//That how we did input before
	std::cout << "Chose color for your jeans (black,red or blue): ";
	std::string input{};
	std::cin >> input;
	std::optional<Color> jeans{ getColorFromString(input) }; //dont forget the * dereference when using std::optional

	if (!jeans)
	{
		std::cout << "No jeans color was chosen.\n";
	}
	else
	{
		std::cout << "Your jeans is " << getColorName(*jeans) << ".\n";
	}

	//After operation overloading:
	std::cout << "Chose color for your jeans (black,red or blue): ";
	Color jeans2{};
	std::cin >> jeans2;
	if (std::cin) // if we found a match and it didnt fail
	{
		std::cout << "Your jeans is " << jeans2 << ".\n";
	}
	else
	{
		std::cin.clear(); // reset the input stream to good
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flushes input sitting in the buffer 
		std::cout << "Invalid color chosen.\n";
	}


	return 0;
}