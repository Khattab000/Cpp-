#include <iostream>
#include "Fraction.h"  // we included this to be able to use the Fraction type
/*
In this chapter we will discuss the compound types that can be used to create user/program defined types:
-enumerated types (inclduing scoped and unscoped enumerations
-class types(including structs, classes and unions)

Just like type aliases before a program defined type can be used it needs to be defined and have a name:
*/
#if 0 //we did that to show an example of using your program defined type througout multiple files 
struct Fraction   // we cover structs in the future / this only defines what a Fraction type looks like, it doesnt create one
{
	int numerator{};
	int denominator;
};  //its important to use semicolons ; after the type definition
#endif 
//The naming convention for program defined types are starting with a capital letter and no suffixes 

/*
But what about if you wanna use the type throughout multiple files you might think that forward declaring is enought which isnt quite right,
as we stated earlier before using it the full definition needs to be visible bc the compiler needs to know how much memory to 
allocate for the type, which isnt the case when we use forward declaration.
In the case where we wanna use a program defined type in multiple files we just put in a header file and include that wherever we wanna use BUT if you 
already know that you only gonna use it in one file its recommended to put it in the same file so its a as close as possible to wherever its used.


And bc program defined types cant be forward declared they are exempted of the one definition rule (ODR) 
so they are allowed to be defined in multiple code files so they can be used but there  are two things to look out for tho : 
You can only have one type definition per file (dw header guards make sure that this mostly doesnt happen) and if you use a type definition throughout multiple files 
they need to be identical otherwise we get undefined behavior.

As an aside: Including iostream in multiple files works fine because its type definitions (like std::ostream) 
are allowed to appear in many files as long as they are the same in each one.

(bc of that for normal functions we only include the forward declaration bc they arent exempted from ODR)
*/

/*
The reason why we kept calling it program defined and not just user defined is bc there are actual differences:

Fundamental :       A basic type built into the core of C++ e.g int ,std::nullptr_t
Compountd:          A type defined in terms of other types e.g int* , double&, std::string, Fraction (the type we created)
user defined:       A class type or enumerated type which include thios defined in standard library or implementation e.g: std::string, Fraction (the type we created)
program defined: 	A class type or enumerated type but excludes those defined in standard library or implementation so only our own types that we created e.g: Fraction (the type we created)
*/



int main()
{
	Fraction x{ 4,5 };  //this instantiates and object of the type Fraction named x / still works bc the header file with the full definition of the Fraction type was included here so we can use it


	return 0;
}