#include <iostream>

//in this lesson we discuss Template aliases which are similar to type aliases

template <typename T>
struct Pair
{
	T first;
	T second;
};

#if 0
template <typename T>
void print(const Pair<T>& p)  // const reference to not copy the value /dont forget CTAD deduction doesnt work for function parameters so <T> required
{
	std::cout << p.first << ' ' << p.second << '\n';
}
#endif

//now to how to create a template alias important tho just like every other template , template aliases need to be defined in the global csope e.g:
template <typename T>
using Coord = Pair<T>;

#if 1 //you can write this instead of const Point<T>& p both are the same bc Coord is an alias for Point so they are the same but you can only have one function not both otherwise error bc redefined
template <typename T>
void print(const Coord<T>& p)  // const reference to not copy the value /and again bc CTAD doesnt work in function parameters we still need <T> so no alias deduction in function parameters
{
	std::cout << p.first << ' ' << p.second << '\n';
}
#endif

int main()
{
	using Point = Pair<int>;  //created a normal type alias /<int> required tho bc this is just a normal type alias and this can be defined locally or globally ofc
	Point p1{ 1,2 };
	print(p1);




	Coord p2{ 7.8,9.7 }; // in C++20 we could use alias type deduction so this is fine in the cases where CTAD also works
	print(p2);

	Coord<int> p3 {2, 3}; // pre C++20 we need to explicitly specify all template arguments
	print(p3);


	return 0;
}