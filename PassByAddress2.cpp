#include <iostream>
#include <cstddef> //for NULL / for std::nullptr_t


#if 0
/*
Another common use case of pass by address is optional argument whereas depending if smth was passed down or not the function changes
(of you can do that with bool and other types too but here you do it with the address meaning you can access the value behind it too and use it)
*/
void printIDNumber(const int* id = nullptr) // if nothing was passed down the defaulted to nullptr
{
	if (id) // if valid address was passed
	{
		std::cout << "Your ID number is: " << *id << '\n';
	}
	else  // if nothing or a nullptr was passed
	{
		std::cout << "Your ID number is not known.\n";
	}
}
#endif

/*
But its better to use function overloading over pass by address with optional arguments, bc then we no longer need to worry about mull dereference
and can pass in literals or other rvalues :
*/

void printIDNumber()
{
	std::cout << "Your ID number is not known.\n";
}

void printIDNumber(int id)
{
	std::cout << "Your ID number is: " << id << '\n';
}




void nullifyptr(int* ptr2)
{
	ptr2 = nullptr;  // this doesnt affect the original ptr that was passed to the function
}

void nullifyptrref(int*& refptr) // refptr is a reference to a pointer so no longer is the address copied to the parameter /syntax is int*&
{
	refptr = nullptr;  // this now also affects the original ptr that was passed to the function
}


void print(int x)
{
	std::cout << "print(int): " << x << '\n';
}

void print(int* x)
{
	std::cout << "print(int*): " << (x ? "non null ptr\n" : "null ptr\n");
}

void print(std::nullptr_t t)  // the type of nullptr is std::nullptr_t so if we pass the nullptr keyword it will always pick this fucntion over the normal pointer function
{                           /*
							notice how i said nullptr keyword and not null ptr in general bc for example if its a int pointer wich holds a null pointer it would pick
							the normal pointer function not the nullptr type function one bc the overloading looks at types not values and the even tho the value
							is still a nullptr the type isnt so keep that in mind and btw std::nullptr_t can only hold nullptr and its main usage is to make sure if 
							a nullptr keyword was passed so we can use the specific overloaded function
							*/ 
	std::cout << "print(std::nullptr_t): null ptr\n";
}

int main()
{
	printIDNumber();
	int userID{ 7 };
#if 0
	printIDNumber(&userID);
#endif

	printIDNumber(userID);
	printIDNumber(122); //now we can also pass literals and rvalues



	//So lets talk about changing what a pointer parametert points at and if it affects the pointer passed to it
	int x{ 8 };
	int* ptrx{ &x };
	std::cout << "the pointer is a " << (ptrx ? "non null ptr\n" : "null ptr\n");

	nullifyptr(ptrx); //makes the ptr parameter to a nullptr
	std::cout << "the pointer is a " << (ptrx ? "non null ptr\n" : "null ptr\n");
	//both print "the pointer is a non null ptr" showing that just passing the ptr and then changing the parameter doesnt affect the original ptr bc we just copy the address to the parameter
	//but what if we want to change the origianl ptr so that changes to the parameter chages the original ptr too , for that we pass the address by reference:
	nullifyptrref(ptrx);
	std::cout << "the pointer is a " << (ptrx ? "non null ptr\n" : "null ptr\n"); 
	//this prints "the pointer is a null ptr" now bc we passed the pointer by reference so the changes in the function affected the pointer we passed to the function


	//We stated in an earlier lesson that you should use nullptr instead of NULL or 0 and here is why:
	int y{ 7 };
	int* ptry{ &y };
	
	print(ptry);     // always calls print(int* x) bc we passed a pointer very clear
	print(0);        // calls print(int x) bc we passed a literal (hopefully this what we expected if we expect it to be a nullptr we will be dissapointed)
	print(NULL);     // tbh could do anything it rly depends on the compiler very ambigious
	print(nullptr);  // always calls print(int* x) /unless there is a function with a std::nullptr_t type which we will cover below
	// so you see try to avoid NULL and 0 and just use nullptr to be completely sure 


	//lets show some examples about the nullptr type std::nullptr_t which we use in the function parameter above
	print(nullptr); // this now calls print(std::nullptr_t t) bc no conversion needed so preferred over print(int* x)
	ptry = nullptr;
	print(ptry);    // still calls print(int* x) even tho it holds a nullptr now the type is what matters and the type is still int*



	//WAIT ITS ALL PASS BY VALUE ? IT ALWAYS HAS BEEN
	//basically reference are implemented by the compiler using pointers and passing pointers basically just copies the address so at the end its just pass by value with extra steps

	return 0;
}