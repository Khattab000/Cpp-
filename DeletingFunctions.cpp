#include <iostream>

//sometimes depending on your input your function doesn behave as desired and lets say we dont want it to promote char or bool and then to print it
void printInt(int x)
{
	std::cout << x << '\n';
}
// int this case we can use the = delete specifier to tell the compiler to halt compilation when the function is called with a certain type e.g:

void printInt(char) = delete; // also counts as overloaded function
void printInt(bool) = delete; // also counts as overloaded function


// but lets say we ONLY want int being accepted so using = delete on each type might be cumbersome but gladly there is a way (we cover the details in a future chapter) e.g:
template <typename T>
void printInt(T x) = delete;
// now every Type (other then int bc int is defined above that and takes precedence over this) will give a compiler error now we are forced to use int

int main()
{
	printInt(5);    // okay prints 5
#if 0 // these two cant be called anymore bc we used the delete specifier
	printInt('a');  // prints 97 due to promotion but not sure we want that
	printInt(true); // prints 1 due to promotion but not sure we want that


	printInt(5.0); // Error: ambiguous call — double can be converted to int, but not via promotion. However, the compiler also sees other overloads (e.g., deleted ones) and can't resolve unambiguously.
#endif

	return 0;
}