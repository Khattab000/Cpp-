#include <iostream>
#include <limits>  // for std::numeric_limits<int>::lowest()
#include <optional> // for std::optional
#include <functional> // for std::reference_wrapper

/*
In the previous lesson we covered error handling of stuff that the compiler couldnt handle himself like a function that does division where the caller might input 0 as a divider and in those 
cases we either made it return a bool showing if it failed or not or return a value that isnt possible e.g:
*/


double reciprocal(double x)
{
	if (x == 0.0)  // if x is semantically invalid
	{
		return 0.0; //return 0.0 as a sentinel to show that an error occured
	}

	return 1.0 / x;
}

void testReciprocal(double d)
{
	double result{ reciprocal(d) };
	std::cout << "The reciprocal of " << d << " is ";
	if (result != 0.0)
	{
		std::cout << result << '\n';
	}
	else
	{
		std::cout << "undefined\n";
	}
}

/*
This way of error handling works but there might be some issues with it:
First the programmer needs to now the sentinel value of the function to test for it properly and that value can differ from function to function.
Second a different version of the same function may use a different sentinel value.
Third this doesnt work if all sentinel value are valid values to return or used from the function

e.g:
*/

//for this function we cant just return zero even if zero is a sentinel value for y  bc it can be still valid if someone uses 0 for x so the valid return value will be 0 so what now ?
int doIntDivision(int x, int y)
{
	if (y == 0)
	{
		return std::numeric_limits<int>::lowest(); // returns the lowest possible value for the type int returning a very unlikely rare number to show that it failed
	}
	return x / y;
}
/*
But this way also has some downsides :
First every time we call the function we need to test for equality for  the std::numeric_limits<int>::lowest() which is not good.
Second and there is the fact that if the user input std::numeric_limits<int>::lowest() or the value of it what we do then which is very ambiguous.


Ofc we could just not use return to return errors but use exceptions but these have their own problems and might cost much performance which is just overkill.

The best option tho is returning the value and a bool indicating if it succeeded and prior to C++17 you had to do it yourself 

But now we have smth better we call std::optional which we can return:
*/

std::optional<int> doOPTIntDivision(int x, int y) // this function optionally returns an int value so it doesnt have to
{
	if (y == 0)
	{
		return {}; //or return std::nullopt  / basically meaning returning no value indicating it failed
	}
	return x / y;
}




/*
We covered in the past how we could use pass by pointer to have nullptr be an optional value basically making it that the caller doesnt need to pass anything e.g:

void printIDNumber(const int *id = nullptr) //user can pass nothing, an valid object or nullptr basically making the argument optional

//the one downside tho is that if an object is passed it cant be an rvalue but std::optional doesnt have that issue e.g:
*/
void printIDNumber(std::optional<const int> id = std::nullopt) // the default needed to make it possible to input nothing and its only possible wiht pointer and std::optional bc there isnt rly a no value equivalent in other types
{
	if (id)
	{
		std::cout << "Your id number is " << *id << ".\n";
	}
	else
	{
		std::cout << "Your id numer is not known.\n";
	}
}


//Here is the workaround where std:reference_wrapper mimics a reference so we can use it with std::optional and dw we will cover struct in the future:

struct Employee
{
	std::string name{}; // expensive to copy
	int id;
};

void printEmployeeID(std::optional<std::reference_wrapper<Employee>> e = std::nullopt) //in this case the argument wasnt passed it was bound to e avoiding the expensive cost of copying 
{
	if (e)
	{
		std::cout << "Your id is " << e->get().id << ".\n"; //dw we cover that later with structs
	}
	else
	{
		std::cout << "Your id is not known.\n";
	}
}


void printEmployeeIDptr(const Employee* e = nullptr) //the same function but we use pointers instead which is recommended over the workaround and which is much more simpler
{
	if (e)
	{
		std::cout << "Your id is " << e->id << ".\n"; //dw we cover that later with structs and this time we dont need the .get() and also no * dereferencing bc -> dereferences implicitly 
	}
	else
	{
		std::cout << "Your id is not known.\n";
	}
}


//variant to be able to pass rvalues if you wanna use actual reference with overloading so you dont need std::optional
void printEmployeeIDOver()   // we use overload to replace std::optional
{
	std::cout << "Your id is not known\n";
}

