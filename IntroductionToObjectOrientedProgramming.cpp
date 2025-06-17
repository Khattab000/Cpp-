#include <iostream>
#include <string_view>

/*
So far we mostly used procedual programming which is where variables and functions are seperate and we need to combine them to do certain stuff which leads to code looking like this:
eat(you,apple) so here we have the function eat and we pass you and apple to make it work.
But this isnt rly reflecting our reality in a proper way where object have properties and functionalities and thats why we use object oriented programming also called OOP which leads
to code looking like this you.eat(apple) so the object you has a helper function eat() that it can call which takes some food variable making it more clear who is doing what
and being more faithful to our reality. Lezs compare the two ways e.g:
*/

//Procedual Programming 
enum AnimalType
{
	cat,
	dog,
	bird,
	snake,
};

constexpr std::string_view animalName(const AnimalType& an)
{
	switch (an)
	{
	case cat:
		return "cat";
		break;
	case dog:
		return "dog";
		break;
	case bird:
		return "bird";
		break;
	case snake:
		return "snake";
		break;
	default:
		return "???";
		break;
	}
}


constexpr int animalLegs(const AnimalType& an)
{
	switch (an)
	{
	case dog:
	case cat:
		return 4;
		break;
	case bird:
		return 2;
		break;
	case snake:
	default:
		return 0;
	}
}
//but lets say we wanted to add a new animal like monkey in this case we would need to change quite a lot and risk breaking parts so lets see Object oriented programming:
struct Cat
{
	std::string_view name { "cat" };
	int numLegs{ 4 };
};

struct Dog
{
	std::string_view name{ "dog" };
	int numLegs{ 4 };
};

struct Bird
{
	std::string_view name{ "bird" };
	int numLegs{ 2 };
};

struct Snake
{
	std::string_view name{ "snake" };
	int numLegs{ 0 };
};
/*
this way we can easily add another animal without breaking anything but as you see it can be a bit repetitive and for this you might wanna consider making a 
common Animal struct and with  OOP you can give the differen animals unique attributes which only apply to one animal we will show that in a later chapter.
OOP helps a lot making your code be able to evolve especially when working with others through features like inheritance, abstraction,encapsulation and polymorhphism
*/



int main()
{
	constexpr AnimalType birdley{ snake };
	std::cout << "Your animal is a " << animalName(birdley) << " and has " << animalLegs(birdley) << " legs.\n";

	constexpr Snake animal{};
	std::cout << "Your animal is a " << animal.name << " and has " << animal.numLegs << " legs.\n";


	return 0;
}