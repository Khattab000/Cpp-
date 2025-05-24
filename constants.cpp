#include <iostream>
// #include "constants.h"

// file used with SharingGlobaleConstants.cpp and constants.h

namespace constants
{
	extern constexpr double pi{ 3.14159 };  // put extern infront of constexpr to make the linkage external
	extern constexpr double avogadro{ 6.0221413e23 };
	extern constexpr double myGravity{9.2};
}