void printEmployeeIDOver(const Employee& e) // we avoid the expensive copy with the reference
{
	std::cout << "Your id is " << e.id << ".\n";
}
int main()
{
	testReciprocal(5.0);
	testReciprocal(-4.9);
	testReciprocal(0.0);

	
	std::cout << doIntDivision(1,3) << ' '<< doIntDivision(0, 0) << '\n';

	std::optional<int> result1{ doOPTIntDivision(9,3) };
	if (result1) //if the function returned a value
	{
		std::cout << "Result 1: " << *result1 << '\n'; // get the value through * bc for std::optional we need this
	}
	else
	{
		std::cout << "Result 1: failed\n";
	}
	
	std::optional<int> result2{ doOPTIntDivision(0,0) };
	if (result2) //if the function returned a value
	{
		std::cout << "Result 2: " << *result2 << '\n'; // get the value through * bc for std::optional we need this
	}
	else
	{
		std::cout << "Result 2: failed\n";
	}
	
	//using std::optional is quite easy we can construct one like this:
	std::optional<int> o1{ 5 }; //initialized with a value
	std::optional<int> o2{};  //initialized with no value
	std::optional<int> o3{ std::nullopt }; //initialized with no value

	//and to check if an std::optional has a value we can use two methods
#if 0
	if (o1.has_value())  // we use a helper function returning true or false
		if (o2)              // or we just use implicit conversion to bool which is false with no value and true with a value /btw even if the value it contains is zero it still converts to true bc its holding a value
#endif

	//to get the value from std::optional we use these:
	std::cout << *o1 << '\n';             // we use * to access the value but its gonna have undefined behavior if you pass smth with no value like o2 or o3
#if 0
	std::cout << o2.value() << '\n';      // we use the helper function .value() to get the value but throws an std::bad_optional_access exception if  o2 doesnt have a value (which in this case it doesnt)
#endif
	std::cout << o3.value_or(42) << '\n'; // we use the helpere function .value_or() to get the value and if there isnt a value we use the default instead in this case 42
	
	//you see the syntax for std::optional and pointers are a bit similar especially with * and {} but semantically they are different bc a pointer is just pointing to smth but std::optional actually contains the object





	/*
	Lets talk about the pro and cons of using std::optional:
	Pros:
	-using it documents that the function either returns a value or not
	-we dont need to remember any sentinel value bc we can just return none
	- the syntax is pretty easy

	Cons:
	-we need to make sure that std::optional contains a value before getting the value by dereferencing othewise we get an error (in this case use .value_or() here you can define your own default value)
	-std::optional doesnt give you the option to pass back why the function failed


	So in Conclusion: Try always using std::optional instead of returning sentinel values when your function returns a value or may fails,  unless you  rly need  to pass back the reason it failed.
	(you might wanna look at std::expected for an alternative to give back the reason it failed)
	*/



	//Lets talk about using std::optional as an optional function parameter:
	printIDNumber();  //we dont know the id so we gave it no argument

	int id1{ 1 };
	printIDNumber(id1); //we know the id and passed it 

	printIDNumber(64);  //we can also pass an rvalue unlike with pointers
	/*
	There are two advantages to the approach, documenting that the parameter is optional and passing an rvalue the only problem is when the type is expensive to copy
	bc std::optional doesnt support references so in this case just use pointer to const instead.
	*/


	//But there is a work around to use references with std::wrapper which we will cover in the future e.g:

	printEmployeeID(); //we dont know the id yet

	Employee eddie{ "James",34 }; //bc of struct dw we cover that in chapter 13
	printEmployeeID(eddie); // we know the id now 

	//Now with the pointer variant which is better :
	printEmployeeIDptr(); //we dont know the id
	printEmployeeIDptr(&eddie); // we know the id now  /dont forget & bc we use a pointer now

	//but if you want an option where you even can pass rvalues you can just use overloading e.g:
	printEmployeeIDOver(); //we dont know the id
	printEmployeeIDOver(eddie); // we know the id now
	printEmployeeIDOver({ "Luis", 89 });  // we can even pass rvalues but for struct we need to use {} and put everything in there so its basically one argument


	/*
	Conclusion: Prefer std::optional for optional return types but prefer funtion overloading for optional function parameters when possible otherwise use std::optional for optional arguments
	that are passed by value but favor pointer to const (const ptr*) for expensive types that you dont wanna copy.
	*/



	return 0;
}