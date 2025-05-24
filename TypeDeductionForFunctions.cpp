#include <iostream>
#include <type_traits> // for std::common_type


#if 0
//In an earlier chapter we talked about Type Deduction now we have a look how it works with functions :
auto add(int x, int y)
{
	return x + y; // this will return an int bc both variables are int and auto doesnt work on a functions with out parameters/input
}
//And also important to not if using auto all return values gotta be from the same type otherwise we get an error:

auto someFcn(bool leaver)
{
	if (leaver)
	{
		return 5;
	}
	else
	{
		return 5.9; 
	}
}
// error bc auto cant be used with multiple return types here the function returns either int or double /if you still wanna do it then without auto and either implicit or explicit covnersion like with static_cast


//now to a big advantage of using auto ín function return types e.g
auto add2(unsigned short x, char y)
{
	return x + y; //with auto its pretty easy bc it already knows what type it is but if we put the return type manually we might run into errors or not intended conversion so for more complex types this is very useful
}

/*
There are two major downsides to auto in return types:

First Downside: Functions that use auto need to be fully defined first to be able to be use and a forward declaration is not sufficient and leads to an error e.g:
*/

auto foo(); // forward declaration of foo()

int main()
{
	foo(); // error bc functions with auto in the return type cant be forward declared they need to be fully defined first / bc auto doesnt have enough info in the forward declaration to deduce the type so auto functions are mainly used only in the same file
	return 0;
}

auto foo()
{
	return 17.9;
}


/*
Second Downside : It hard for us to find out what the type is without digging into function body unlike when using auto with variables their initializer are always present,
where its pretty clear just looking at it and this also makes errors more likely so generally try to avoid using auto in function return types unless the return type is not important
or difficult to express
*/



//But another use case for the auto keyword is to use in Trailing return type syntax which basically puts the return type after the function prototype but in this instance auto doesnt do deduction its more like a place holder e.g:

auto add4(int x, int y) -> int // the exact same as int add4(int x, int y)  / in this case auto is just part of the syntax
{
	return x + y;
}
//Here are reasons why you would wanna use Trailing return type syntax:
//1.Functions with complex return types (readability):
std::common_type_t<int, double> compare(int, double); // harder to read and figure out where the name is
auto compare2(int, double) -> std::common_type_t<int, double>;// easier to read and figure out where the name is

//2.Multiple consecutive functions calls names are alligned which makes it easier to read:
auto add5(int x, int y) -> int;
auto divide6(double x, double y) -> double;
auto printSomething() -> void;
auto generateSubstring(const std::string& s, int start, int len) -> std::string;

//3.If we have a function whose return type must be deduced based on the type of the function parameter then a normal return type isnt enough e.g:
std::common_type_t<decltype(x), decltype(y)> add7(int x, int y); // compiler error , compiler hasnt seen the definitions of x and y yet
auto add8(int x, double y) -> std::common_type_t<decltype(x), decltype(y)>; //okay bc now it has seen the definition of x and y first /btw decltype() gives us the type of the variable or literal and std::common_type_t gives us the common type between two types that why decltype() is needed

//4.Trailing return syntax is also used for some advanced features like lambdas which we will cover in the future


// But for now its recommended to continue using the traditional function syntax over the Trailing one unless you rly need it or its required
#endif

void addAndPrint(auto x, auto y) //unfortunatly type deduction doesnt work with function parameters and before C++ 20 it also didnt compile
{                                // in C++ 20 the auto keyword was extended so that this function compiles when called but in this case auto isnt invoking a type deduction its using a diffrent feature called "function templates" which handles such cases we will discuss this further in a future chapter
	std::cout << x + y << '\n';
}



int main()
{

	addAndPrint(3, 8); // call addAndPrint with int parameters
	addAndPrint(4.4, 6.7); // call addAndPrint with double parameters
	return 0;
}