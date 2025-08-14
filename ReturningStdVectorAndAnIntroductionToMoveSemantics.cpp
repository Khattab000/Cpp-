#include <iostream>
#include <vector>

std::vector<int> generate()
{
	std::vector arr1{ 1,2,3,4,5 };
	return arr1;
}



int main()
{
	std::vector arr1{ 1,2,3,4,5 };
	//copies { 1,2,3,4,5 } into arr1
	std::vector arr2{ arr1 };
	//copies arr1 into arr2

	arr1[0] = 6; //we can use bot arr1 and arr2 independently 
	arr2[0] = 7;

	std::cout << arr1[0] << arr2[0] << '\n'; //67

	std::vector arr3{ generate() }; 
	//the return value of generate() dies at the end of the expression
	arr3[0] = 7; // we only have access to arr3 not the return value
	std::cout << arr3[0] << '\n';
	/*
	so using generate() created a temporary that was copied over to
	arr3 and then afterwards got destroyed, but the temporary is going
	to be destroyed anyways and creating a potentially expensive copy
	to just destroy the original is a bit suboptimal thats where move
	semantics come in. The way move works is instead of copying the 
	value from the original instead the ownership of the value is 
	transferred, this process is pretty cheap (bc its
	usually just two to three pointer assignments) 
	and also saves us the cost of destroying the temporary. The rules
	for move semantics are that everything that can be move will be
	moved and everything that cant be moved will be copied.

	So when is move semantic invoked ? only when all of these are true:
	- the type of the object supports move semantic
	- the object is being initialized with or assigned with an rvalue
	  object of the same type
	- the move isnt elided
	*/

	return 0;
}