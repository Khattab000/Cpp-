#include <iostream>
#include <string>

int return5()
{
	return 5; // 5 is an rvalue expression
}




template <typename T>
constexpr bool is_lvalue(T&) //T& is an lvalue reference so this overlaod will be preferred for lvalues
{
	return true;
}

template <typename T>
constexpr bool is_lvalue(T&&) //T&& is an rvalue reference so this overload will be preferred for rvalues
{
	return false;
}

// A helper macor (#expr prints whatever is passed in for expr as text)
#define PRINTVCAT(expr){std::cout << #expr << " is an " << (is_lvalue(expr)?"lvalue\n":"rvalue\n");}

int getInt()
{
	return 5;
}


int main()
{
#if 0
	/*
	There are two things to an expression , the type of the expression and the value. The first determines what type the outcome of the expression has and the latter
    decides the interactions it has with other types or on what side it can be like on the right or on the left side 
	*/

	int x{};
	x = 5; // correct / bc x is a modidifiable lvalue and on the right is an rvalue (could be lvalue to would be just converted)

	5 = x; //incorrect /bc 5 is rvalue which cant be modified and the operator requires the right side to

	//so how does the compiler know which one is correct and which isnt valid, thats where value category comes into play determining if the expression resolves to a value,function or object
	// we have two main value categories lvalue and rvalue ( there are more like glvalue,prvalue and xvalue but we will cover those later when we talk about move semantics)

	//A lvalue is an expression that evaluates to an identifiable object e.g:
	int x1{ 5 };
	int y{ x };  // x is an lvalue expression
	//there is also two types of lvalues the one that can be modified and the one that cant be modified e.g:
	int x2{};
	const double d{};
	int y2{ x2 }; // x2 is a modifiable lvalue expression
	const double e{ d }; //d is an non modifiable lvalue expression

	//A rvalue on the other hand is an expression that doesnt evaluate to an identifiable object and is basically the opposite of lvalue (does exclude C-Style literals) e.g:
	int x3{ 5 };             // 5 is an rvalue expression
	const double d2{ 1.2 };  // 1.2 is an rvalue expression

	int y3{ x3 };            // x3 is a modifiable lvalue expression
	const double e2{ d2 };   // d2 is a modifibale lvalue expression
	int z{ return5() };      // return5() is an rvalue expression  (since the result is returned by value)

	int w{ x + 1 };                   // x + 1 is a rvalue expression
	int q{ static_cast<int>(d2) };    // the result of static casting d2 to and int is an rvalue expression 
 
	// You  may wonder why return5(), x + 1 or static_cast<int>(d2) are rvalue expression, the reason being the only give us a temporary value without identifiable objects
	// So in general Lvalue expressions evaluate to identifiable object and rvalue expression evaluate to a value

	//Certain operators have an expectatation or rquirements what kind of values are used either rvalue or lvalues e.g:
	std::cout << 1 + 2 << '\n'; // 1 and 2 are rvalues operator + returns an rvalue and expects rvalues as its operands /in the case of these operators when you give them an lvalue it converts the lvalues to rvalues to be able to do the operation
	/*
	now we can answer our first ever question about why x = 5 works and 5 = x doesnt work, the reason being that  the operator = requires its left operator to be a 
	modifiable lvalue and the right operator to be an rvalue (again tho in most operator matters its fine if you use and lvalue on the right too bc it can be just converted, 
	the same cant be said about rvalues which cant be converted to lvalues thats why have the error
	*/


	// as we stated earlier lvalues can be converted to rvalues so it they can be used whenever a rvalue is expected (not possible vice versa) e.g:
	int b{ 1 };
	int g{ 2 };
	b = g; // since g isnt an rvalue you prob why this works /this works bc if an rvalue is expected but a lvalue is provided the lvalue undergoes lvalue to rvalue conversion making g turn to 2 making it a viable rvalue

	//another example 
	b = b + 1; // the b on the right undergoes conversion so its able to be used with the operator + and the whole calculation +1 bvecomes an rvalue so we can proceed with b =

	

	/*
	Here is a rule of thumb how to differentiate lvalues and rvalues:
	-lvalue expressions are those that evaluate functions or identifiable objects (inlcuding variables) that persist beyond the end of the expression
	-rvalue expressions are those that evaluate to values,including literals (not C-Style literals tho) and temporary objects that do not persist beyond the end of the expression
	*/
#endif
	// There is a way tho to make the compiler tell us if smth is an rvalue or lvalue: 
	PRINTVCAT(5);                         //rvalue
	PRINTVCAT(getInt());                  //rvalue
	int x{ 5 };                           //rvalue (5) /but the x itself would an rvalue but we mostly are talking about expressions rn
	PRINTVCAT(x);                         //lvalue
	PRINTVCAT(std::string {"Hello"});     //rvalue
	PRINTVCAT("Hello");                   //lvalue   / is lvalue bc of it being an array and decaying to a pointer so it needs to be lvalue
	PRINTVCAT(++x);                       //lvalue
	PRINTVCAT(x++);                       //rvalue

	return 0;
}