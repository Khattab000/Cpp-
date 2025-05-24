#include <iostream>

//A reference is an alias for an exisiting object and changes made to the reference also change the object that is reference in this lesson we talk about lvalue references


int main()
{
	/*
	Here is how references look like 
	int         //normal type
	int&        //an lvalue reference to an int object
	double&     //an lvalue reference to an double object
	const int&  //an lvalue reference to an const int object
	*/

	int x{ 5 };     // x is a normal integer variable
	int& ref{ x };  // ref is an lvalue reference variable which is an alias to x /btw you could also write it like this int &ref{x}; but its not recommended

	std::cout << x << '\n';     //prints 5
	std::cout << ref << '\n';   // also prints 5 bc ref is a reference to x and acts as an alias

	x = 6;        // x now has the value 6
	
	std::cout << x <<' '<< ref << '\n'; //prints 6 6 

	ref = 7;   // we can modify x with a non const lvalue reference

	std::cout << x << ' ' << ref << '\n'; //prints 7 7


	/*
	References need to be initialized e.g
	int& Invalidref;  // invalid

	int x{6};
	int& ref{x}; // valid bc reference to int is bound to int variable

	//but be careful bc non const lvalue references can only be bound to modifiable values e.g
	const int c {4};
	int ref2{c}; //invalid we are trying to bind a non const lvalue to an unmodifiable value (const)
	int ref3{0}; //invalid non const lvalue reference cant bind to an rvalue

	//btw lvalue reference to void types arent allowed
	//btw even if the type dont match exactly no conversion happens the difference in types is handled in the binding process
	*/

	/*
	A reference only binds to an object matching its referenced type but if you still try the compiler tries to implicitly convert the objects type
	and bind it to that then but that will lead to an compilation error bc the result of a conversion is an rvalue e.g:

	int x{5};
	int& ref{x};    //okay referenced type int matches type of initializer+

	double d {6.0};
	int& ref2{d};    //invalid converion from double to int narrowing conversion are disallowed for list initialization
	double& ref3{x}; //invalid bc conversion needed so the result of that will be an rvalue and we cant bind non const lvalue reference to an rvalue

	//there are some exceptions that we will talk about later on, on the topic of inheritance
	*/

	//References cant be reseated/changed to reference another object e.g:
	int x2{ 5 };
	int y2{ 9 };

	int& ref2{ x2 };
	ref2 = y2; // this doesnt reseat the reference it just gives x2 the value of y2 but the reference will still just reference x2

	std::cout << x2 << '\n'; // prints 9 now bc value changed
	//btw references have the same scope and duration as normal variables

	/*
	the lifetime of a reference and the lifetime of the referent(the object that is being referenced) are independent so the object
	can be destroyed before the reference and the reference can be destroyed before the object e.g
	*/

	int p{ 5 };
	{
		int& ref5{ p };   //reference to p
		std::cout << ref5 << '\n';
	} // ref5 is destroyed here
	std::cout << p << '\n';  // prints 5
	// so even tho the reference was destroyed before the referent it didnt rly affect the referent
	// but if an referent is destroyed before the reference then the reference is left referencing an object that no longer exists and this will lead to undefined behavior we call that dangling references we will talk more about those in the future
	
	/*
	Reference arent objects so e.g a reference cant reference another reference bc reference need an identifiable object to reference and normally the compiler 
	optimizes the references to switch with their referent so that the reference doesnt allocate any memory for itself , but there are cases 
	where the reference needs some memory after all and there is a solution if you need a reference to be an object or need the reference to be reseated by using 
	std::reference_wrapper (we will cover this in the future)
	*/

	int var{ };
	int& ref7{ var };  //an lvalue reference bound to var 
	int& ref8{ ref7 }; //an lvalue reference bound to var
	/*
	You maybe are tempted to say that this isnt allowed bc we established that a reference cant reference a reference so why is int& ref8{ref7}; allowed ?
	but this isnt correct bc when used in a context of initialization ref1 evaluates to var so this would be just a normal lvalue reference, bc the syntax for 
	reference to reference would be int&& not int& but because C++ doesnt support reference to references this syntax was repurposed we will cover this in a future chapter
	*/

	return 0;
}//p destroyed here