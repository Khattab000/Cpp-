#include <iostream>
#include <string>

std::string& getRef()
{
	static std::string s{ "Meow" };
	return s;
}


int main()
{
	int a{ 5 };
	auto b{ 6 }; //b deduces ad 6 bc of type deduction through auto we covered that in an earlier chapter
	
	const double a1{ 7.8 };  //type const double 
	auto b1{ a1 }; // dont forget the deduction drops the const 

	constexpr double a2{ 7.9 }; //tpye const double (constexpr implicitly applies const9
	auto b2{ a2 };   // const dropped yet again

	//but const can be applied e.g :
	double a3{ 5.5 };
	const auto b3{ a3 }; // type const double

	constexpr double a4{ 5.5 };
	const auto b4{ a4 };     // const dropped first and then const reapplied again type const double
	constexpr auto c4{ a4 }; // const dropped first and then constexpr reapplied again type constexpr double


	//To addition to dropping const auto also drops references e.g:
	auto ref{ getRef() };    // type deduced as std::string and not std::string& so the value is only being copied not referenced so reference was dropped
	auto& ref2 { getRef() };  // reference dropped and the reapplied (just like how we did to const)

	//Btw pointers arent affected auto dropping smth like their pointer type only const and reference are 


	//There are two types of const Top-level const and low-level const



	return 0;
}