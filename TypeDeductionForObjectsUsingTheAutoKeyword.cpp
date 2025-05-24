#include <iostream>
#include <string>
#include <string_view>


int add(int x, int y)
{
	return x + y;
}

int main()
{
	double d{ 5.0 }; // technically speaking this is redundant bc the initialized value already tells us that its a double so instead we can use auto e.g
	auto r{ 5.0 }; // auto tells the compiler to take the value from the initializer value / so r evaluates to a double
	auto i{ 1 + 2 }; // i evaluates to an int
	auto x{ i }; // x evaluates to an int
	auto sum { add(5,6) }; // evaluates to int bc functions return type is int
	auto c{ 'd'}; // evaluates to char
	auto p(6u); // evaluates to unsigned int
	auto l(4.0f);// evaluates to float

	const auto ca{ 7 }; // evaluates to const int
	constexpr auto ca2{ 8 }; //evaluates to constexpr int


	//Auto cant  be used without and initializer bc otherwise it cant deduce the type so type void is also not permitted to use with auto

	// Auto can be very useful if types become much more complex so basically it makes our job a bit easier by finding out what type a value is


	// one important thing is that auto drops the const lemme explain :

	const int a2{ 8 };
	auto a3{ a2 }; // evaluates to int not const int bc const got dropped 
	//but when both are const it gets reapplied e.g:
	const auto a4{ a2 }; // evaluates to const int even tho the const got dropped first it got reapplied again bc of the const keyword on this variable


	//smth similar to const happens to constexpr e.g
	constexpr double n{ 3.4 }; // it is a constexpr double but the type is still called const double bc constexpr is not part of the type
	auto n2{ n }; // const is dropped so this is just double
	const auto n3{ n }; // const is dropped and reapplied but the constexpr status is lost
	constexpr auto n4{ n }; // const is dropped and reapplied and the constexpr status is also reapplied

	//but if you want to use auto on strings its a bit difficult bc you need to use the suffixes s and sv from std::literals e.g
	using namespace std::literals;

	auto satz{ "Hello World"s }; // evaluates to std::string 
	auto satz2{"Herbert"sv}; // evaluates to std::string_view

	// just somethings i wanted to try out lol
	auto sentence{ "hellooooo party people"s };
	std::cout << sentence << c << '\n';
	std::getline(std::cin >> std::ws, sentence);
	std::cout << sentence << '\n';

	//tbh just avoid using auto with std::string or std::string_view

	/*
	Here are some benefits to using auto e.g
	1. Increases readablity:
	int x{78};
	long long y{54};

	auto x{78};
	auto y{54};

	now it looks much better bc the letters for the type are the exact same

	2. Makes sure all your variables are initialized
	int x; // we forgot to initialize but our compiler doesnt care
	auto x; // we forgot to initialize and the compiler will give us an error

	3. Makes sure we dont do unintneded conversions:
	std::string_view getString(); // this function returns std::string_view

	std::string s1{getString()};  // we accidentally use std::string instead of std::string_view that was an expensive conversion
	auto s2{getString()}; // good this made sure its the same type as the functions return type so no conversion

	*/

	//But here are some downsides to auto:
	auto y{ 5 }; //oops we intended this to be a double and bc we use auto it wont even convert to double and we wouldnt notice that smth is off bc the type is obscured / you can hover over auto and it should tell you the type deduced
	// here another example

	auto v{ 1 };
	auto v2{ 2 };
	std::cout << 1 / 2 << '\n'; // oops we wanted floating point division here

	// and also if the type of an initializer changes it will also change the type of the variable sometimes unexpectadly so e.g
#if 0
	auto sum{ add(5,6) + gravity }; // changes to the initializer may change the variable too like if the return type of ass changes from int to double then sum will also change to double
#endif

	//Conclusion: Type deduction (auto) is generally safe to use and encouraged to increase readability so use it when the type of the object doesnt rly matter but if it matters then its recommended to not use auto and just explicitly typing it


	return 0;
}