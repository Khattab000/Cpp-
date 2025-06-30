#include <iostream>

//In this lesson we talk about the hidden "this" pointer and member function chaining

class Simple
{
	int m_id{};
public:
	Simple(int x)
		:m_id{x}
	{}

	int GetID() const
	{
		return m_id;
	}
	void setID(int x)
	{
		m_id = x;
	}
	void printID() const
	{
		std::cout << this -> m_id << '\n'; // we added "this" just for the lesson showing that this pointer is holding the address of the implicitly passed object and accessed its member data
	}

};


//calling "this" pointer could have an advantage for distinguishing variables of the same name e.g:
struct Something
{
	int data{}; //not using m_ prefix bc its a struct

	void setData(int data)
	{
		this->data = data;  // we need this-> bc both the data member and the parameter had the same name 
	}
	//but if possible avoid calling "this" explicitly and just change the name or give them m_ prefixes
};


//one huge advantage of implicitly calling "this" is returning *this to be able to chain multiple member functions together similar how std::cout works e.g
class Calc
{
	int m_value{};
public:
	
	Calc& add(int value) //normally void but this time we return the "this" pointer by reference so you can chain other member functions after it / you will see why reference  instead of pointer later on
	{
		m_value += value;
		return *this; 
	}

	Calc& sub(int value)
	{
		m_value -= value;
		return *this;
	}

	Calc& mult(int value)
	{
		m_value *= value;
		return *this; //no need to check if its a nullptr before dereferencing bc this will always point to an implicit object
	}

	int getValue()
	{
		return m_value;
	}

	void reset()
	{
		*this = {}; //using the default constructor to create a temporary default object Class and initializing the implicit object with it/ {} is deduced as a temporary Calc object due to the type of *this on the left-hand side
	}

};

int main()
{
	Simple simple{ 1 };
	simple.setID(2);
	simple.printID();
	/*
	So you might wonder how C++ knows that.setId(2) should operate on the object simple and that m_id actually refers 
	to simple.m_id the answer to that is a hidden "this" pointer. Inside every member fucntion/constructor te keyword "this" is a const pointer that holds the address of the current 
	implicitly passed object. Most of the time we dont mention "this" explicitly but we can, lets add it explicitly to the member function. We added "this" to the printID() member 
	function and its still works as intended

	Even tho it looks like simple.setID(2) only has one argument its actually being rewritten bc it actually has two when compiled rewrties as follows:
	Simple::setID(&simple,2);  //&simple being the address of the object that is calling .setID() /and look "simple" now changed to function argument instead of an object prefix
	
	So now this is basically a normal function call but that only one part bc it provides two arguments the definition also needs to change to accommodate the argumetns passed:
	
	// the const after simple*  here makes it a const pointer so it cant change the address where it points too but doesnt mean that the object its pointing too is 
	   const so the object can be modified / we cover static member functions in the future
	static void setID(simple* const this,int x)  
	{
		this -> m_id = x;
	}
	*/

	Calc calc{};
	calc.add(5).sub(3).mult(7); 
	/*
	Here is the reason why we made the member functions return the reference to the *this pointer instead of just the pointer bc if we returned the pointer we would have 
	had to use -> to chain additionaly member functions after calling a member function that returns a pointer but bc its a reference we can use . instead,
	this way it looks tidier and we dont need to switch from . to ->
	*/

	std::cout << calc.getValue() << '\n';
	calc.reset();
	std::cout << calc.getValue() << '\n';

	/*
	With non const member functions "this" is a  const pointer to non const meaning that "this" cant change which object to point too but can modify it but with const 
	member functions "this" becomes a const pointer to const meaning "this" cant change which object to point too and cant modify it either. So bc of that, this is the reason
	why we get a compilation error when calling a non const member function with a const object bc the passed pointer is a const pointer to const but the function is asking for 
	a const pointer to non const so dropping the to const leads to an error bc this cant be done implicitly.


	Btw you might wonder why "this" is a pointer and not a reference and the fact that it could never be a nullptr to begin with ?
	The answer is references didnt exist yet so pointers where chosen but if "this" would have been created nowadays it definetly would have been a pointer

	*/
	return 0;
}