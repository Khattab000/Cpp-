#include <iostream>
#include <string>
#include <string_view>

//In this lesson we talk how to use struct with other program defined types, there are two way to do so

//First way is to define one program defined type in the global scope and use it as a member of another program defined type e.g:

struct Employee
{
	int id{};
	int age{};
	double wage{};
};

struct Company
{
	int numberOfEmployees{};
	Employee CEO{};  // Employee is a struct inside the struct Company we where able to use it bc Employee is defined in the global scope
};


//Second way is to nest Employee inside Company if its mainly used in Company e.g:
struct Company2
{
	struct Employee2   // this is accessed by for example Company2::Employee2 frank{};
	{
		int id{};
		int age{};
		double wage{};
	};
	int numberOfEmployees{};
	Employee2 CEO{};  // Employee is a struct inside the struct Company we where able to use it bc Employee is defined in the global scope
};


/*
One thing about structs is that we want the struct and its members to be owners not viewers (like std::string_view, references or pointers) so try to give them owning 
types like int or double. Bc if one of the members is left dangling accessing that member might lead to undefined behavior e.g:
*/

struct Owner
{
	std::string s{};
};

struct Viewer
{
	std::string_view sv{};
};

std::string getName()
{
	std::cout << "Enter a Name: ";
	std::string s{};
	std::cin >> s;
	return s; // this will return the temporary string s and is destroyed after the function call
}



//Lets talk about the size of struct, normally the size of struct is just the sum of all its members types but there are exception e.g:
struct Foo
{
	short a{};
	int b{};
	double c{};
};


struct Foo2
{
	short a{}; // 2 byts of padding bc int a larger type is next and it needs to allign with it 
 	int b{}; 
	short c{}; //2 bytes of padding at the end for  allignment making the struct size become a multiple of 4
};

struct Foo3
{
	int a{};
	short b{}; //no padding bc no allignment needed bc its a smaller type
	short c{}; //no padding bc no allignment needed bc struct size already multiple of 4

	// to avoid padding try starting with the larger types and then decrease the lower you get 
};


int main()
{
	Company myCompany{ 600,{1,67,9000.0} };  //nested initialization  list to initialize Employee
	std::cout << myCompany.CEO.wage << '\n'; // print the CEO's wage so we need ot access .CEO first and then .wage

	Company2 myCompany2{ 700,{1,42,10000.0} }; //nested initialization  list to initialize Employee2
	std::cout << myCompany2.CEO.wage << '\n';


	Owner name1 { getName() }; // this is fine the temporary string s is copied by value to name1 so its fine that s is destroyed afterwards
	std::cout << "Owner name is " << name1.s << '\n'; //ok

	Viewer name2{ getName() }; // this isnt fine bc the temporary string s is only viewed by name2 and than s is destroyed afterwards making which leads to name2.sv left dangling
	std::cout << "Viewer name is " << name2.sv << '\n'; //undefined behavior



	std::cout << "The size of short is " << sizeof(short) << " Bytes\n";    // 2 Bytes
	std::cout << "The size of int is " << sizeof(int) << " Bytes\n";        // 4 Bytes
	std::cout << "The size of double is " << sizeof(double) << " Bytes\n";  // 8 Bytes

	std::cout << "The size of Foo is " << sizeof(Foo) << " Bytes\n";        // 16 Bytes / even tho we expected 14 Bytes bc 2 + 4 + 8 = 14 
	/*
	It turns out we can only say for sure how large at least a struct has to be in this case 14 Bytes but the actual size might be bigger like in this case 16 Bytes, 
	this happens bc the compiler will sometimes add gaps into the structure for performance reasons we call that padding. In this case the padding was  added 
	after Foo.a bc it seems to add 2 Bytes of padding to short quite often and this can have significant effects on the size of the struct e.g:
	*/

	std::cout << sizeof(Foo2) << " Bytes\n";  // 12 Bytes
	std::cout << sizeof(Foo3) << " Bytes\n";  //  8 Bytes

	//Even tho Foo2 and Foo3 had the same amount of members with the same types , Foo2 still is 50 percent larger due to the order of the members and the applied padding
	//To avoid padding as we said order the members in a decreasing fashion

	return 0;
}