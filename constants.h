#pragma once
// file used with SharingGlobaleConstants.cpp and constants.cpp

/* Way 2
namespace constants   // only the forward declarations
{
	extern const double pi;      // we cant forward declare a constexpr but in this case we use const for the forward declaration and again dont forget extern to make it visible outside of the file
	extern const double avogadro;
	extern const double myGravity;
}
*/

// Way 3

namespace constants
{
	inline constexpr double pi{ 3.14159 };  // put inline infron so the variable can be defined multiple times so no need for a unique copy everytime its used
	inline constexpr double avogadro{ 6.0221413e23 }; // also no need for extern if you use inline on constexpr bc inline has external linkage by default (in this case it wouldnt have needed that anyways bc its in a namespace and those are always global)
	inline constexpr double myGravity{ 9.2 };
}