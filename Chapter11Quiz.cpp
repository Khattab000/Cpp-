#include <iostream>
/*
Question 4:

11
2    // compiler normally prefers normal functions with this syntax (foo(s)) but bc its not an exact match the templated function is preferred 
4
2
6
*/



//Question 2 write code :
//step 1
template<typename T>
T add(T x, T y)
{
	return x + y;
}

template <typename T>
T mult(T x, int y)
{
	return x * y;
}


template <typename T,typename U>
auto sub(T x, U y)          // in this case you could have also used the abreviated version without template by just using auto
{
	return x - y;
}


int main()
{
	std::cout << add(2, 3) << '\n';
	std::cout << add(1.2, 3.4) << '\n'; 

	std::cout << mult(2,3) << '\n';
	std::cout << mult(1.2, 3) << '\n';

	std::cout << sub(3,2) << '\n';
	std::cout << sub(3.5, 2) << '\n';
	std::cout << sub(4, 1.5) << '\n';

	return 0;
}