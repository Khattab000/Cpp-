#include <iostream>
#include <string>
#include <cassert>

//we covered two ways to pass to a function, pass by value and pass by reference now we will cover pass py address:
void printByValue(std::string s) // the parameter is a copy of str
{
	std::cout << s << '\n';     //any changes here dont affect str merely the copy
}

void printByReference(const std::string& s) // the parameter is a reference of str and binds with it
{
	std::cout << s << '\n';   // any changes here would normally affect str but dw bc this is reference to const so we cant make any changes anyways
}

void printByAddress(const std::string* s) // the parameter is the address of str and points to it 
{
	std::cout << *s << '\n';    // any changes here would normally affect str but dw bc this is pointer to const so we cant make any changes anyways
	//in the printByAddress way we need to use dereferencing * to access the value behind the address 
}

void changeValue(int* ptr) // if you want to prevent changing of values use const int* ptr
{
	*ptr = 6;   // this is fine now bc this is pointer to non const
}

void print(int* ptr)
{
	std::cout << *ptr << '\n';
}

void printNL(const int* ptr) // we changed it to pointer to const int so we can use it with assert
{
#if 0
	if (ptr)   // if ptr is not a nullptr
	{
		std::cout << *ptr << '\n';
	}
#endif 

	assert(ptr); //fail the program in debug mode if a null pointer is passed (since it should never happen this way we document it and it warns you early and stops the programm)


	//there are better way to check for nullptr and handle them so we dont need to check over and over for each action:
	if (!ptr)   // if null ptr then return so we do the test beforehand as a pre condition before we even start with the function
	{
		return; // return to main without dereferencing this way we handled the negative case immediatly
	}
	
	std::cout << *ptr << '\n';
}



void printByValue(int i) 
{
	std::cout << i << '\n'; 
}

void printByReference(const int& i)
{
	std::cout << i << '\n';
}
void printByAddress(const int* i) 
{
	std::cout << *i << '\n';    
}






int main()
{
	std::string str{ "Hallo" };
	printByValue(str);     // makes a copy of str
	printByReference(str); // doesnt make a copy of str just binds with it
	printByAddress(&str);  // doesnt make a copy of str just points to it
	std::string* strptr{ &str };
	printByAddress(strptr); // another way to pass to printByAddress this time we pass our own pointer and it works the exact same as the first call to  the function



	// when we use pass by address and the parameter also is pointer to non const we can then modify the value (avoid const ptr in the parameter tho only use ptr to const) e.g:

	int x{ 8 };
	std::cout << "x = " << x << '\n';
	changeValue(&x); // changes the value of x to 6 bc we passed the address of x
	std::cout << "x = " << x << '\n';
	/*
	So in General: prefer ptr to const parameter to ptr to non const unless you rly wanna change the value. But dont make const ptr parameter unless there is a 
	specific reason to do so.
	*/


	//Null Checking:
	int r{ 4 };
	print(&r);  //this works fine
#if 0
	int* ptrr{};
	print(ptrr); //at first the first call will go through and then the programm will crash bc it tries to dereference a null ptr

	//so we should check first if its a Null poitner before dereferencing:
	int* ptrr{};
	printNL(ptrr); //this version checks first if its a null pointer bc if it is it wont allow it to dereference so the programm doesnt crash but it will halt bc it throws out an assertion
#endif	

	/*
	As you can see the print() and printNL() functions didnt handle nullptr too well so why do we even let the user input it in the first place ?
	Pass by const reference offers us basically the same benefits without the downside of accidentally dereferencing nullptr.
	Pass by const reference also has some advantages which pass by const address dont have:
	- Pass by reference can pass down rvalues , pass by address can
	- The syntax for passing down values or using them is cleaner bc with pass by address you end up having to use * and & pretty often regardless what you do

	Here is an example for an rvalue being passed down:
	*/

	printByValue(5);          //no problem at all just copies the literal
	printByReference(5);      //no problem at all converts the literal to int and creates a temporary copy to bind too but it only works bc the paramter is const int& bc int& wouldnt do the conversion
#if 0
	printByAddress(&5);        //compilation errors literal isnt allowed bc cant take the address of an rvalue
#endif

	//Conclusion: prefer pass by const reference to pass by const address unless you have a specific reasong to use by address.
	//"Pass by reference whe you can. Pass by address when you must"

	return 0;
}