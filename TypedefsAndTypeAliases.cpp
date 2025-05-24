#include <cstdint> // for fixed width int
#include <iostream>
#include "myTypes.h" //we have some type aliases there
#include <string> // for std::string
#include <vector> // for std::vector
#include <utility> // for std::pair


#if 0
bool hasDuplicate(std::vector<std::pair<std::string, int>> pairlist) // crazy and complex type so we should use type aliases 
{
	//do something
	return true;
}
#endif

using VectPairSI = std::vector < std::pair < std::string, int >>;


bool hasDuplicate(VectPairSI pairlist) // much better
{
	// do something
	return true;
}



//Aliases can also help to clarify e.g
using Testscore = int;

Testscore gradePaper()
{
	Testscore x{ 1 };
	return x;
}// if we used int instead it wouldnt have been clear what exactly is returned but tbh most of the time a comment would be enough


using PrintError = int;
PrintError printData();

int main()
{
	using Distance = double; // defines Distance as an alias for type double / You should use capital letters to name Type Aliases to distinguish from variables
	Distance milesToDestination{ 3.4 }; // defines a variable with the type double bc Distance is an alias to double
	std::cout << milesToDestination << '\n';

	// Type Aliases arent definining a new type its just introduces a new identifier for an already existing types and they can be used interchangeable e.g:

	using Miles = long;
	using Speed = long;

	Miles distance{ 5 }; // type long
	Speed mhz{ 3200 };  // type long

	distance = mhz; // value of a type long assigned to a variable of a type long no error here even if their type aliases had different names

	Mello schrank{ 7 };
	Near wallnuss{ 8 };
	std::cout << schrank << wallnuss << '\n';

	// There is also smth called typedef which was used in C :
	typedef long Miles; // the same as using Miles = long

	// But generally its recommended using type aliases instead bc more convenient and its clearer and less prone for errors

	// Now we come to the reasoning why we and where we should use type aliases its mainly used for platform independent coding e.g:
#ifdef INT_2_BYTES
	using int8_t = char;
	using int16_t = int;
	using int32_t = long;
#else
	using int8_t = char;
	using int16_t = short;
	using int32_t = int;
#endif
	// Normally this should be written outside of main this is just here for studying purposes / this is used bc certain platforms either give int 2 or 1 bytes and depending on this we define which it is to get the correct size for the types

	std::int8_t x{ 97 }; // int8_t usually a typedef for char thats why it will print out a char and not a number
	std::cout << x << '\n';


	// Another use case of type aliases is simplifying complex types e.g: 
	std::vector<std::pair<std::string, int>> pairlist; // crazzzy yeah use type alias for that e.g
	VectPairSI pairlist2; // much better 
	
	// another usage of type aliases is if you wanna change the type of certain things like for students id so instead of changing each and every one of them it easier if you used type aliases from the beginning e.g:
	using StudentId = long; // this was initially using StudenId = short; but we decided to use long now so only changing it here changed it for every instance where we used the alias but be careful it might change certain interactions

	// try to only use type aliases if there is a clear benefit to them and you use them frequently so it adavnces code readability or code maintenance otherwise it does more harm then good like obscurring types and make it more difficult to understand


	return 0;
}