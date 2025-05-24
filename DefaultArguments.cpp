#include <iostream>
#include <string_view>






#if 0
// a default arguments is a default value provided for a function parameter e.g:
void print(int x, int y = 10) //10 is the default argument in case an argument for y wasnt passed down if one is passed dont the value is then replaced
{// btw for default values only = works so y = 10 is fine but y{10} or y(10) leads to a compile error
	std::cout <<"x: " << x << '\n';
	std::cout <<"y: " << y << '\n';
} // surprisingly the compiler handles default at call site not before so a function call like print(1) is rewritten to print(1,10)


//Here are a couple use cases when to use default values in functions e.g:

// default arguments are used when a function needs a value that has a reasonable default value but you want the user to be able to override it if he wants
int rollDie(int sides = 6);
void openLogFile(std::string filename = "default.log")

/*
default arguments can be also helpful if we want to add an additional parameter to an already existing function bc without the default value all previous
function calls to the function will be most likely broken but with the default argument they all still work and we can use the extra parameter in future function calls
*/


//A function also can have multiple default arguments :

void print(int x = 10, int y = 20, int z = 30)
{
	std::cout << "Values: " << x << " " << y << " " << z << '\n';
}





void print(std::string_view sv = "Hello", double d = 10.0);



//Default arguments can not be redeclared so you either put them in the definition or the forward declaration but you cant put it in both e.g:
void print(int x, int y = 10); // forward declaration
void print(int x, int y = 10)  // compiler error 
{
	std::cout << x << " " << y << '\n';
}
/*
Another thing to note the default argument must be declared before use e.g:

void print(int x, int y);

int main()
{
  print(1);    // compile error default value couldnt be used bc its not declared yet
}

void print(int x, int y = 10) // this time its fine bc default wasnt declared twice
{
	std::cout << x << " " << y << '\n';
}



//Conclusion to redeclaration: if you use forward declaration like in a header file try putting the default argument in there instead of the definition of the function
  bc the declaration is most likely seen first by other files e.g:


in foo.h:
void print(int x, int y = 10);

in main.cpp: 
#include <iostream>
#include "foo.h"

int main()
{
  print(1);    // now its fine
}

void print(int x, int y) // dont put the default here bc its already in the forward declaration
{
	std::cout << x << " " << y << '\n';
}


// otherwise if you dont use forward declaration just put it the default argument in the function definition
*/


/*
You can also overload functions with default arguments BUT default arguments are not used to differentiate and are not part of the functions signature e.g:
int add(int x = 10)
{
return x;
}
so its signature is add(int) thats it so if we defined another function called int add(int x = 20) it wouldnt count as differentiated and will lead to a compile error
*/ 
void print(std::string_view s)
{
	std::cout << s << '\n';
}

void print(char c = ' ')   // succesfully overloaded a function with default 
{
	std::cout << c << '\n';
}
#endif

void foo(int x = 0)
{

}
void foo(double x = 0)
{

}


void print(int x); // signature print(int)
void print(int x, int y = 10); //signature print (int,int)
void print(int x, double y = 20.5) //signature (int , double)



int main()
{
#if 0
	print(1, 2); // prints 1 and 2
	print(1);    // prints 1 and 10 bc no value was passed for the second argument so a default one was used  


	print(1, 2, 3); // prints 1,2,3
	print(1, 2);    // prints 1,2,30 bc the last argument was omitted so it used the default
	print(1);       // prints 1,20,30 bc the last two arguments were omitted so it used the defaults
	print();        // prints 10,20,30 bc all arguments were omitted so it used the defaults
	/*
	print(,,3)     // smth like that is currently not possible so  its not possible to use an explicit value for z but a default one for x you need to start with the right most one
	*/

	//Here are 3 consequences of that:
	//1
	print();             // okay both arguments defaulted so this defaults to ("Hello",10.0)
	print("Macaroni");   // okay d defaults to 10.0
	print(20.0);         // error does not match abovefunction cannot skip argument sv
	//2
	void print(int x = 10, int y);
		/*
		this is not allowed you gotta start with the right most in this case if the leftmost has a default value then everything also does need one so if smth gets a default
		argument everything on the right also needs one / ik this is supposed to be written outside of main its just for learning
		*/

		//3 
		//If more then one parameter has a default argument the leftmost parameter should be the one most likely set by the user
#endif


	print("Hello World"); // calls print(std::string_view)
	print('a');           // calls print(char)
	print();              // calls print(char)


	
	// You need to be careful tho bc default arguments can easily lead to ambiguous matches !!!!! e.g: 
	foo(); // normally the error would be that no arguments where passed but in this case its the ambiguous match error and compiler doesnt know if he should do foo(0) or foo(0.0)
	//Here another example for ambiguous matches
	print(1, 2);   // calls print(int,int)
	print(1, 2.5); // calls print (int, double)
	print(1);   // compile erro   
	/*
	compiler error doesnt know if to call print(int) (which we prob wanted to) or print(int, int) or print(int, double), ambiguous function call bc normally with a normal 
	overload without defaults it wouldnt be an issue but with defaults technically all function calls only need one parameter 
	*/

	return 0;
}