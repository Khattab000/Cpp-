#include <iostream>

//In this lesson we discuss how structs are initialized 


#if 0
//Data members need to be initialized bc they arent initialized by default e.g:
struct Employee
{
	int id;   // no initialization here
	int age;
	double wage;
};
#endif

//aggregate data type is any type that can contain multiple data members like structs or arrays



struct Employee
{
	int id{};
	int age{};
	double wage{};
	//btw if you add new member variables to a struct at a later point alway put the new variable at the bottom to avoid mistakes for variables already using the struct and messing up the order 
};

struct Worker
{
	int id{};
	int age{};
	double wage{ 76000.0 }; // this is a default value
	double wammy{};
};


//lets use operator overload to print the full struct of employee
std::ostream& operator<< (std::ostream& out, Employee& e)
{
	out << "id: " << e.id << " age: " << e.age << " wage: " << e.wage;   //added "id: " and others instead of ' ' to be more descriptive
	return out;
}


int main()
{
#if 0
	Employee jeff;  //no initialization here either
	std::cout << jeff.age << '\n'; //this will lead to undefined behavior
#endif
	/*
	either the data members in Employee need to be initialized or jeff needs to be initialized so it also initializes the members but if both arent initialized 
	this will lead to an compilation error
	*/


	//so how do we initialize a variable with a struct type , in this case we use the aggregate initialization and there are two ways to do so e.g:
	Employee daphne = { 1,32,60000.0 }; // copy list initialization 
	Employee jekyl{ 3,20,50000.0 }; // list initialitation (preferred) /3 is id , 20 is the age, 50000.0 is the wage
	//we could also use () but this is not recommended

	//lets see what happens when we initialize a struct type but dont initialize every member variabele e.g:
	Worker mike{ 5,38 };  
	/*
	with this we only passed values for.id and .age but what about the other two ? compiler looks first for default values which .wage has so its initialized with that 
	and if there is none like with .wammy it gets initialized with 0 or in the .wammy case with  0.0 but all in all this allowed and will compile
	*/
	Worker steve{}; //so this is also completely fine everything that has a default gets the default and the rest ar initialized with 0 or 0.0

	Employee dan{};
	std::cout << daphne << '\n'; // with the operator overload this should work now and should print id , age and wage 
	std::cout << dan << '\n'; //prints 0 0 0 bc we didnt give dan any value neither does Employee have any default values 


	//ofc struct type can be const or constexpr and just like const variables they need to be initialized
	const Employee han{ 2,56,80000.0 };
	constexpr Employee fan{};


	//lets say tho you want to initialize a struct variable which has 3 member variables and you only want to pass values to the first and third one how do you do that ?
	//there are two ways ot called designated initializer e.g:

	Employee sheldon{ .id{1},.wage{4000000.0} }; //this is fine and recommended /this way we passed value to the first and last member variable but not the second which is .age
	Employee lenord{ .id = 2,.wage = 2.0 }; // this also fine but not recommended
#if 0
	Employee Rajesh{ .wage{12.0},.id{7} }; // not fine and compilation error you need to stay in order of declaration in the structn
#endif
	//we wouldnt recommend using it bc  aggregate initialization should be enough most of the time but if you need like in the case above use it it just clutters the code 


	//we also showed in the past that you can change the value of member functions after initialization e.g:
	Employee Tung{};
	Tung.id = 2;
	//But what if we want to change multiple things this is also possible : 
	Tung = { Tung.id,4,90000.0 }; // here we changed .age and .wage , but bc we didnt wanna change .id and we passed Tung.id so it stays the same and we need to pass smth for id otherwise compilation error
	//the same also goes for if we wanna skip smth and use designated initializer 
	Tung = { .id = Tung.id,.wage = 800000.0 }; // we wanted .id to stay the same thats why we passed Tung.id again otherwise it would still work but .id would be initialized with 0 and .age is initialized with 0 now but its okey
	// use {} for initialization and = for changes afterwards



	//you can also initialize a varaible with a struct type with another variable of the same struct type e.g:
	Employee rick{ 4,21,99000.0 };  

	Employee morty{ rick }; //initialized with the value 4,21,99000.0 /you could also do Employee morty = rick or Employee morty(rick) but the one we used is recommended

	std::cout << rick << '\n' << morty << '\n';  //both print the same values 



	return 0;
}