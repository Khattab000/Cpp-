#include <iostream>
#include <string>

//On this lesson we learn about containers and arrays



/*
Lets say you have 30 different test scores from students , how would you save all of them ? You could ofc make 30 different variables or put them all in struct to at least 
have an easier time passing it but lets say you wanna calculate the average, you would still need to access each and everyone individually and type them all out which can be prone
to errors so there has to be an easier way to store and work on many elements at once, thats where containers come in , just like a bag of cereal you wouldnt store each individual
element of a cereal in different compartments right ? Instead we put them all in one container that holds all the elements, one container we already kept using is the 
std::string type which is a container of multiple characters (char) :
*/
int main()
{
	std::string alex{ "Alex" }; // alex is a container for each letter of the word Alex
	std::cout << alex << '\n'; // output our string as a sequence of characters
	/*
	But unlike in structs the individual elemens dont have a name in a container which is good for storing huge amounts of elements bc we 
	dont have to give each a unique name , but there are ways to access each individual element bc each container gives us a method to do so but we cover those in a later lesson
	*/


	/*
	The number of elements in container is called length and we showed in an earlier lesson that we can use the.length() 
	member function to tell us what the length of a std::string is :
	*/
	std::cout << alex << " has " << alex.length() << " letters in the name.\n"; // alex.length() returns 4 

	//dont confuse lenght with size we use length for amounts of elements in container and size for the amount of storage required in an object (in byte)

	/*
	The main things you can do with a container is:
	-create one and store elements in them
	-remove or insert elements
	-access elements
	-get the number of elements 

	but there are many other containers that either have additional operations or variations of the above and finding which one suits the
	task best can be helpful in regards of optimizing your code and increasing its maintainability, we will cover those in the future.
	*/

	/*
	The type of elements in an container in C++ are all the same and can be set by the user itself but its mostly used in class templates so the user can provide the desired type
	argument, this way its very flexible and we dont have the need to create a new container for each type. We will show examples of these in the future.
	*/

	/*
	In C++, the standard containers are part of the Containers library, but not every type that behaves like a container is officially considered one.

	For example, C-style arrays and std::string are not considered standard containers. Even std::vector<bool> is often treated as a special case because
	it doesn't behave like a typical container.

	To be a standard container in C++, a type must be a class (often a class template) that meets specific requirements defined by the standard. 
	Examples of true container classes include std::vector and std::array.

	Other containers like std::deque, std::list, std::set, and std::map are also part of the Containers library and are used in more specialized cases.
	*/

	/*
	Btw an array is a container data type that stores a sequence of values contiguously which means each element is placed in an adjacent memory location with no gaps.
	There are three primary types of arrays: C-Style arrays, std::vector container class and std::array container class.
	We cover each of them in the future but we mostly use std::vector and std::array bc C-Style array are pretty dangerous and are mostly replaced by std::array.
	*/

	return 0;
}