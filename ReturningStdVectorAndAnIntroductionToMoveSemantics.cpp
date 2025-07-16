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

	return 0;
}