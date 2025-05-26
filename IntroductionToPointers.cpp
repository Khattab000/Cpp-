#include <iostream>

int main()
{

	char c{'g'};       //char uses 1 byte of memory and lets assume its assigned address is 140
	char& refc{ c }; //ref ís an lvalue reference to c so when we call ref it also goes to the address 140

	//if your interested in the adress of smth use the & operator e.g:
	int x{ 3 };
	std::cout << x << '\n';  // prints the value of x  3
	std::cout << &x << '\n'; // prints the the memory adress of the variable x / 0000006D8393F834 it prints it in hexadecimal
	//For objects tho that need more then one byte the & operator will return the first byte used by the object

	//but knowing the adress isnt that useful by itself thats why we use the * operator to return the value stored at that address e.g:
	std::cout << *(&x) << '\n'; //print the value at the memory address of variable x   3 /() not required but preferred makes it more readable

	//Now we start talking about pointers , a pointer is an object which holds a memory address of another variable we use * after the type (not on the name tho it has to be on the type) to specify one e.g:
#if 0
	int* ptr;      // a pointer to an integer 
#endif
	int& refi{ x }; // a reference as comparison

	/*
	Btw if you declare multiple pointers you need to be careful e.g:
	int* ptr1,ptr2;   // this declares one pointer and one int so this is wrong
	int* ptr1, * ptr2 // this declares two pointers each pointer having their own *  / but tbh just avoid multiple declaration in one line with that 
	*/

	//Always initialize your pointers e.g:
#if 0
	int* ptrw;         //an uninitializeed pointer holds a garbage value
#endif
	int* ptrn{};       //a null pointer (we will discuss that later )
	int* ptrx{ &x };   //a pointer initialized with the address of the int x

	std::cout << ptrx << '\n';  // prints the address of x
	std::cout << *ptrx << '\n'; // prints the value of x that is saved in this address using the dereference operator * 


	//just like how the type of a reference needs to match with the object the same goes for pointers e.g:
	int i{ 2 };
	double d{ 4.8 };

	int* iPtr1 { &i };     //okay int pointer to i
	double* dPtr1{ &d };   //okay double pointer to d
#if 0
	int* iPtr2{ &d };      //not okay int pointer cant point to a double
	double* dPtr2{ &i };   //not okeay double pointer cant point to an int 

	//and initializing a pointer with literal is also disallowed (one exception tho we will cover that in the future) e.g:
	int* lPtr1{ 3 };          //not okay bc its a literal
	int* lPtr2{ 0x0012FF7C }; //not okay even if it where a possible address the hexadecimal is treated as an integer literal
#endif


	//We can change where the pointer is pointing too and also change the value in the address through the pointer e.g:
	int k{ 75 };
	int* kptr{ &k };

	std::cout << *kptr << '\n'; //prints 75 

	int m{ 90 };
	kptr = &m;  //no kptr is pointing to m instead of k

	std::cout << *kptr << '\n'; //prints 90 now 
	//but can also change the value of m now e.g
	*kptr = 89; // we use the * operator to access the value saved at that address and now we changed it to 89 
	std::cout << m << '\n';   //this prints 89 now / the same happens when we print *kptr but the address is still the same bc only changed the value

	// so to repeat ptr = &variable changes the address the pointer is pointing to and *ptr = someValue changes the value of the object in the address the pointer is pointing to 


	//pointers are pretty similar to references e.g:

	int q{ 4 };
	int& refq{ q };  //reference to q
	int* ptrq{ &q }; //pointer to q
	 
	std::cout << q;                //prints 4
	std::cout << refq;             //prints 4
	std::cout << *ptrq << '\n';    //prints 4

	refq = 6;
	std::cout << q;                //prints 6
	std::cout << refq;             //prints 6
	std::cout << *ptrq << '\n';    //prints 6

	*ptrq = 7;
	std::cout << q;                //prints 7
	std::cout << refq;             //prints 7
	std::cout << *ptrq << '\n';    //prints 7

	/*
	There are some differences tho between pointers and references the main being that even tho they can do similar things the pointer needs to explicitly get the address 
	and explicitly dereference to get the value which reference does both implicitly but here are some more:

	- References need to be initialized but pointers dont (but you should)
	- References are not object but pointers are
	- References cannot be reseated pointers can be easily reaseated
	- References always need to be bound to smth , pointers dont they can point to nothing
	- References are mostly safe , pointers tho are inherently dangerous (we discuss its danger later)
	*/

	// The address of operator (&) actually returns the address but not as an literal bc C++ doesnt support address literals but as an pointer type e.g
	int o{ 9 };
	std::cout << typeid(o).name() << '\n';  //returns int
	std::cout << typeid(&o).name() << '\n'; //returns int * __ptr64 indicating its a ptr


	// The size of a pointer depends on the architecture of the executable , for example 32 bit executable has a 32 bit memory address and 64 bit executable a 64 bit memory address and this is regardless of the size of the object that is pointed to
	char* ptrchar{};      // char usually 1 byte
	int* ptrint{};        // int usually 4 bytes
	double* ptrdouble{};  // double usually 8 to 12 bytes 


	std::cout << sizeof(int*) * 8 << '\n';  // * 8 bc sizeof returns the value in bytes not bits /64
	std::cout << sizeof(ptrchar) * 8 << '\n';   // 64
	std::cout << sizeof(ptrint) * 8 << '\n';    // 64
	std::cout << sizeof(ptrdouble) * 8 << '\n'; // 64
	// so regardless of the size of the object where the pointer is pointing the address memory stays the same size
	


	//lets talk about dangling pointers which are similar to dangling reference which also leads to undefined behaviour e.g:
	int tr{ 5 };
	int* ptrtr{ &tr };
	std::cout << *ptrtr << '\n'; //valid /prints 5
	{
		int y{ 8 };
		ptrtr = &y; //now ptrtr points to y instead of tr
		std::cout << *ptrtr << '\n'; //valid /prints 8
	} // but y goes out of scope here and now ptrtr is dangling

	std::cout << *ptrtr << '\n'; // undefined behavior for dereferencing a dangling pointer /prints 8 but might not and smth unexpected might happen like crashing the program so avoid at all cost


	

	return 0;
}