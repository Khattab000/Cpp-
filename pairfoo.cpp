#include <iostream>
#include "Paired.h"

void foo()
{
	Paired<int> p1{ 1,2 };
	std::cout << max(p1) << '\n';
}