#include <iostream>

#if 0
int max(int x, int y)
{
	return (x < y) ? y : x;
}

double max(double x, double y)
{
	return (x < y) ? y : x;
}
#endif
/*
Lets say the user want to use some types we didnt specify yet so in this case we need  to create more overloaded functions but then we prob
still didnt cover every type and doing so many overloaded functions might lead to errors and is agains DRY (dont repeat yourself).
But gladly C++ has a solution in this regards its C++ templates which basically is a placeholder we use instead of giving the function the type this way
the compiler can create as mane overloade functions as it needs automatically and we only need to maintain the template function so lets change our max(int) to a template function : 
*/

// use single capital letters for Template type parameters like T , but if it has to be smth specific either let it be a word with capital letter (e.g: Allocator) first or before the first letter a capital T to make it clear that its a template (e.g: TAllocator)
template<typename T> // This tells that we are creating a template with the template parameter T only the subsequent (so only the next function) is a template and can us T everything after isnt
T max(T x, T y)      // template<class T> would also work but we talk about templates with classes later on
{
	return x < y ? y : x;
}

#if 0
T min(T x, T y) // compiler error you need to define a new template with a new template parameter bc the template above only has scope to the function that follows  after the template definition
{
	return x < y ? x : y;
}
#endif



int main()
{
	std::cout << max(1, 4) << '\n';
	std::cout << max(1.5, 4.7) << '\n';
	std::cout << max('A', 'C') << '\n';

	return 0;
}