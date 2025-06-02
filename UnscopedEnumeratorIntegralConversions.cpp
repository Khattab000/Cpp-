#include <iostream>
#include <cstdint> // for std::int8_t

//Every enumerator converts to an integral value , this depends on the placement of the enumerator in the enumeration e.g
enum Color
{
	black,    // 0
	yellow,   // 1
	purple,   // 2
	blue,     // 3
	white,    // 4
	red,      // 5
	green,    // 6
	orange,   // 7
};

//You can also assign the enumerators a custom integral and the once that you dont define just get an integral that is higher then the integral before it e.g:
enum Animal
{
	cat = -3,
	dog,        // -2
	guinea_pig, // -1
	horse = 5,
	giraffe = 5,// having two enumerators have the same integral value is allowed that just means that both are the same and interchanegable 
	chicken = 6,

};
//But assigning explicit values to your enumerators isnt recommended unless you have a important reason to do so


enum UniverseResult
{
	destroyUniverse,
	saveUniverse,
};


enum Winner
{
	winnerUnknown, // default value (0)
	player1,
	player2,
};


enum Codex:std::int8_t // we use :std::int8_t to make this the underlying type of the enum /this can be useful if you need to specify a smaller type 
{
	beige, 
	grey,
	turqois,
};

int main()
{
	Color shirt{ yellow };  // shirt actually stores integral value 1

	Animal pet{};  // for zero initialization the enumeration is given the value 0 even if there isnt a corresponding enumerator with the value 0
	
	//So bc zero intialization gives the enumeration a value 0 , you should try to make your first enumerator a good default one otherwise it can lead to some issues e.g:
	UniverseResult universe{}; // value 0 so destroyed prob not what we wanted 
	//instead make your first enumerator a invalid or uknown enumerator this also helps in cases where no 0 enumerator exist which leads to semantical error when zero initialized e.g:
	Winner result{}; 
	//And with this you can also check for it even if 0 intialization which you couldnt if there where no 0 values in enumerators e.g:
	if (result == winnerUnknown)
	{
	}

	//Lets see what happens when we try to use std::cout with a enumeration type e.g:
	std::cout << shirt << '\n';  // this prints 1 
	//bc the cout << operator doesnt know how to work with the enumerated type so instead it checks for integral type which the enumerated type implicitly converts too and cout can work with


	//So you míght ask what integral type exactly are enumerators and the answer is its implementation defined but most compilers put make them int but you can also decide yourself what integral type the enumerators should be:
	Codex c{ turqois };
	std::cout << sizeof(c) << '\n'; // prints 1 (for one 1 byte)
	//but only specify the type when rly necessary
	//small reminder bc we made Codex std::int8_t it will print as char not int when we put it in std::cout bc remember std::int8_t is an type allias for char e.g:
	std::cout << c << '\n'; //lmao this prints a smiley 


	//even tho we said that the compiler implicitly converts unscoped enumeration to integer it doesnt apply in the opposite direction so int wont implicitly conert to enum e.g:
#if 0
	Color color{ 1 }; // you would assume that this converts to yellow but no this will lead to a compile error
	shirt = 4;        // this also doesnt work even tho yellow the value of shirt will implicitly convert to int you cant pass it a int to conver to enum  so also compile error
#endif 
	//But there is a way to make it work by using static_cast<>() e.g:
	Color color{ static_cast<Color>(1) }; // explicitly converting works and now color has the value yellow
	shirt = static_cast<Color>(4);        // this works too so now shirt has the value white 
	//so using static_cast<>() is safe as long as its in the range of the underlying type that also applies to values that arent represented as enumerators 
	//but there is an exception the rule which is when you specified the base like we did with the enum Codex but  you can ONLY do brace initialzation with it e.g:
	Codex r{ 7 }; // this is fine bc we specified the base for Codex which is std::int8_t
#if 0
	Codex r2(2);  // compile error only brace initialization
	Codex r3 = 4; // compile error only brace initialization
	r = 4;        // compile error only brace initialization
#endif 


	return 0;
}