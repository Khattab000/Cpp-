#include <iostream>
#include <utility>      //for std::to_underlying()
#include <type_traits>  //for std::underlying_type_t
#include <string_view>

enum class Animals
{
	chicken,  // 0
	ostrich,  // 1
	eagle,    // 2
	cow,      // 3
	pelican,  // 4
	parrot,   // 5 
	dove,     // 6
	raven,    // 7
	crow,     // 8

	maxAnimals,
};

//converts enum to underlying type this prevents implicit conversions to integral but makes easier when we request an explicit conversion to integral
template <typename T>
constexpr auto operator+(T a) noexcept // we will cover noexcept later but basically just tells the compiler that no exceptions will be thrown this helps with optimization
{
	return static_cast<std::underlying_type_t<T>>(a);
}
//this template function takes any type as a parameter and auto then deduces the return type we then return the underlying type of the enum that was passed when the unary +operator is used


//Also since C++20 we got a new keyword being ' using enum ' which imports all of the enumerators in the enum to the current scope e.g:
enum class Drink
{
	water,
	soda,
};

constexpr std::string_view getDrinkName(Drink d)
{
	using enum Drink;  //enumerators where imported in the scope of the function / small reminder using is also used for type alliases for example using game = int;
	switch (d)
	{
	case water:   //no need for Drink:: bc we imported the enumerators of the unscoped enum
		return "water";
	case soda:
		return "soda";
	default:
		return "no drink";
	}
}



enum class AnimalFarm
{
	chicken = 1,
	sheep = 2,
	goat = 4,
	cat = 6,
	duck = 3,
	horse = 8,
};


constexpr std::string_view getAnimalFarmName(AnimalFarm a)
{
	using enum AnimalFarm;
	switch (a)
	{
	case chicken:
		return "chicken";
	case sheep:
		return "sheep";
	case goat:
		return "goat";
	case cat:
		return "cat";
	case duck:
		return "duck";
	case horse:
		return "horse";
	default:
		return "not an animal from this farm";
	}
}


void printNumberOfLegs(AnimalFarm a)
{
	using enum AnimalFarm;
	int i{ static_cast<int>(a) };
	i %= 2;
	std::cout << "A " << getAnimalFarmName(a) << " has ";
	switch (i)
	{
	case 1:
		std::cout << 2;
		break;
	case 0:
		std::cout << 4;
		break;
	default:
		std::cout << "???";
		break;
	}
	std::cout << " legs.\n";
}


//here is a better version of printNumberOfLegs()
#if 0
void printNumberOfLegs(Animal animal)
{
	std::cout << "A " << getAnimalName(animal) << " has ";

	// If C++20 capable, could use `using enum Animal` here to reduce Animal prefix redundancy
	switch (animal)
	{
	case Animal::chicken:
	case Animal::duck:
		std::cout << 2;
		break;

	case Animal::pig:
	case Animal::goat:
	case Animal::cat:
	case Animal::dog:
		std::cout << 4;
		break;

	default:
		std::cout << "???";
		break;
	}

	std::cout << " legs.\n";
}

int main()
{
	printNumberOfLegs(Animal::cat);
	printNumberOfLegs(Animal::chicken);

	return 0;
}
#endif 

int main()
{
#if 0
	//Although unscoped enums are distinct types they are not type safe which can cause some issues:

	enum Color
	{
		red,
		blue,
	};

	enum Fruit
	{
		banana,
		apple,
	};

	Color color{ red };
	Fruit fruit{ banana };

	if (color == fruit)  
	{
		/*
		You would expect it to be false but no this will evaluate to true bc both red and banana convert to  the literal 0 bc the operator first checks if he knows 
		how to do the operation which he doesnt so then he just converts them to int to make the comparions possible 
		*/
		std::cout << "color and fruit are equal\n"; // this will be executed 
	}
	else
	{
		std::cout << "color and fruit are NOT equal\n";
	}
#endif
	/*
	So with that issue and other problems like namespace issues and naming conflicts we need a better solution that where scoped enumeration comes in,
	the main difference to unscoped enumeration is that first the enumerators dont implicitly convert to integers and they are only place in the scope region of the 
	enumeration and not the scope of where the enumeration is defined and to make a scoped enumeration we use the keyword enum class e.g:
	*/

	enum class Color //just like enum you can specify a base if you want e.g enum class Color : std::int8_t  
	{
		red,
		blue,
	};

	enum class Fruit
	{
		banana,
		apple,
	};

	Color color{ Color::red }; //for enum class we need to use Color::red bc red isnt in the scope of where the enumeration is defined its only inside the enumeration
	Fruit fruit{ Fruit::banana };
#if 0
	if (color == fruit) //bc enumerators from enum class wont implicitly convert to int this will lead to a compile error bc it doesnt know how to compare to different enum types
	{
		std::cout << "color and fruit are the same\n";
	}
	else
	{
		std::cout << "color and fruit are NOT the same\n";
	}


	std::cout << red << '\n';   // this doesnt compile bc just like we said its in the scope of the enumeration so we need Color:: before it 
	std::cout << Color::red << '\n'; //this would compile BUT we need to teach std::cout<< how to interact with the enumeration first bc this wont implicitly convert to int so compiler error

#endif

	if (color == Color::red) //comparing enumerators of the same enum type is fine 
	{
		std::cout << "Your color is red.\n";
	}
	else if(color == Color::blue)
	{
		std::cout << "Your color is blue.\n";
	}

	/*
	But there are cases where it might be useful to convert a enum class enumerator to an integral value which you can do with static_cast<int>() bc explicitly converting
	enum class is allowed´, but better then static_cast is std::to_underlying() which converts the enumerator to the underlying type making sure it the correct type of the 
	enumerator avoiding potential issues on different platforms e.g:
	*/
	Color shirt{ Color::blue };
#if 0
	std::cout << shirt << '\n';  //wont work bc there is no implicit conversion to int bc enum class wont allow it 
#endif	
	std::cout << static_cast<int>(shirt) << '\n';   //this explicit conversion to int allowed for blue  / print 1
	std::cout << std::to_underlying(shirt) << '\n'; // preferred bc it converts blue to the underlying type making sure its the correct type  / print 1

	//the opposite is also possible :
	std::cout << "Chose a color (red = 0, blue = 1): ";
	int input{};
	std::cin >> input;

	Color jeans{ static_cast<Color>(input) };  //static_cast redundadn here 

	//but for initialization and input you can also just initialize enum classes with literals without any static_cast or any base specification required its redundand here e.g:
	Color dress{ input }; // this works 
	Color shoes{ 1 };     // also works

	/*
	So favor scoper enum to unscoped unless you have a reason to do so you still see it being used a lot in cases where we want the implicit conversion
	and dont mind the namespace issues which saves us to always write the scope specifier e.g Color:: or using static_cast over and over again
	*/

	std::cout << +Animals::raven << '\n'; //convert Animals::raven to an integer with the unary operator + / print 7


	Drink drink{ Drink::water };

	std::cout << "I will have a " << getDrinkName(drink) << ".\n";


	printNumberOfLegs(AnimalFarm::chicken);
	printNumberOfLegs(AnimalFarm::goat);
	printNumberOfLegs(AnimalFarm::cat);
	printNumberOfLegs(AnimalFarm::duck);

	return 0;
}