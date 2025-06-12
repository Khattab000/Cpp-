#include <iostream>
#include <string>
#include <utility> // for std::pair 
#include "Paired.h"


#if 0
//In this lesson we talk  about class templates which are similar to function templates e.g:

template <typename T >  // this way we dont need to create multiple functions for the same job for different types 
T max(T x, T y )
{
	return (x > y)? x:y;
}


//The same issues we got with function may occur with structs or aggregate types too e.g:
struct Pair
{
	int first{};
	int second{};
};
//But what if we wanted a version for double too so we can pass that the function maximum

struct Pair
{
	double first{};
	double second{};
}; //compile error bc redifinition of Pair you cant just overload structs

constexpr int maximum(Pair p)
{
	return (p.first > p.second) ? p.first : p.second;
}


constexpr double maximum(Pair p) // compile error bc overloaded function only differs in return type 
{
	return (p.first > p.second) ? p.first : p.second;
}
#endif


//To solve this issue we can use class templates e.g:

template <typename T>  // you see its very similar to the function template
struct Pair
{
	T first{};
	T second{};
}; //now you can use whatever type you want 


#if 0
//and just like function templates you can tell the compiler how certain template cases like int should look like or if you only want certain cases to be in the template e.g:
template <typename T>
struct Pair; // this is a forward declaration of struct pair and we need to  remove the definition above it with #if 0 in this case only the cases we specify below will evaluate

//Explicitly defined Pair<int>
template<> //<> tells the compiler this a template type without template parameter
struct Pair<int>
{
	int first{};
	int second{};
};

//Explicitly defined Pair<double>
template<> //<> tells the compiler this a template type without template parameter
struct Pair<double>
{
	double first{};
	double second{};
};
#endif 

/*
Now to our initial issue and how to use struct templates with functions.
one way is to overload the function BUT it important to specify in the function parameters which  templated Pair struct is used e.g:

constexpr int max(Pair<int> p)
{}

constexpr double max(Pair<double> p)
{}

without the <int> or <double> we would get a compilation error but there is another way which is just using a template function for the struct Pair e.g:
*/

template <typename T>
constexpr T max(Pair<T> x)  // we put the T inside the Pair bc thats is the important type that is also returned
{
	return (x.first > x.second) ? x.first : x.second;
}



//ofc you can also make class templates with non template types e.g:
template <typename T>
struct Foo
{
	int moo{}; // moo will always have the type int regardless of T
	T koo{};   // koo gets the type that T has 
};


//you ofc also can have class templates with different template types e.g:
template<typename T, typename V>
struct Pairing
{
	T first{};
	V second{};
};

#if 0
template<typename T, typename V> //only works with Pairing<T,V> tho
void printPairing(Pairing<T, V> p)  //<T,V> for two different types that could be used for the pairing struct
{
	std::cout << p.first << p.second << '\n';
}
#endif 

//But currently our template functions always only work with one class type lets see how we can make one that works with more then one class type e.g:
struct Point
{
	int first{};
	int second{};
};
//for this to work the other class type  needs the same name for the members in this case first and second so the function can access them properly

template<typename T>
void printPairing(T p)  
{
	std::cout << p.first << p.second << '\n';
}
/*
so now instead of using the passed types of T and V inside of Pairing we just take the whole struct as a parameter this way we can use multiple class types as long as 
the member names that are used  in the function are the same but there is a smth important to notice which can lead to mistakes e.g:

template <typename Pairing> //template parameter with the name Pairing
void printPairing(Pairing p)  //this Pairing refers to the template type not the struct
{
	std::cout << p.first << p.second << '\n';
}

You might think that this only compiles for Pairing structs but it doesnt bc as we stated the template type takes precedence over the struct type thats why stick to 
calling your typenames T , V or U to avoid mistakes like these AND very important bc template types take precedence if you where to use the struct type Pairing in the function 
it will still refer to the template type not the struct so avoid at all cost .

*/

//There is actually a class template called std::pair which is identical to the Pairing class template we created and its recommended to use it lets put in the function template e.g:
template <typename T,typename U>
void print(std::pair<T, U> p)
{
	std::cout << p.first << p.second << '\n'; //the exact same bc std::pair also has members called first and second
}








void foo(); // forward declaration of foo()

int main()
{
#if 0
	std::cout << max(1, 4) << '\n';
	std::cout << max(1.2, 5.6) << '\n';

	std::cout << maximum({ 1,4 }) << '\n';

	std::cout << maximum({ 1.5, 5.6 }) << '\n';
#endif

	Pair<int> p1{ 1,2 }; //instantiates Pair<int> and creates object p1
	// <int> no needed bc it deducts the type but recommended to make sure it has the right type 
	Pair<double> p2{ 1.5,4.6 };  //instantiates Pair<double> and creates object p2
	Pair<double> p3{ 7.8,9.1 };  // creates object p3 bc using the already instantiated Pair<double> when we created p2

	std::cout << p1.first << ' ' << p2.first << ' ' << p3.first << '\n';


	std::cout << max(p1) << ' ' << max(p2) << ' ' << max(p3) << '\n';

	Pair<int> px{ 7,8 };
	std::cout << max<int>(px) << " is larger\n"; // call to max<int> calles specifically not recommended bc not needed compiler can just deduct it 

	Pair<double> px2{ 2.2, 1.5 };
	std::cout << max(px2) << " is larger\n";  //call to max<double> calling without specifiying is recommended


	Pairing<std::string, int> tv{ "hello", 1 }; //<> not needed just to make it cleare what types these are
	printPairing(tv);

	Pairing<int, int> tv2{ 1,1 };
	printPairing(tv2);

	printPairing(Pairing {3.4, 7}); //in this case we need Pairing bc its a templated struct non templated structs wouldnt need the name of the struct here


	Point r{ 1,3 };
	printPairing(r);

	Pairing <double, float> b{ 4.5,7.8f };
	printPairing(b);

	//now printPairing() works with both structs Point and Pairing



	std::pair<int, double> q{ 7,4.4 };
	print(q);

	print(std::pair<int, int> {8, 9});



	Paired<double> o1{ 4.5, 8.9 };
	std::cout << max(o1) << '\n';


	foo();

	return 0;
}