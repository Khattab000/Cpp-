#include <iostream>
#include <vector>

//On this lesson we learn about std::vector and the unsigned length and subscript problem

//Both the the length type and the subscript type of arrays are both unsigned which can lead to issues if a negative number is inputted leading to undefined behavior or overflow


void foo(unsigned int)
{ }


int main()
{
	int s{ 5 };
#if 0
	unsigned int u{ s }; //compile error: list initialization disallows narrowing conversions (bc signed to unsigned or vice versa cant hold all the values of the opposite)
#endif
	foo(s);              //possible warning: copy initialization allows narowing conversion

	//but if the value is constexpr and the compiler sees that value can be represented in unsigned (or signed) then the conversion isnt considered narrowing 
	constexpr int s2{ 5 };  //now constexpr
	unsigned int u2{ s2 };  //ok: s2 can be converted safely and not narrowing conversion
	foo(s2);                //ok: s2 can be converted safely and not narrowing conversion
	//We will take advantage of this concept of the non narrowing constexpr conversion (constexpr int to constexpr size_t)

	/*
	Most containers have a member typedef/typalias called size_type which is used for the length of the container and its most of the time an alias for std::size_t so
	dont wonder when debugging and for example when using .size() with a std::vector that it says that the type it returns is from the type size_type.

	(When you want to access the size_type member of a class you gotta use the full scope qualifier e.g std::vector<int>::size_type)
	*/

	std::vector<int> prime{ 2,3,5,7,11 };
	std::cout << "length: " << prime.size() << '\n'; // .size() returns lenght as type size_type (alias std::size_t)
	/*
	Keep in mind that for std::string and std::string_view, both .size() and .length() exist — and they do the same thing: they return the number of characters in the string.
	For containers like std::vector or arrays, only .size() exists and it returns the number of elements.

	So:
	- std::string/.string_view: .size() == .length()
	- std::vector/.array: only .size(), which returns element count 
	(std::size() can be used too but for non member functions, for container classes it just calls .size() and this method is mainly preferred when dealing with non decayed
	C-style arrays)

	All of them return counts of elements, not raw bytes (sizeof() for bytes).
	e.g:
	*/

	std::vector<int> dream{ 8,3,4,2 };
	std::cout << dream.size() << std::size(dream) << '\n'; // both return the the lenght of the vector 


	//as we stated earlier the lenght type is unsigned so initializing a signed int with it will most likely lead to compile error so use static_cast<int>() in this case
	std::vector<int> vic{ 7,8,95 };
	int rando{ static_cast<int>(vic.size()) }; // okay bc we used static_cast<>()
	std::cout << "length: " << rando << '\n';



	//There is also another way, we can get the length as a large signed integral value (type std::ptrdiff_t) by using std::ssize()  (btw double s so ssize not size) e.g:
	std::vector<int> drei{ 3,3,3 };
	std::cout << "length: " <<  std::ssize(drei) << '\n'; //returns the length of the vector as a large signed integral value
	//If you want to use the method to store the value of the length there is two main ways
	int yahl{ static_cast<int>(std::ssize(drei)) }; // first way is using static_cast bc int may be smaller then the returned large integral type this way you avoid narrowing conversion warnings/errors
	std::cout << "length: " << yahl << '\n';

	auto yak{ std::ssize(drei) }; //second way use auto to deduce the correct type returned by std::ssize() so you dont need to worry about any conversion
	std::cout << "length: " << yak << '\n';


	//In a prior lesson we introduced the []operator and we also stated that it doesnt do bounds checking 
	std::vector<int> mal{ 7,0,2 };
	std::cout << mal[1]; // this fine bc still inbounds
#if 0
	std::cout << mal[3]; // undefined behavior bc out of bounds 
#endif
	//Btw the index for []operator can be a non const we cover that later on


	//But there is another way to access a certain array element which even does runtime bounds checking and throws an exceptions we use .at() for that e.g:
	std::vector<int> uz{ 8,4,5,7 };
	std::cout << uz.at(2) << '\n'; //this fine bc still inbounds
#if 0
	std::cout << uz.at(4) << '\n'; // throws an exception at runtime and terminates the program bc out of bounds
#endif
	//Btw index for .at() can also be non const

	//[]operator is preferred over .at() even tho .at() is safer its slower then []operator and we can just make sure beforehand to not input any invalid index 


	//just like above with how we can use to constexpr value to avoid narrowing conversion warnings we can use it in the index which normally takes an unsigned std::size_t
	std::vector dried{ 8,9,12,7,33 };
	std::cout << dried[3] << '\n'; //3 is int to std::size_t not narrowing conversion
	constexpr int index{ 3 };      //constexpr signed
	std::cout << dried[index] << '\n'; //this normally might give us an compile warning but it wont due to constexpr /would still work without it tho
	//less of an issue here bc no list initialization is involved its just an example and as we stated earlier for the index we can also use non const e.g:
	
	std::size_t ind{ 3 }; //non constexpr
	std::cout << dried[ind] << '\n'; // no conersion at all needed 

	//but if we use non const signed values we might get warnings due to narrowing conversion (it still works tho) e.g:
	int indra{ 3 }; //non constexpr signed
	std::cout << dried[indra] << '\n'; // okay but possible warning due to implicit narrowing conversion but this is fine bc we expect a non negative value to be used on the index


	//Best way for indexing is just using a std::size_t variable and only using it for indexing (ofc if you need to use a variable)

	/*
	Under the hood std::vector holds its elements in a C-style array knowing this there is also another way to index by using the .data() member function which returns a pointer
	to the underlying C-style array which then can be indexed with the []operator but in this case C-style array can take both unsigned and signed as an index 
	so regardless what you input from those two there isnt any conversion happening (we will cover more of C-style arrays in the future and other indexing challenges) e.g:
	*/
	int cyu{ 3 };                           // non constexpr signed value 
	std::cout << dried.data()[cyu] << '\n'; //okay and no warning bc no sign conversion


	std::vector hello{ 'h','e','l','l','o' };
	std::cout << "The array has " << std::size(hello) << " elements.\n"; 
	std::cout <<   hello[1] << hello.at(1) << '\n';







	return 0;
}