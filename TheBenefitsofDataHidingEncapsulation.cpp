#include <iostream>
#include <string>
#include <string_view>

//In this lesson we talk about data hiding (encapsulation ) and its benefits 

#if 0
//Another big advantage of encapsulation is when the our class type has a invariant that needs to be sure bc with structs you couldnt rly take care of that but with class you can e.g:
class Employee
{
	std::string m_name{};
	char m_firstInitial{}; //invariant we need to make sure that m_firstInitial is the Initial of m_name 

public:
	void setName(std::string_view sv)
	{
		m_name = sv;
		m_firstInitial = sv.front();  //std::string::front() is a helper function returning the first letter works for std::string and std::string_view
	}
	void printInfo() const
	{
		std::cout << m_name << " has the first initial " << m_firstInitial << '\n';
	}
};
#endif

//another advantage of data hiding is better error detection we will show it with an example where we remove the invariant from the Employee class e.g:
//Another big advantage of encapsulation is when the our class type has a invariant that needs to be sure bc with structs you couldnt rly take care of that but with class you can e.g:
class Employee
{
	std::string m_name{};
	//The invariant existed bc m_name and m_firstInitial where two different variables

public:
	void setName(std::string_view sv)
	{
		m_name = sv;
	}
	char firstInitial() const //const bc its not modifying m_name itself more so make a copy of it but only from the first letter /this way we removed the invariant bc first 
	{
		return m_name.front();
	}
	void printInfo() const
	{
		std::cout << m_name << " has the first initial " << firstInitial() << '\n';
	}


	/*
	but now we got a new invariant being if someone passed an empty string and then we called.front() it would lead to undefined behavior but the good thing about data hiding is
	bc the user doesnt have direct access to m_name we can just put some kind of verification in setName() to make sure that the user cant pass a empty string or what 
	to do in this case like : ignore the request to setName() and return to caller , assert out or throw an exception.
	
	*/
};



class Something
{
#if 0 //if we had a struct only this part would suffice and the user has direct access but it also means if we changed the class all calls to this class are broken then
	int m_value1{};
	int m_value2{};
	int m_value3{};
#endif 

	//we changed the private data member now
	int m_value[3]; // we changed the implementation of the class to an array of 3 //dw we cover arrays later on

public:
	void setValue1(int x)  //we dont need to change the member functions only the function body this way calls to it work as expected and dont need to be all changed
	{
		m_value[0] = x; // changed from m_value1{} to m_value[0] bc its an array now
	}
	int getValue1() const
	{
		return m_value[0]; // changed from m_value1{} to m_value[0] bc its an array now
	}

	//debugging is also easier with encapsulation bc you only need to keep track of the functions in the class and see how they affect the value
};



class Yogurt
{
	std::string m_flavor{ "vanilla" };

public:
	void setFlavor(std::string_view f)
	{
		m_flavor = f;
	}

	const std::string& getFlavor() const
	{
		return m_flavor;
	}

#if 0
	//Worst: member function print() uses direct access to m_flavor even tho  getter exist so there is no need for print() to be a member function and more useful as a standalone function so others can use it too
	void print() const
	{
		std::cout << "The yogurt has the flavor " << m_flavor << '\n';
	}
#endif
#if 0
	//Better bc now print() doesnt have direct access and uses getFlavor() but still not the best bc its a member function
	void print(std::string_view prefix) const
	{
		std::cout << prefix << " " << getFlavor() << '\n';
	}
#endif
};
//The best: non member function print() is not part of the class interface and does not anc cannot access any member fuinction directly and changes to the class doesnt matter to it
void print(const Yogurt& y) //this way we can make different applications of print to customize instead of having to use a member function 
{
	std::cout <<"The yogurt tastes like " << y.getFlavor() << '\n';
}





int main()
{

	std::string_view sv{ "Hello World" };
	std::cout << sv.length() << '\n'; 
	//even tho we dont see the encapsulated class inner structure this is fine as long as we know how to use the interface .length(), thats why we use private and public on classes

	Employee e{};
	e.setName("Tarik");
	e.printInfo(); // prints Tarik and T

	e.setName("Michael");
	e.printInfo(); // prints Michael and M
	//this way we dont give the user to much control and simplify the interface to avoid any mistakes like the invariant not being true


	Something something{};
	something.setValue1(4);
	std::cout << something.getValue1() << '\n';
	//even tho we changed the implementation of the class our program still works bc the functions call still have the same name just the implementation changed 



	/*
	One important bit is that you should prefer making a function a non member function if possible especially if it contains application specific data or logic.

	Here is a small guide to when to use which:
	-Use a member function if you have to bc in some cases C++ requires a function to be a member function
	-Use a member function when the function needs access to private or protected members or data that should not be exposed
	-Use a non member function otherwise especially for functions that dont modify the object 

	We will show some examples with the Yogurt class
	*/

	Yogurt y{};
	y.setFlavor("cherry");
#if 0
	y.print();
#endif
#if 0
	y.print("The yogurt tastes like");
#endif
	print(y);


	/*
	Conclusion: Its recommended putting your public member fist and private members last if sharing your code or working with others bc the others are more interested 
	in the interface.

	As an aside here is the order by the Goodle C++ style guide:
	-Types and type aliases 
	-static constants
	-factory functions
	-Constructors and assignemnt operators 
	-Destructor
	-All other functions (static and non static member functions and friend functions)
	-Data memvers (static and non static)
	*/


	return 0;
}