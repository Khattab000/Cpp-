#include <iostream>

int main()
{
	int x{ 5 };
	int* xptr { &x }; //ptr is a normal non const pointer

	int y{ 6 };
	xptr = &y; // we can change where the pointer points to 
	*xptr = 7; //we can change the value at address that we are pointing to


	//Well what happens when the value is const :
	const int cx{ 5 }; 
#if 0
	int* cxptr{ &cx }; //compiler error bc cant convert from const int* to int* 
#endif
	const int* cxptr{ &cx }; // compiles now bc we are using a non const ptr that points to const for a const variable
#if 0
	*cxptr = 9; //not allowed bc of const value
#endif
	const int cy{ 92 };
	cxptr = &cy; // bc the pointer itself isnt const we can reassign it the const int* merely says that it points to a const value /points to cy now 

	int ncx{ 312 };
	cxptr = &ncx; //just like reference to const , you can assign the pointer to const to a non const variable but it treats the value just like const so no changing it through the pointer itself
#if 0
	*cxptr = 34; //this is not allowed bc we are using pointer to const even if the variable itself is non const
#endif
	ncx = 909; //this is allowed bc doesnt matter if the pointer is to const the variable is still a non const



	//Now we talk about const pointers which are pointers whose address can not be changed after initialization e.g:

	int l{ 8 };
	int* const ptrl{ &l }; //this time the const keyword comes after the type to indicate that its a const pointer , if it is before the type it would be a non const ptr to const
	//this now is a const pointer to a non const
	int op{ 7 };
	int end{ 8 };
	int* const bestptr{ &end }; // okay the const pointer has to be initialized otherwise error / and we cant give it const variables bc this is to non const
#if 0
	bestptr = &op; //this is not possible bc const ptr cant be reassigned
#endif
	//BUT bc its to non const it still can modify the value e.g:
	*bestptr = 90; //even tho its a const ptr bc its to non const we can freely modify the value it points through through the pointer



	//Finally with all that we can do const pointer to const :
	int value{ 5 }; // this can be const int too but doesnt rly matter for the example bc same outcome
	const int* const valueptr{ &value }; // a const ptr to const so now you cant change its address and neither can you change the value of the object it points too through the pointer 

	/*
	Conclusion:
	- a non const pointer (int* ptr) can change what its assigned to
	- a const pointer (int* const ptr) cant change what its assigned to
	- a pointer to non const(int* ptr) change the value of it but cant point to const
	- a pointer to const (const int* ptr)  cant change the value of it but can point to non cons and const but treats both as const
	
	*/
	
	return 0;
}