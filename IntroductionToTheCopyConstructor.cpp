#include <iostream>

//In this lesson we talk about copy constructor

class Fraction
{
	int m_nominator{ 0 };
	int m_denominator{ 1 };
public:
	Fraction(int nom = 0,int denom = 1)
		:m_nominator{nom}
		,m_denominator{denom}
	{ }
#if 0
	//lets try making our own copy constructor
	Fraction(const Fraction& x) //compiler error if you use (Fraction x)  bc this would call the implicit copy constructor even tho we are defining a copy constructor rn so alway use reference for copy constructors
		:m_nominator{ x.m_nominator }
		, m_denominator{ x.m_nominator }
	{
		std::cout << "custom copy constructor invoked\n"; // this message just here to show that it invoked the custom copy constructor not the implicit one
		//but avoid that bc copy constructors should have no side effect beyond copying
	}
#endif
#if 0
	//If a class doesnt have a copy constructor the compiler implicitly creates one but we can also explicitly call for this exact copy constructor e.g:
	Fraction(const Fraction& x) = default;
#endif
#if 0
	//but we can also make the opposite for example if we dont want a class type to by copyable we can prevent this by using the =delete; keyword e.g:
	Fraction(const Fraction& x) = delete; //now most of the below code wont work bc copy initialization isnt allowed anymore for this class type 
#endif
	//You can also make your copy constructor private to prevent the public from copying bc the existence of copy constructor regardless of private or public disables fallback to the default implicit one

	void print() const
	{
		std::cout << m_nominator << "/" << m_denominator << '\n';
	}
};

void printFraction(Fraction f) // f is passed by value
{
	f.print();
}

Fraction generateFraction(int n, int d)
{
	Fraction f{ n,d };
	return f;
}

int main()
{

	Fraction f{ 5,4 };   // call constructor Fraction(int,int)
	Fraction fcopy{ f }; // this works but what constructor is used here ? The anwer is the copy constructor by C++ and which is implicitly created and is public 
	f.print();
	fcopy.print();

	//The copy constructor is used to initialized an object with an existing object of the same type which creates a new object which should be a copy of the object passed
	//now that we added our own copy constructor Fraction fcopy{ f }; will invoke that instead but that just for learning purposes prefer the implicit copy constructor 
	printFraction(f); // f is copied into the function parameter using copy constructor 

	Fraction f2{ generateFraction(1,2)}; // generateFraction() returns a temporary Fraction using copy constructor
	printFraction(f2); // f2 is copeid into the function parameter using copy constructor
	/*
	btw depending on the the version or compiler you might get less messages about the copy constructor even tho it was used more often this is bc of compiler 
	optimization known as copy elision, we will discuss that in a later chapter 
	*/

	/*
	As an asider there is smth we call the rule of three which is a C++ principle that states that if a class either requires user defined copy constructor,destructor or copy 
	assignment operator then it probably needs all three. This rule was expanded to the rule of 5 which adds the move constructor and move assignment to the rule.
	But we discuss that in more detail in later chapters.
	*/




	return 0;
}