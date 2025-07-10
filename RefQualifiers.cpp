#include <iostream>
#include <string>
#include <string_view>

//In this lesson we learn about Ref qualifiers


//We discussed in earlier chapters how calling access functions to return references to data members can be dangerous if the implicit object is an rvalue here a small recap:
class Employee
{
	std::string m_name{};

public:
	Employee(std::string_view name)
		:m_name{ name }
	{}

	
	/*
	Ofc we could just return by value but this would mean making an expensive copy to avoid the issue with rvalues and possible dangling reference and most uses cases are with
	lvalues, but what solution do we have to satisfy both cases so that it returns by value for rvalues and by reference for lvalues ?  The answer is Ref Qualifiers 
	which allows us to overload the member function and handle different cases depending if an lvalue implicit object calls it or an rvalue implicit object, 
	we do that by adding & for lvalue and && for rvalue after the function (also after the const if there is one ) and ofc you change the behavior yourself like chaning 
	the rvalue one by making it return by value e.g:
	*/

#if 0 // the initial version of the function
	const std::string& getName() const
	{
		return m_name;
	}
#endif 
	//lvalue version which returns bc const reference
	const std::string& getName() const &
	{
		return m_name;
	}

	//rvalue version which returns by value
	std::string getName() const &&
	{
		return m_name;
	}


};

Employee createEmployee(std::string_view name)
{
	Employee e{ name };
	return e;
}


int main()
{
#if 0 //before we added ref qualifiers the code works fine now
	//Case 1 okay: used the returned reference to member of  rvalue class object in same expression / still fine butjust like Philip below its returned by value now
	std::cout << createEmployee("Frank").getName() << '\n';

	//Case 2 bad: save returned reference to member of  rvalue class object for use later /after the change Philip would not cause undefined behabvior bc its returned by value to ref
	const std::string& ref{ createEmployee("Philip").getName() }; // references becomes dangling when return value of createEmployee() is destroyed which happens after the expression
	std::cout << ref << '\n'; // undefined behavior / after the change its fine bc returned by value 
#endif

	Employee doe{ "Doe" };
	std::cout << doe.getName() << '\n'; // Doe is an lvalue so this calls const std::string& getName() &  which returns by reference

	std::cout << createEmployee("Lucas").getName() << '\n'; // Lucas is an rvalue so this calss std::string getName() &&   which returns by value

	//This way we can do the performant thing when called by lvalue and the safe thing when called by rvalue

	/*
	Some notes about ref qualifiers:
	- Ref qualified overloads and non ref qualified overloads cant coexist only use the one or the other
	- If only a const lvalue qualified function exists it will accept either lvalue or rvalue implicit objects
	- either ref qualified overload can be deleted with the = delete; keyword preventing any calls to it, like for example deleting the rvalue overload one in the above example 
	  making the lvalue ref qualified overlaod the only one that still can be called. 

	Downsides:
	- Adding a rvalue overload to every getter function that returns a reference adds clutter to the class to solve a problem that is easily avoided by good habits
	- Having a rvalue overload return by value means we have to pay for the cost of the copy even in cases where returning a reference with an rvalue object would have been save
	  to do so like the example above  ( std::cout << createEmployee("Frank").getName() << '\n';)
	- Most C++ developers dont know about this feature and most libraries dont use it either

	Conclusion: Try to avoid Ref qualifiers instead opt for always using the rsult of an access function immediately and not saving returned references for use later 
	            to preven the issues with it called with an rvalue object.
	*/
	

	return 0;
}