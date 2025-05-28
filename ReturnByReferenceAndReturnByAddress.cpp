#include <iostream>
#include <string>

/*
We already covered that for non fundamental types copying to the parameter is expensive that why we use pass be reference or pass by address to avoid that 
but what about the return ? Bc the return also copies the expensive value back (e.g std::string foo() which returns a std::string which is exepensive)
to the caller so we need to tackle that. By default its return by value but just like with parameters we can return by reference or return by address e.g:

std::string& foo();        //returns a reference of std::string so this is cheap
const std::string& foo()   //returns a reference to const ost std::string which is cheap

std::string* foo();       // returns a pointer of std:string so this is cheap
const std::string* foo(); // returns a pointer to const of std:string so this is cheap
*/

const std::string& getProgramName() // returns a const reference
{
	static const std::string s_programName{ "Calculator" }; //static so its not destroyed after the function call still stays and doesnt need to be initialized again
	                                                        //this is important for return by reference and return by address otherwise it is left dangling which will lead to undefined behavior
	return s_programName;
}

#if 0
//The programmer must make sure that the object that is referenced or whose address we returned stays and isnt destroyed after the function call otherwise the reference/address is left dangling:
const std::string& getProgramNameNoStatic() // returns a const reference
{
	const std::string s_programName{ "Calculator" };  //now the variable is a non static destroying it after the function call making the reference be left dangling
	return s_programName;
}

//so never return a non static local variable or temporary variable by reference 



//lets see what happens when we return a temporary by reference:
const int& returnByReference()
{
	return 5; // returns const reference to temporary object
}
#endif
//here is another example for what happens when you return a literal by function
const int& returnByReferenceI(const int& ref)
{
	return ref;
}


const int& getNextID()
{
	static int s_x{ 0 }; // notice the variable is not const
	++s_x;               // generate the next id
	return s_x;          // return a reference to it
}


std::string& getName()
{
	static std::string s_name{};
	std::cout << "Enter a name: ";
	std::cin >> s_name;
	return s_name;
}


void printFirstAlphabetical(const std::string& s1, const std::string& s2)
{
	if (s1 < s2) // both s1 and s2 are referencing the last input name bc they both are referencing the same non const static variable
	{
		std::cout << s1 << " comes before " << s2 << '\n';
	}
	else
	{
		std::cout << s2 << " comes before " << s1 << '\n';
 	}
}


const std::string& alphabetOrder(const std::string& s1, const std::string& s2)
{
	return(s1 < s2 ? s1 : s2); //completely safe to return parameter references bc we know its in scope 
}



const std::string& foo(const std::string& s)
{
	return s;
}


std::string getHello()
{
	return "Hello";  //implicit conversion to std::string
}

int& max(int& x,int& y )
{
	return x > y ? x : y;
}


