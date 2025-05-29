#include <iostream>
#include <algorithm> // for std::swap()

// QUESTION 5


void sort2(int& x, int& y)
{
	if (x < y)
	{
		return;
	}

	std::swap(x, y);
}

/*
Alternatively better version:

void sort2(int& x, int& y)
{
	if (x > y)
	{
		std::swap(x, y);
	}

}
// no need for precondition 

*/

int main()
{
	int x{ 7 };
	int y{ 5 };


	std::cout << x << ' ' << y << '\n'; //prints 7 5

	sort2(x, y); // 
	std::cout << x << ' ' << y << '\n'; //prints 5 7

	sort2(x, y);
	std::cout << x << ' ' << y << '\n'; //prints 5 7
 


	return 0;
}