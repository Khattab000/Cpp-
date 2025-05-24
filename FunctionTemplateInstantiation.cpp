#include <iostream>
#include <string>

template<typename T>
T max(T x, T y)
{
	std::cout << "Called Template Function\n";  // this is just for test purposes
	return x < y ? y : x;
}

int max(int x, int y)
{
	std::cout << "Called Overloaded Function\n";  // this is just for test purposes
	return x < y ? y : x;
}




template<typename T>
void print(T c)
{
	std::cout << c << '\n';
}


void print(bool b)
{
	std::cout << std::boolalpha << b << '\n';  // boolalpha makes the bool be printed as true or false instead of 1 or 0
}



template<typename T>
int someFcn(T, double)   // example of templaty type and non template type parameter / btw in this case no names are needed bc they arent used in the function body
{
	return 5;
}


template<typename T>
T addOne(T x)
{
	return x + 1;
}

template<>                                   // template specialization
const char* addOne(const char* x) = delete;  // const char* bc thats what the C-Style literal converts to / = delete to tell the compiler to give an compilation error in this case 


template<typename T>
void printTimes(T val, int times = 1)
{
	while (times--)    //-- after times bc if you put it before it would return 0 but after return 1 and then goes to zero in the next sequence /thats the case if default value is used
	{
		std::cout << val << ' ';
	}
}



template <typename T>
void printIDAndValue(T value)
{
	static int id{ 0 };                     // every instantiated function got its own static int id variable
	std::cout << ++id << ") " << value << '\n';
}


int main()
{
	// the way we call a template function is by max<actual_type>(arg1,arg2) 
	std::cout << max<int>(1,23) << '\n';           // instantiates and calls function max<int>(int,int)
	std::cout << max<int>(1, 0) << '\n';           // this one doesnt instantiate it just goes directly to already created max<int>(int,int) function
	std::cout << max<double>(1, 2) << '\n';    // instantiates and calls function max<double>(double,double) /  int arguments will be converted to double
	//basically when we call the template it creates a function with the specified types


	//there is a different syntax to call template functions bc if the actual_type and the arguments have the same type then you dont need to specify adtual_type e.g :
	max<>(1, 2); // this will call max<int>(int,int) bc the type was deduced from the arguments
	//or 
	max(1.5, 2.4); // this will cal max<double>(double,double) bt the type was deduced from the arguments
	/*
	But be careful there is a slight difference between max<>() and max() the first only will chose a function from a template function but the second also 
	considers and even prefers non template overloaded functions so keep that in mind e.g:
	*/
	max<int>(1, 2);  // calls templated function
	max<>(1, 1);     // calls templated function
	max(1, 6);       // calls non templated overloaded function 
	//this syntax max() is preferred tho bc little to no downsides and if there is a non templated overloaded function we prefer it being called anyways here is an example :
	print<bool>(true); // prints 1 bc of the generic templated function
	print<>(true);     // prints 1 bc of the generic templated function
	print(true);       // prints true bc of the specific overloaded function for the case that its a bool
	
	//In general prefer using the normal function call syntax like print() 


	// function templates can also have non templates type parameters in addition to the template type parameter e.g
	someFcn(1,3.4);             // matches someFcn(int,double)
	someFcn(1,3.4f);            // matches someFcn(int,double)  /float is promoted to double
	someFcn(1.2,3.4);           // matches someFcn(double,double)
	someFcn(1.2f,3.4);          // matches someFcn(float,double)
	someFcn(1.2f, 3.4f);        // matches someFcn(flaot,double) /float is promoted to double



	
	
	// But be careful sometimes depending on the type you use an instantiated function that was created by a templated function wont compile e.g:
	addOne(1);        //this is fine calls addOne<int>(int)
	addOne(2.0);      //this is fine calls addOne<double>(double)
#if 0
	std::string hello{ "hola comaastas" }; 
	addOne(hello); // wont compile so dont call the function with a type std::string
	//this wont compile bc it calls addOne<std::string>(stt::string) which isnt the problem but in the function body it tries to return it + 1 which isnt possible


	//small fun fact if we did addOne("Hello") it would work and return "ello" the reason being this isnt a std::string its a C - Style string which when passed converts to a pointer const char* and + 1 would just move that pointer so thats why the 'H' is removed
	addOne("hello"); // calls addOne<const char*>(const char*) and returns "ello" / prob not what we intended
	//bc of that keep in mind that Instantiated functions dont check if it makes sense semantically it only checks for syntax so keep that in mind 


	//but there is a way to make sure that certain types arent allowed like a C-Style literal by using = delete and smth called template specialization written like this template<> e.g:
	addOne("hello"); // compilation error bc of template<> and = delete / the former addOne("hello"); also doenst work anymore
#endif

	// Template functions ofc also can have default values for non templated paramaters e.g:

	printTimes(5);   // print 5   1 times bc of the default value 
	std::cout << '\n';
	printTimes('n', 6);  // print 'n'   6 times
	std::cout << '\n';



	//Now we discuss what happens static varbiables when used with template functions bc if its a const static then its fine but if it can be modified then it gets complicated e.g:
	//btw static variables regardless where they are called keep their value even between diffrent function calls until the program ends 
	printIDAndValue(12);     //instantiates and calls printIDAndValue<int>(int)   and has a static variable that retains it value between calls                                                           prints 1) 12  
	printIDAndValue(13);     //calls the same function for int  that was already instantiated printIDAndValue<int>(int)   and has the same static variable as the first call so the value was retained    prints 2) 13
	printIDAndValue(14.5);   //instantiates and calls printIDAndValue<double>(double)  and has a different static variable bc the template function instantiated a new function for double                prints 1) 14.5 

	//Conclusion : Use function templates to write genereic code that can work with a wide variet of types whenever you need.

	return 0;
}