#include <iostream>
#include <cmath>  //for std::sin and std::cos

namespace mathe
{
	constexpr double pi{ 3.14159265358979323846 };
}

//In this lesson we talk about in and out parameters "in parameters" are just the classic parameters that we always used usually passed by value or const reference:


void print(int i)  // i is a in parameter just taking in an argument
{
	std::cout << i << '\n';
}

void print(const std::string& s)  // s is a in parameter 
{
	std::cout << s << '\n';
}

//Out parameters are usually non const references or pointer to non const  and their main purpose is to modify the variable its referencing/pointing at in case a return statement isnt sufficient:

void getSinCos(double degrees, double& sinOut, double& cosOut) //sinOut and cosOut are "out parameters" bc they can be modified and theis sole purpose is modifying the passed arguments
{
	double radians = degrees * mathe::pi / 180.0;
	sinOut = std::sin(radians); 
	cosOut = std::cos(radians);
}




int getByValue()
{
	return 5;
}

void getByReference(int& xOut)  // if you use out parameters try to add the word Out after the name making it clear that its a out parameter
{
	xOut = 5;
}

#if 0
void foo1(int x);
void foo2(int& x);
void foo3(int* x);
#endif 

void modifystring (std::string& INOUT)
{
	// use INOUT and modify it
}


int main()
{
	print(5);
	std::string s{ "Hello there" };
	print(s);
	

	double sin{ 0.0 };
	double cos{ 0.0 };

	double degrees{};
	std::cout << "Enter number of degrees: ";
	std::cin >> degrees;

	getSinCos(degrees, sin, cos);
	std::cout << "The sin is: " << sin << " and the cos is: " << cos << '\n';


	//But there are some downsides to "out parameters":

	int x{ getByValue() };                    // can be used to initialize an object directly
	std::cout << getByValue() << '\n';        // can use temporary return value in expression

	//first downside of out parameter is you need to allocate firs an assignable object you cant just initialize directly
	int y{};
	getByReference(y);
	std::cout << y << '\n'; // second downside : and only then can we use the value



	//Another issue of "out parameter is that they dont make it clear that they are gonna modify the argument:
	x = getByValue(); // very clear that x is gonna be modified

	getSinCos(degrees, sin, cos); // not clear that only sin and cos are gonna be modified 
	//for this case you can consider using pass by address which makes it a bit clearer bc of the & syntax that the argument is gonna be modified:
#if 0
	int i{};
	foo1(i);   // cant modify i 
	foo2(i);   // can modify i but not obvious
	foo3(&i);  // can modify i and makes it clear it prob will

	int* ptri(&i);
	foo3(ptri);  // can modify i but bc we ommited & its not obvious
	// but this way does add the problem with nullptr again and us being forced to check for them
#endif 
	
	//In conclusion try to avoid out parameters and if you are forced to use them use pass by reference

	//there is also IN/OUT parameters basically being the same as out parameters just that the passed argument is used first before modified but its basically the same and has the same nuances


	//As we mentioned multiple times try to prefer passing by const reference rather than passing by non const reference but there are two cases where we want to pass by non const reference:
	// First usecase when you have a IN/OUT parameter and this way you avoid the copies its more straight
	std::string wort{ "Wort" };
	modifystring(wort); 
	//Alternative of that would be using pass by value or pass by const reference and copying the modiefied value and using retur back which leaads to possible expensive copies made along the way which you then need to assign to the variable in main

	//Second usecase is when you have a normal parameter but copying it is very expensive so instead you use out parameter 
	
	//(most commonly use are arrays which we will cover in the future)


	//Conclusion: Objects are rarely that expensive that we need to resort to non conventional methods of returning objects like IN/OUT parameters.
	return 0;
}