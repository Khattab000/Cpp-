#include <iostream>
#include <string>

// In this lesson we talk about Member selection with pointers and references 

struct Employee
{
	int id{};
	int age{};
	double wage{};
};

void printEmployee(const Employee& e)
{
	std::cout << "ID:   " << e.id << '\n';  // even tho e is just a reference  we can access the members with . operator 
	std::cout << "Age:  " << e.age << '\n';
	std::cout << "Wage: " << e.wage << '\n';
	std::cout << '\n';
}



struct Point
{
	double x{};
	double y{};
};

struct Triangle
{
	Point* a{};
	Point* b{};
	Point* c{};
};




struct Paw
{
	int claws{};
};

struct Animal
{
	std::string name{};
	Paw paw{};
};




int main()
{
	Employee joel{ 3,25,80000.00 };

	++joel.age;
	joel.wage = 68000.00;

	printEmployee(joel); //so using a struct with reference and even using the member selection operator . is fine

	//lets look at pointers tho :
	Employee* ptrJoel{ &joel }; //pointer to the struct joel this is fine
#if 0
	std::cout << ptrJoel.id << '\n'; //Compilation error bc we cant use the member selection operator . with pointers
#endif
	
	//To make the member selection operator . work with pointer we first need  to dereference the pointer this is one way to do it:
	std::cout << (*ptrJoel).id << '\n'; //this works now important tho to use () and put the dereference operator and the pointer inside and the member selection operator outside
	
	//But this way is ugly and might not be clear but we have a great solution for that by using the member selection from pointer operator ->  e.g:
	std::cout << ptrJoel->id << '\n';
	/*
	with this we dont need to use* or () bc -> does the dereference itself before selcting the member so it works the exact same as the above but this is preferred bc
	its easier to type and less prone to error so alway use -> instead of (*ptr). if you wanna access a member through a pointer 
	*/

	
	//you can also chain -> (and have to) if the member we are pointing at is also a pointer to another member e.g:
	Point a{ 1,2 };
	Point b{ 3,4 };
	Point c{ 5,6 };

	Triangle tr{ &a,&b,&c };
	Triangle* ptrtr{ &tr };
	std::cout << ptrtr->a->x << '\n'; 
	/*
	ptrtr is a pointer to the struct tr and now we want to access the member ' a ' which is a pointer  to a Point struct
	in the Triangle struct and from there we want to access ' x ' which is a member of of the Point struct
	*/

	//but lets see a similar example but this time the the member we are pointing at isnt a pointer but has the type of another struct e.g:
	Animal balu{ "balu",{4} };
	Animal* ptrb{ &balu };

	std::cout << (ptrb->paw).claws << '\n'; 
	/*
	ptrb->paw.claws would be correct too but the () helps for readability and as you can see bc the member that we are pointing at isnt a pointer just a member with 
	another struct type thats why we need to use the  member selection operator . instead of another -> 
	*/





	return 0;
}