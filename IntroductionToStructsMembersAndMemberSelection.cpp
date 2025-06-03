#include <iostream>

/*
In this lesson we introduce structs which is a program defined type which is used to bundle multiple variables into one type for example for information about an employee:
int id{};
int age{};
double wage{};

if we wanna pass down this employee we would need to pass all 3 variables down and also make sure that people know that these variables are related and everytime we
create a new employee we need to make 3 extra variables so instead we use struct:
*/

struct Employee // thats just a type definition so no object created here 
{
	int id{};   // we use ; instead of , that we used for enum
	int age{};
	double wage{};
	//these variables inside a struct are called data members
}; // dont forget ; at the end of a struct 



int main()
{
	//lets use our struct type employee:
	Employee jeff{}; //we defined a varibale of the type Employee named jeff
	Employee frank{}; // another employee with the Employee struct

	//so now how do we access the different variables inside the struct , we do that by the selection operator. right after the name of the variable e.g:
	jeff.age = 32; //we .age to acces age and give it the value 32 /btw no () required bc its not a helper function
	std::cout << jeff.age << '\n'; // print jeffs age without issues bc all operations work as usual unlike enums /.age required otherwise it wont compile you cant just pass jeff it wont print the whole struct


	//one of the biggest advantages of structs is  that we only need to creat one new struct variable name we dont need to worry about variables in the struct e.g:
	Employee joe{};
	joe.id = 14;
	joe.age = 23;
	joe.wage = 6000.0;

	Employee david{};
	david.id = 25;
	david.age = 50;
	david.wage = 12000.0;

	int totalAge(joe.age + david.age);
	std::cout << "Joe and David have lived " << totalAge << " total years.\n";

	if (joe.wage > david.wage)
	{
		std::cout << "Joe gets more money than David.\n";
	}
	else if (joe.wage < david.wage)
	{
		std::cout << "David gets more money than Joe.\n";
	}
	else
	{
		std::cout << "Joe and David earn the same\n";
	}

	david.wage += 5000;  //david got a raise 
	++joe.age;  //joe got older
	
	//see its very clear which member variable belong to which variable and that you can do basically any operation with them 

	return 0;
}