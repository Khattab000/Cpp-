#include <iostream>



int main()
{
/*
we learned a lot about fundemental data types like int but they dont cover everything and for more complex stuff there might be no type lets just say you wanna make
the user be able to type in and calculate two fractions you might consider doing smth like that :
*/
	int num1{};
	int denum1{};

	int num2{};
	int denum2{};

	char ignore{}; // this is just here to eat up the '/' that is inputted by the user 

	std::cout << "Please input two fractions to be multiplied to each other: ";
	std::cin >> num1 >> ignore >> denum1;
	std::cin >> num2 >> ignore >> denum2;
	std::cout << "The two fractions multiplied equal " << num1 * num2 << '/' << denum1 * denum2;


	/*
	This approach works but can get messy and error - prone if we want to handle fractions properly,
    since numerator and denominator are closely related and should be grouped together.
	*/

	/*
	To solve this, we use compound types that group related data into one unit. We used some of them already but here are all compound types:

	-Functions
	-C-Style Arrays
	-Pointer Types
	-Pointer to member types
	-Reference types
	-enumerated types
	-class types (struct,class,union)
	*/


	return 0;
}