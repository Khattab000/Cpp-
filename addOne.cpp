#include <iostream>
// used with UsingFunctionTemplatesInMultipleFiles.cpp 
#include "addOne.h"
#if 0  // definiton was moved to addOne.h bc template functions need their whole defintion passed and its always preferred to include header files instead of full .cpp files

template<typename T>
T addOne(T x)    // function template definition
{
	return x + 1;
}
#endif 


void  foo()
{
	std::cout << addOne(900) << '\n';
}