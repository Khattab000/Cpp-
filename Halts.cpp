#include <iostream> 
#include <cstdlib> // used for std::exit() and std::abort

// when a program terminates with return the std::exit() function is called implicitly but if you wanna call std::exit() explicitly yourself you gotta include the cstdlib library


void cleanup()
{
	std::cout << "cleanup!\n";  // this could be anything like freeing/cleaning up memory or making sure certain stuff happen before the exit
}

int main()
{
#if 0
	std::cout << 1 << '\n';

	std::atexit(cleanup); // with that we dont need to call the cleanup function ever again bc its automatically called when we use std::exit() / and only name needed of the function no the () after like we normally do when calling functions
	// important the functions in std::atexit() need to not take any parameters and have no return value and you can register multiple ones e.g: std::atexit(cleanup); std::atexit(memory); std::atexit(washing);    and they are called in reverse order so first washing then memory and lastly cleanup

	// also in  multi threaded programs you might wanna use std::quick_exit and std::at_quick_exit so you avoid static objects being cleaned in case other threads still use them

	std::exit(0); // terminate and return status code 0 to OS  and the code below that wont be executed 

	std::cout << 2 << '\n';

	// main difference of return and std::exit() is that if used in a function outside of main return just terminates the function but std::exit() terminates the whole program 
	
	/*
	unlike return std::exit doesn't clean up local variables if called explicitly so its recommended to do the necessary cleanup before like in the example when we called the function cleanup()
	but calling it every time you use std::exit might be tedious so in this case we can use std::atexit() with that it automatically calls the designated function when we use std::exit()
	*/

#endif
 
	//now to std::abort() which terminates your program abnormally e.g

	std::cout << 1 << '\n';
	std::abort(); // terminates abnormally and causes a runtime error like if you tried dividing through 0 which also causes a runtime error and ofc this termination doesnt do any cleanup

	std::cout << 2 << '\n'; // never executes

	// there is also std::terminate() which works in conjunction with std::abort() which means it calls it but its mainly used when you try to handle a unhandled exception we will cover its use cases in a later chapter



	//Conclusion: You should avoid using Halts bc most of them arent cleaning local objects which is an issue bc thats important in C++ when we get into classes so you rather use Exception which we will cover later too so only use them if tere is no other way to retunr normally from a function

	return 0;
}