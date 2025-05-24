#include <iostream>
#include <type_traits>  //for std::common_type_t


template <typename T, typename U> // 3. We defined an additional template parameter U, so now we can call max(1, 3.4) without errors.
auto max(T x, U y)  // return type changed to auto so the narrowing conversion mentioned below doesnt happen anymore
{
	return x < y ? y : x;   // we do have a conversion bc ?: operator require all types to be the same and tries to find a common type in this case double in the call max(1,3.4) BUT the return type is int bc of T so bc of that narrowing conversion takes place
}


template<typename T,typename U>
auto max2(T x, U y) -> std::common_type_t<T, U>; // returns the common type of T and U with that we can forward declare in this case bc of the trailing type syntax and std::common_type_t<>



// we call that abbreviated function template and its recommended to use it takes much less code then to write a template only disadvantage being you need to use the classic template if you want to make sure that multiple auto types are the same if you dont care tho then its find use auto type parameter
auto max3(auto x, auto y)   // bc we used auto at one of the parameters this function become a function template / btw only one parameter is needed 
{
	return x < y ? y : x;
}
/*
this is the same as the classic template function at the topw with auto return type:

template <typename T, typename U> 
auto max3(T x, U y) 
{
	return x < y ? y : x;
*/



template <typename T>
auto add(T x, T y)  // add two values but need to be  matching type
{
	return x + y;
}

template <typename T,typename U>
auto add(T x, U y)   // add two values with diffrent type /could have also used auto add(auto,auto) without the templates
{
	return x + y;
}

template <typename T,typename U,typename Z>
auto add(T x, U y, Z z)  // add three values with different type //could have also used auto add(auto,auto,auto) without the templates
{
	return x + y;
}

int main()
{
	std::cout << max(1, 2) << '\n';
	std::cout << max(1.2, 1.5) << '\n';
	//but lets consider now you want to input one int and one double:
#if 0
	std::cout << max(1, 3.4) << '\n';  //this will lead to an compiler error 
#endif
	//This fails bc T can only represent a single type and we passed it two types if it was a normal function it would have just converted it but template function cant do that when it uses type deduction  but there are three ways to resolve it
	//1. static_cast<>():
	std::cout << max(static_cast<double>(1), 3.4) << '\n'; // this is fine now and calls max(double,double)

	//2. Give the specified type when calling so it can converts it and doesnt use template type deduction:
	std::cout << max<double>(1, 3.4) << '\n'; // this is fine now and calls max(double,double) /ofc you also could have written and overloaded function for this case

	//3.Rewriting the function template to have like using two template type parameter like T and U with that we are able to use diffrent types if we wanted e.g
	std::cout << max(1, 3.4)<< '\n'; //this is fine now and calls max<int,double>(int, double) and it works with two different types without any issues / in this case return type is int so it prints 3 instead of 3.4 bc of narrowing conversion
	//to solve the issue with the narrowing conversion we are gonna change the return type from T to auto so it does type deduction and finds the best one to fit both so no data loss occurs so now it prints 3.4
	//remember tho if using auto the function needs to be fully defined before it can be used bc it needs to check out the function implementation to determine return type

	//but if we need a template function with auto forward declared then there is a way by using trailing type syntax with auto and std::common_type_t e.g:
	std::cout << max2(2.3, 1) << '\n';


	//Since C++20 there is a new functionality for the auto keyword which is that if you use it on a parameter as a type it automatically converts it  to  template e.g:
	std::cout << max3(2, 4.5) << '\n';


	/*
	Last thing is that template functions also can overload and the way it decides which one to pick is similar to the normal overloaded functions but if multiple matches are found
	then he picks the one with the most restriction (e.g he would pick add<T>(T,T) instead of add<T,U>(T,U) even if both are technically a match)
	but if they all similar restrictive then you get an error due to ambiguous match result e.g
	*/
	std::cout << add(1.2, 3.4) << '\n'; //instantiates and calls add<double>() /in this case it calls add<T>(T,T) even tho add<T,U>(T,U) would be also a match its not as restricted thats why the compiler prefers the first
	std::cout << add(5.6, 7) << '\n';   //instantiates and calls add<double,int>()
	std::cout << add(8, 9, 10) << '\n'; //instantiates and calls add<int,int,int>()




	return 0;
}

template <typename T,typename U>
auto max2(T x, U y) -> std::common_type_t<T, U>
{
	return (x < y )? y : x;
}
