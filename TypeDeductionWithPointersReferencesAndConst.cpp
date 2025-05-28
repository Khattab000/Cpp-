#include <iostream>
#include <string>
#include <string_view>



std::string& getRef()
{
	static std::string s{ "Meow" };
	return s;
}

const std::string& getConstRef()
{
	static std::string s{ "Woof" };
	return s;
}



constexpr std::string_view g_hello{ "Hello" };  // implicitly const

constexpr const std::string_view& getConstexprRef() // function is constexpr but returns a const std::string_view& bc as we explained already  constexpr isnt a type qualifier
{
	return g_hello;
}


std::string* getPtr()  //just like references to make a pointer constexpr or a function returning a pointer you need to use constexpr const instead of just constexpr
{
	static std::string sus{ "Amogus" };
	std::string* susptr{ &sus };
	return susptr;
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


	//There are two types of const Top-level const and low-level const:

	//Top level const apply to an object itself
	const int x{ 4 };  // const applies to x
	int* const ptr{};  // const applies to ptr
	//references dont have a top level constant bc they are implicitly top level const

	//Low Level const on the other hand applies to the object being referenced or pointed too
	const int& refx { x };  // this const applies to the object that is being referenced 
	const int* ptrx{ &x };  // this const applies to the object that is being pointed too
	// A reference to const value is always low level const but a pointer can have top level, low level or both 
	const int* const ptrx2{ &x }; //both low level and top level const

	
	//But important to note to the top and low level const topic is that type deduction (auto) only drops top level const not low level const we will show some examples below.

	auto ref3{ getConstRef() }; //important to note the reference is dropped first and then the const /ref and const dropped type std::string
	/*
	Also important to note if you wonder why the const is dropped even tho the reference has low level const try to visualize it :
	1. the function returns const std::string& the const here is a low level const
	2. auto drops the reference leaving us with const std::string  making the const top level now 
	3. auto drops the const bc its a top level const so we are left with std::string
	*/
	//but of course you can reapply them individually or just at the same time e.g:
	const auto ref4{ getConstRef() }; //ref and const dropped and const reapplied type const std::string
	auto& ref5{ getConstRef() };      //ref dropped and reapplied , const never dropped bc of ref being reapplied and staying a low level const type const std::string&
	const auto& ref6{ getConstRef() };//ref dropped and reapplied , const never dropped bc of ref being reapplied and staying a low level const type const std::string&

	//If you want to const reference reapply both the const and reference even if const isnt necessary sometimes like in case of ref6 and ref5 but it makes it more clear what your intentions are


	//Now you may ask yourself what happens to constexpr references , constexpr is not dropped by auto bc its not part of an expression type qualifier like const is its a compile time qualifier:
	//Quick reminder to constexpr a reference we use constexpr const int& the constexpr applies to the reference and const applies to the reference object
	//but even if we pass constexpr the object getting the value doesnt inherit constexpr

	auto ref7{ getConstexprRef()};               // reference and const dropped
	constexpr auto ref8{ getConstexprRef() };         // reference and const dropped and then constexpr applied implcitly adding const / type constexpr const std::string_view but const redundant here just added it here to clarify 

	auto& ref9{ getConstexprRef() };    // reference dropped and reapplied so const never dropped / type const std::string_view&
	constexpr const auto& ref10{ getConstexprRef() }; //reference dropped and reapplied so const never dropped and then constexpr applied / type constexpr const std::string:view& this time const required tho





	//As we stated earlier type deduction doesnt drop pointers e.g:
	auto ptr1{ getPtr() }; //std::string* pointer isnt dropped
	auto* ptr2{ getPtr() };//still std::string* pointer isnt dropped but we can use * to make it clear that this is a pointer /btw in this case tho pointer is removed and then reapplied bc of the * 
	//The reason of reference being dropped and not pointers is when we use type deduction the type of the object that is reference is deduced but with pointers the type of pointer itself is deduced
	
	auto ptr3{ *getPtr() };  //std::string bc the * dereferenced it /this is fine bc the initializer doesnt need to be a pointer it can be whatever it wants to be
#if 0
	auto ptr4* { *getPtr() };//cant compile /bc we added * the initializer needs to be a pointer
#endif
	//Just like with reference only the top level const is dropped even if you use pointers but we dont need to worry about the low level const becoming a top level one bc pointers arent dropped unlike references:
	
	const auto ptr5{ getPtr() }; //std::string* const 
	auto const ptr6{ getPtr() }; //std::sting* const // in both cases auto const and const auto make it std::string* const / its similar to int const and const int so  the order of the const doesnt matter

	const auto* ptr7{ getPtr() }; //const std::string* // when we use auto* the order of const actually matters anc changes accordingly 
	auto* const ptr8{ getPtr() }; // std::string* const

	//now lets cover some cases where the passed pointer is a const:
	std::string le{};
	const std::string* const ptrle{ &le };

	auto ptr9{ ptrle };          // const std::string*  /top level const was dropped
	auto* ptr10{ ptrle };        // const std::string*

	auto const ptr11{ ptrle };   // const std::string* const /top level const was dropped but const reapplied
	const auto ptr12{ ptrle };   // const std::string* const /top level const was dropped but const reapplied the same bc for auto the const placement doesnt matter in this case

	auto* const ptr13{ ptrle }; // const std::string* const /top level const was dropped but const reapplied
	const auto* ptr14{ ptrle }; // const std::string*  /top level const was dropped but not reapplied bc const order matters here and this const is for low level const which never dropped
#if 0
	const auto const ptr15{ ptrle }; // error bc this tries to reapply the top level const twice in the same expression bc both const on the left and right try to reapply the top level const
#endif
	const auto* const ptr16{ ptrle };// const std::string* const /top level const was dropped but const reapplied


	/*
	Conclusion if you want const pointer, pointer to const or const pointer to const when using auto then reapply the const qualifiers even if not necessary and also try using auto* instead 
	of auto which also makes you intent clearer and gives you more control over const (being able to explicitly reapply both top and low level const) and it makes sure you initialize it with a pointer
	bc otherwise it will throw out an error
	*/


	return 0;
}