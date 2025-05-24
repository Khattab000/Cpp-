#include <iostream>
#include <typeinfo> // for typeid()

/*
Now we talk about the different rules of diffrent types of operands.
Operation where the operands need to be the same:
binary +,-,*,/,%,<,>,<=,>=,==,!=,&,^,|

conditional operator ?: (exluding the condition bc the condition is always bool)
*/

/*
Now we go into the general rules:
the compiler ranks the the types from long double to int which is the lowest rank

Step 1: 
If one operand is integral and the other is floating type point the 
integral is converted to floating , otherwise if its a small integral type like
char, short or bool these get promoted to int unsigned int

Step 2:
If one operand is signed and the other unsigned special rules apply:
- If the rank of the unsigned operand is greater or equal than the rank
  of the signed operand, the signed operand converts to the type of the
  unsigned operand
- If the type of the signed can represent all the values of the type of the 
 unsigned operand , the type of the unsigned operand converts to the type 
 of the signed
- Otherwise both operand are converted to the corresponding unsigned type
  of the signed operand

Otherwise the operand with the lower rank gets promoted to the rank of higher rank operand.


*/
int main()
{
	int i{ 2 };
	std::cout << typeid(i).name() << '\n'; //shows us the name of the type of i
	double d{ 3.5 };
	std::cout << typeid(d).name() << '\n';

	std::cout << typeid(i + d).name() << ' ' << i + d << '\n'; // show us the type of i + d
	// prints double 5.5

	short a{ 4 };
	short b{ 5 };
	std::cout << typeid(a + b).name() << ' ' << a + b << '\n'; // show us the type of a + b
	//prints int 9 bc both operands got promoted bc they where small ones 

	std::cout << typeid(5u - 10).name() << ' ' << 5u - 10 << '\n';
	/*
	this surprisingly prints unsigned in 4294967291 
	bc of the conversion rule the int operand got converted to unsigned int
	and since the value -5 is out of range it overflows so we got an unexpected
	result
	*/


	std::cout << std::boolalpha << (-3 < 5u) << '\n';
	/*
	you would expect it to print true but bc the signed operand
	got converted to unsigned bc of the conversion rule it prints false
	bc -3 overflows
	*/

	/*
	We will cover in future std::common_type and std::common_type_t 
	to find out what the common type of two types is and where that is useful
	*/
	return 0;
}