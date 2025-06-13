#include <iostream>
#include <utility>  // for std::pair

//in this lesson we talk about class template argument deduction

//replace the U with T and remove typename U if you want all types to be the same 
template <typename T = int,typename U = int> //we can also give the template types default typing in case they arent initialized
struct Pair
{
	T first{};   // you can also give first or second a default value in case they arent initialized
	U second{};
};


//that is a deduction guide for our class template in case we use the code in C++17 
template <typename T,typename U> //replace the U with T and remove typename U if you want all types to be the same 
Pair(T, U) -> Pair<T, U>;
//basically this tells the compiler that Pair objects initialized with arugments of type T and U should deduce to Pair<T,U>
//but this isnt rly needed bc C++20 does it automatically so no need for the guide



//but there are cases where class template argument deduction doesnt work first case when initializing a non statirc member e.g:
struct Foo
{
	std::pair<int, int> first{ 1,6 }; // this works fine
#if 0
	std::pair second{ 1,5 };    // doesnt work for non static member initialization all templated arguments need to be explicitly specified
#endif
};
// another case where CTAD doesnt work is for function parameters e.g:
#if 0
void print(std::pair p) // compile error CTAD cant be used here bc its template argument deduction not template parameter deduction
{
	std::cout << p.first << ' ' << p.second << '\n';
}
#endif
//in the functions case just use function template e.g:
template <typename T, typename U>
void print(std::pair<T, U> p)
{
	std::cout << p.first << ' ' << p.second << '\n';
}

int main()
{
	std::pair<int, double> p1{ 7,8.9 };
	std::pair p2{ 8,4.5 }; //<int,double> not needed bc of (CTAD) type deduction but only works if <> is not used  //doesnt need deduction guide even in C++17

#if 0
	std::pair<> p3{ 9,8 };      //error to few arguments both arguments not deduced
	std::pair<int> p4{ 9,8.2 }; //error to few arguments second argument not deduced 
#endif

	std::pair p5{ 5.6f,8.9f };  // we can also use f and u to make it deduce that its a float or that its unsigned
	std::pair p6{ 5u,9u };


	Pair<int, int> p7{ 9,8 };
	Pair p8{ 7,8 }; // this works but in C++17 it wouldnt work bc deduction didnt work for class templates yet but there is a workaround for it by giving the compiler a deduction guide
	//with the deduction guide this also works now in C++17

	Pair<int, double> p9{ 8,9.5 }; // explicitly specify Pair<int,double>
	Pair p10{ 1,3 }; //( CTAD) argument deduction used to instantiate Pair<int,int>
	Pair p11;        // bc no arguments default is used so Pair<int,int>


	print(p5);

	return 0;
}