#include <iostream>
#include <string>
#include <string_view>

// Question 1 Monster

enum MonsterType  // you could also put the enum inside the Monster struct if you dont wanna use it somewhere else 
{
	unknown,
	ogre,
	dragon,
	orc,
	giant_spider,
	slime,
};


struct Monster
{
	MonsterType type{};
	std::string name{};
	int health{};
};

void printMonster(const Monster& mon)
{
	std::cout << "This ";
	
	switch (mon.type) // you should also make this a seperate function and then call it in printMonster e.g: constexpr std::string_view MonsterTypeString(Monster::MonsterType type) /Monster:: if we put the enum of MonsterType in the struct
	{                                                                                                            
	case ogre:
		std::cout << "Ogre ";
		break;
	case dragon:
		std::cout << "Dragon ";
		break;
	case orc:
		std::cout << "Orc ";
		break;
	case giant_spider:
		std::cout << "Giant Spider ";
		break;
	case slime:
		std::cout << "Slime ";
		break;
	default:
		std::cout << "??? ";
		break;
	}
	std::cout << "is named " << mon.name << " and has " << mon.health << " health.\n";

}

template <typename T>
struct Triad
{
	T first{};
	T second{};
	T third{};
};

#if 0 //is using C++17 we need the deduction guide
template <typename T>
Triad(T,T,T) -> Triad<T>;

#endif 

template <typename T>
void printTriad(Triad<T> tri)
{
	std::cout << "[" << tri.first << ", " << tri.second << ", " << tri.third << "]";
}

int main()
{

	Monster torg{ orc,"Torg",1800 };
	Monster johan{.name{"Johan"},.health{25}};
	
	printMonster(torg);
	printMonster(johan);

	Triad t1{ 7,8,9 };
	Triad t2 { 1.2,0.9,6.7 };

	printTriad(t1);
	printTriad(t2);

	return 0;
}