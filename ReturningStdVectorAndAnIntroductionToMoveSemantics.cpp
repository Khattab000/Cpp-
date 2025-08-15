#include <iostream>
#include <vector>

std::vector<int> generate()
{
	std::vector arr1{ 1,2,3,4,5 };
	return arr1;
}

std::vector<int> doSomething(std::vector<int> v2)
{
	std::vector v3{ v2[0] + v2[0] }; // Step 3 construct value
	return v3;                       // Step 4 return value
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

	The issue is tho that not many types support move semantics, but std::vector and std::string both support it.
	
	So its inexepensive to return  std::vector and std::string by value bc of move semantics but we still recommend to pass
	those types by const reference because passing an lvalue wouldnt work with move semantics bc it would lead to the 
	lvalue being empty and leading to undefined behavior when tried to be accessed.
	Lets look at the whole process step by step :
	*/

	std::vector v1{ 5 }; //Step 1  construct value
	std::cout << doSomething(v1)[0] << '\n'; //Step 2 pass value
	std::cout << v1[0];

	/*
	We cant rly optimize Step 1 and Step 3 but we can optimize Step 2 and 4 lets see how:
	Step 2 we can pass by reference instead of passing by value bc move semantics doesnt apply hereand its expensive to pass
	by value.

	Step 4 Just return by value bc move semantics are a applied in this case ofc even better would ellision (copy being elided)
	but that depends on the compiler and if its being smart. returning a const reference/address is not recommended bc you end 
	up with a dangling reference or pointer.

	So to summarize pass bc const reference and return by value for types that support move semantics.
	*/

	return 0;
}