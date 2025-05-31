#include <iostream>
#include <bitset>


#if 0
//In this lesson we talk about enumerations lets say your program needs to track the colors of certain things:

using Color = int;

constexpr Color red{ 1 };
constexpr Color blue{ 2 };
constexpr Color yellow{ 3 };

#endif


//here is an example for an unscoped enumeration

enum Color 
{
	red,  //btw enumerators are explicitly constexpr
	blue,
	yellow, //for the data types of the enumeration types we use , not ; 
	
	//so the type color only can be initialized with those three enumerators red, blue or yellow

};  //just like struct we need ; for the definition

enum Pet
{
	dog,
	cat,
	weasel,
};


//Enumerated types are mostly used when we have small set of related constants that only need to hold one of certain values at a time like weekday , cardinal directions or deck of cared e.g:
enum Day
{
	monday,
	tuesday,
	wednesday,
	thursday,
	friday,
	saturday,
	sunday,
};

enum Direction
{
	north,
	east,
	south,
	west,
};

enum CardSuits
{
	clubs,
	diamonds,
	heart,
	spades

};

#if 0
//Traditionally certain functions returned small negative numbers to indicated different failures but these are magic numbers but using enum we can be more descriptive e.g:

enum FileReadResult
{
	readResultSuccess,
	readResultErrorFileOpen,
	readResultErrorFileRead,
	readResultErrorFileParse,
};

FileReadResult readFileContents()
{
	if (!openFile())
	{
		return readResultErrorFileOpen;
	}
	if (!readFile)
	{
		return readResultErrorFileRead;
	}
	if (!parseFile())
	{
		return readResultErrorFileParse
	}

	return readResultSuccess;

	//this way we know exactly what failed instead of reyling on magic numbers
}
#endif 

//another usage could be in games so basically anything that is a small set of related objects e.g:

enum Item
{
	sword,
	shield,
	gun,
};


#if 0
//enumerated types are also very useful as function parameters when making a choice between two or more options: 
enum SortOrder
{
	alphabetical,
	alphabeticalReverse,
	numerical,
};


void sortData(SortOrder order)
{
	switch (order)
	{
	case alphabetical:
		// sort alphabetical
		break;
	case alphabeticalReverse:
		// sort alphabeticalReverse
		break;
	case numerical:
		// sort numerical
		break;
	}
}
#endif


//btw its fine to copy enums bc they are cheap to copy and we also can use them define a collection of related bit flag positions to use for std::bitset e.g:
namespace Flags
{
	enum State
	{
		isHungry,
		isSad,
		isMad,
		isHappy,
		isLaughing,
		isAsleep,
		isDead,
		isCrying,
		// 8 for 8 bits
	};
}


//Lets talk about the scope of unscoped enumerations:
enum Feelings // this enum is defined into the gloabal namespace
{
	happy,  // we call this unscoped enumeration bc the enumerators have the same scope as the enumeration definition itself so also global
	sad,
	mad,
};
//But putting all that into global can lead to naming collisions e.g:
#if 0
enum Words
{
	hello,
	garden,
	sad,  //naming collision so compilation error bc sad, defined already in enum Feelings
};
#endif
//ofc you can changed the names a bit for example wiht a prefix like words_sad but there is a better option to avoid naming collisions by putting usncoped enums in namespaces e.g:
namespace Words
{
	enum Words
	{
		hello,
		garden,
		sad, // no naming collisions this time bc sad is inside the the namespace Words
	};
}

namespace Monster
{
	enum MonsterType
	{
		orc,
		goblin,
		troll,
		ogre,
		skeleton,
	};
}




int main()
{
#if 0
	/*
	this approach works but lets say someone inputs 8 instead of the color names it would still be valid even if semantically wrong and we cant enforce it that way and while debugging
	we only see the integer not the name itself so that is confusing too
	*/
	Color appleColor{ red };
	Color shirtColor{ yellow };
#endif

	/*
	Now thats where enumerations comes in which makes it possible to define our own custom  types where we could define the set of named values associated with that type so you are forced 
	to use one of these otherwise it will result in an error.

	There are two types of enumerations, unscoped which we will cover now and scoped which we will cover in a later chapter. 
	And bc enumerations are program defined types they need to be fully defined before being able to be used so forward declaration isnt enough here an example of an unscoped enum:
	*/

	Color apple{ red }; //unlike the example above red isnt an int and Color isnt an allias for int either so you cant initialize with another literal int 
	Color shirt{ yellow };
#if 0
	Color apple{ white }; // error white isnt an enumerator of Color
	Color hat{ 0 };       // error 2 isnt a enumerator of Color
#endif

	//Naming convention for enum should be use a capital first letter for the enumeration type and lowercase letters for the enumerators 


	//enumerated types are distinct unlike typedefs and type aliases and also keep in mind for two different enumerated types that you cant use the enumerators for one type to the other e.g:
#if 0
	Color socks{ weasel }; // doesnt work bc weasel isnt an enumerator for color
	Pet pet{ red };        // vice versa
#endif 

#if 0
	if (readFileContents() == readResultSuccess) // easier to understand instead of testing for some integer
	{
		//do smth
	}
	else
	{
		//print error messages
	}
#endif


	Item holding{ gun };


	std::bitset<8> me{};
	me.set(Flags::isHappy);
	me.set(Flags::isLaughing);
	std::cout << std::boolalpha;
	std::cout << "I am happy? " << me.test(Flags::isHappy) << '\n';
	std::cout << "I am laughing? " << me.test(Flags::isLaughing) << '\n';
	// if your wondering why this works bc std::bitset normally expect an integral to be used to indicate which bit but we will cover that in the next chapter 



	Feelings you { mad };


	//As we talked about scopes, unscoped enums also provide a named scope region for the enumerators meaning you can call them like if we call things in namespaces e.g:
	you = Feelings::happy; //Feelings:: which refers to the enum is not required tho meaning not recommended so use me = happy; instead


	//here is us using the namespace Words to avoid naming collision
	Words::Words wort{ Words::sad }; //Words:: in both cases is referring to the namespace not the enum

	/*
	So in conclusion to the scope topic prefer putting unscoped enumerations inside named scope region (namespaces) to avoid naming collisions or if its only used in a certain function to put it 
	inside the function.
	We will also cover in the future other options like scoped enums defining its own scope or putting enums inside classes.
	*/


	//We can use the == and != operators to compare enumerators e.g:
	Color pants{ yellow };
	if (pants == blue)
	{
		std::cout << "Your pants are blue.\n";
	}
	else
	{
		std::cout << "They aint blue chief.\n";
	}


	Monster::MonsterType Jeff{ Monster::troll };  //depending on warning level you might need [[maybe_unused]] bc its an unused variable just a side note

	return 0;
}