int main()
{


	std::cout << "This program is named " << getProgramName() <<".\n";  //returns a reference of s_programName so no need for an expensive copy
#if 0
	const int& ref{ returnByReference() }; 
	/*
	initialized with a temporary reference to an temporary object which both go out of scope after the function call and bc lifetime extension doesnt work accross function
	boundaries we get a dangling reference 
	*/
	std::cout << ref << '\n';  //undefined behavior
#endif
	const int& ref1{ 5 }; //5 got a temporary object assigned and its lifetime got extended
	std::cout << ref1 << '\n'; //everything is fine reference still has access to the temporary opject holding 5

	const int& ref2{ returnByReferenceI(5) }; //binds to a dangling reference bc the temporary object holding 5 went out of scope after the function call
	std::cout << ref2 << '\n';  // undefined behavior

	//so in general lifetime extensions does not workd across function boundaries so keep that in mind and dont return temporary by reference



	//Now lets look at smth else and why you shouldnt return non const static variables by reference e.g:
	const int& id1{ getNextID() };
	const int& id2{ getNextID() };
	std::cout << id1 << ' ' << id2 << '\n';
	/*
	This prints 2 2 instead of 1 2 because both id1 and id2 are referencing the same static variable,
	which gets incremented on each call. The static variable is updated, so both references see its final value.
	This can be easily fixed tho by making id1 and id2 to normal int instead of references this way they just get the value passed down of the reference instead of being 
	a reference themselves to s_x. Another issue by using a non const static and returning it by reference is its not easy resetting it to the default state other then 
	maybe using a dedicated reset function or restarting the program. So in general avoid returning references to non const static variables.
	*/
	//here is another example with issues of returning a non const static variable
	printFirstAlphabetical(getName(), getName()); 
	/*
	 Both getName() calls may return a reference to the same static variable.
     If modified during the calls, both parameters might reference the same (changed) value,
     leading to unexpected results (e.g., same name printed twice).

	 Using std::string_view parameters wouldnt have worked either bc at the moment the string chaged it would invalidate the first std::string_view so in this case 
	 to fix it we would need to make the parameters std::string instead of a reference to just copy the value in there
	*/
	
	//Returning a const referenece to const static is used if you want to return an expensive variable that is too expensive to be copied or initialized over an over again between function calls
	//Returning a const reference to const global is used to sometimes encapsulate access to a global variable making it easier to make changes later on but try to be careful about that


	//As we stated earlier with the getNextID() example is that if we assing or initialize a normal variable with a returned reference , makes a copy of the value to assign/initialize it with:
	const int id3{ getNextID() };
	const int id4{ getNextID() };
	std::cout << id3 << ' ' << id4 << '\n'; //will print 3 and 4 bc this time the value are just copied bc id3 and id4 arent references just normal variables 
#if 0
	//IMPORTANT if a program returns a dangling reference the reference is left dangling before the copy is made and this will lead to undefined behavior e.g:
	std::string name{ getProgramNameNoStatic() }; //makes a copy of a dangling reference 
	std::cout << "This program is named " << name << ".\n"; //undefined behavior
#endif
	//Always make your returned reference static to avoid dangling references


	//Ofc its completely safe to return reference parameter by reference even without making sure they are static bc to be able to pass them down they need to exist in the scope of the caller:
	std::string hello{ "Hello" };
	std::string world{ "World" };
	std::cout << alphabetOrder(hello, world) << '\n'; //safe and cheap avoiding making any copies
	//The same ruling applies for rvalues passe by const reference parameters these are also safe to be return by const reference bc the temporary object is still in scope and got extended lifetime e.g:
	const std::string s{ getHello() }; //the rvalue is destroyed right after the expression
	std::cout << s << '\n';
	const std::string s2{ foo(getHello()) }; // this works bc foo() extends the lifetime of the literal
	std::cout << s2 << '\n';
	/*
	This works because the temporary std::string returned by getHello()
	is bound to a const reference parameter in foo(), and then immediately
	used to initialize a new std::string (s2), which extends the temporary's lifetime.

	Returning a reference to a temporary directly (e.g., return std::string("Hello"))
	is dangerous because the temporary is destroyed after the return statement,
	leaving a dangling reference. Example:
	const std::string& foo() { return std::string("Hello"); }  // Undefined behavior

	In contrast, returning a reference to a parameter (like const std::string& s) is safe
	because the object exists in the caller's scope. Also, if an rvalue is passed to a const
	reference parameter, its lifetime is extended until the end of the full expression,
	making it safe to return that reference
	*/


	//The caller can modify values through reference 
	int a{ 3 };
	int b{ 5 };

	max(a, b) = 7; // sets the greater of a or b to 7 bc the function returned a reference to the greater one
	std::cout << a << ' ' << b;




	/*
	Now we talked about return by reference a lot but what about return by address and its basically the exact same with basically the same rules and the same caeveats
	where you need to make sure that the object whose address is returned outlivess the function call otherwise you risk a dangling pointer.
	There is one major advantage tho of return by address which is being able to return nullptr in case that there isnt a valid object to return for example if we are looking 
	for a student and find him we can return a valid pointer to him but if we dont find any we can return a nullptr indicating that no valid objects where found.
	BUT there is also a major disadvantage for return by address which is the dereferencing the nullptr issues we talked about earlier basically being forced to check for nullptr
	before dereferencing a pointer which otherwise might lead to undefined behavior.
	*/

	//Conclusion prefer return by reference to return by address unless return nullptr is needed or important

	return 0;
}