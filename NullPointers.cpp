#include <iostream>
#include <cstddef>  // for NULL


int main()
{
	int x{ 1 };
	std::cout << x << '\n';

	int* ptrx{ &x };
	std::cout << *ptrx << '\n'; // use the dereferencing operator * to get the value that is stored on that address 

	//in this lesson we will talk about null pointer:

	int* ptrn{}; // here we created a null pointer which holds no address

	int h{ 7 };
	ptrn = &h;  // even tho ptrn was null pointer , just like normal pointers we can change their assignment now ptrn holds an address which points to h
	std::cout << *ptrn << '\n'; // prints the value of h the object its pointing to now


	/*
	But there is also a nullptr keyword which can be used to make a pointer that is holding an address to a nullptr and its also recommended to initialize with it 
	if you explicitly want to create a null pointer even if the keyword isnt neccessary:
	*/
	int* neroptr{ nullptr }; // explicitly making it a nullptr tho the same as int* neroptr{} but the first is recommended
	int kol{ 890 };
	neroptr = &kol;    //neroptr points to kol now and is not a nullptr anymore now its just a normal pointer
	neroptr = nullptr; //neroptr is turned to a nullptr not holding an address anymore
#if 0
	std::cout << *neroptr << '\n'; //dereferencing a null pointer will lead to undefined behavior and will most likely crash the programm
	someFcn(nullptr);  //we can also pass the nullptr keyword for a function with a pointer parameter
#endif

	//So in general be careful when using pointers the most common mistakes being dangling pointers or dereferencing null pointers as this causes undefined behavior and possible crashes

	//Ofc to be safe we can also check for null pointers e.g:
	int jk{ 9000 };
	int* ptrjk{ &jk };
#if 0 //bc there is a better version bc just like how non zero values convert to bool 1 (true) and zero to bool 0 (false) when used in conditional the same applies to nullptr which converts to 0 and normal pointer 1
	if (ptrjk == nullptr)
	{
		std::cout << "ptr is null pointer\n";
	}
	else
	{
		std::cout << "ptr is not a null pointer\n";  // this will execute 
	} 

	// we can also use conditional expression instead of if statements e.g:
	std::cout << (neroptr == nullptr ? "ptr is null pointer\n" : "ptr is not a null pointer\n");  //this will pring "pts is null pointer"
#endif

	if (ptrjk) // no need for == nullptr bc nullptr converts to bool 0 and non nullptr to bool 1
	{
		std::cout << "ptr is not a null pointer\n"; // this will execute / switch the statements tho 
	}
	else
	{
		std::cout << "ptr is  a null pointer\n";  
	}

	// we can also use conditional expression instead of if statements e.g:
	std::cout << (neroptr ? "ptr is not a null pointer\n" : "ptr is a null pointer\n");  //this will print "ptr is null pointer" / no need for == nullptr bc nullptr converts to bool 0 and non nullptr to bool 1

	//but be aware conditionals can only differentiat between null ptr and non null ptr it wont tell you tho if the ptr is pointing to a valid object or is dangling

	/*
	To prevent dereferencing a null pointer you can always use a conditional to make sure its not a null ptr e.g:
	if(ptr)
	{
	  std::cout << ptr << '\n';
	}
	else
	{
	   // do smth else that doesnt involve dereferencing the ptr bc its a null pointer
	}
	
	But what about dangling pointers how to prevent those. Sadly there isnt a ez way to check for them but we can somethings to avoid it e.g:
	- make sure that every initialized ptr is either pointing at an valid object or a null ptr that way we can check for both before dereferencing
	- your responsibility to make sure that after destroying an object to make sure that the pointer is set to a nullptr otherwise it will be left dangling bc they wont be set
	automatically to nullptr

	*/
	

	// In older code and in C you might come across 0 and NULL being used as keywors instead of nullptr e.g
	float* ptrzero { 0 }; // we talked about how literals arent allowed to initialize a ptr but there is an exception that is 0 which sets the pointer to a nullptr
	float ik{ 7.4f};
	ptrzero = &ik;  // pointer set to point to ik
	ptrzero = 0;   // turned to  a nullptr

	double* ptrnil{ NULL }; // same as nullptr 
	double lk{ 8.9 };
	ptrnil = &lk; // pointer set to point to lk
	ptrnil = NULL; // turned to a nullptr
	// BUT both NULL and 0 should be avoided so use nullptr instead why exactly will be covered in the future



	//Lets look at an example showing why using references is a bit safer then pointers :

	int* ptrio{};
	{
		int x{ 5 };
		ptrio = &x;
	} //ptrio is now dangling bc x went out of scope

	if (ptrio) //sadly this only checks if its a null ptr and not if its pointing to a valid object or dangling
	{
		std::cout << *ptrio << '\n';  //might lead to undefined behavior or crashing
	}


	/*
	Conclusion: Favor references to pointers bc of their safety, bc they cant be bound to null which elimminates the worry about null references
	and they need to be bound to a valid object at their initialization and they cant be reseated making dangling references much harder to achieve then dangling pointers
	(ofc this all is only when the additional capabilites of the pointers arent needed)
	*/

	return 0;
}