#include <iostream>
//this file is used with InternalLinkage.cpp
//this file is also used for ExternalLinkage.cpp

[[maybe_unused]] constexpr int g_x{ 2 }; // this internal g_x is only accessible within a.cpp so its fine that we called it g_x even if there is another g_x already in another file 
// only visible in this file 


// functions default to external linkage so we need to use static to make it internal
[[maybe_unused]] static int add(int x, int y)  // now this function cant be used outside of this file regardless even with a forward declaration in another file
{
	return x + y;
}


void sayHi()  // This function has external Linkage by default and can be seen by other files via forward declaration 
{
	std::cout << "Hi\n";
}

int g_j{ 1 }; // extern keyword only needed in forward declaration 
extern const int g_l{ 0 }; // extern keyword is needed in forward declaration and definition here bc its const