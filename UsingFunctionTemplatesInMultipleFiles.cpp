#include <iostream>
#include "addOne.h"  //btw if your wondering if this would break ODR, it doesnt bc normally we only pass down forward declaration but in this case its a full definition BUT types,templates,inline functions and inline variables are exempted of ODR as long as they have identical definition
// and if your wondering the instantiated functions are implicitly inline so they are also exempted from ODR so dw


#if 0 //not needed anymore bc of addOne.h
template <typename T>
T addOne(T x);          // function template forward declaration / with a normal function this would work you wouldnt even need to include the header file but bc its templated it doesnt
// This doesnt work alone with the forward declaration bc addOne<double>(double) and addOne<int>(int) where never instantiated in addOne.cpp if they where it would have worked but thats too fragile

//to fix the issue is to remove addOne.cpp and just put the whole definition in a header file
#endif

void foo(); // forward declaration of the function foo from addOne.cpp to show that addOne() can be used in multiple functions without issue

int main()
{
	std::cout << addOne(1) << '\n';
	std::cout << addOne(2.3) << '\n';
	foo();
	return 0;
}