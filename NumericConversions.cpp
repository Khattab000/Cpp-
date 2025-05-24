#include <iostream>
#include <iomanip> // for std::setprecision()

int main()
{
#if 0
	// There are 5 Types of numeric conversions (expluding promotions)

	//1.converting integral to another integral:
	short s = 3; // int to short
	long l = 3; // int to long
	char ch = s; // short to char
	unsigned int u = 3; // int to unsigned int

	//2.converting floating point typed to another floating point type:
	float f = 3.0; // double to float 
	long double ld = 3.0; // double to long double

	//3.converting floating point type to any integral typed
	int i = 3.5; // double to int (is not possible in bracket initialization)

	//4.converting integral type to any floating type
	double d = 3; // int to double

	//5.converting integral type or floating type to bool
	bool b1 = 3; // int to bool 
	bool b2 = 3.5; // double to bool

#endif
	/*
	Unlike numeric promotions which are always value preserving whichffdf
	means its safe but numeric conversion on the other hand isnt many 
	numeric conversions are unsafe conversions its split in 3 diffrent
	types:
	*/

	//1.Value preserving conversions like int to long and short to double these are safe numeric conversions:
	int n{ 5 };
	long l = n; // is safe produces the value 5
	short s{ 5 };
	double d = s; // okay produces the double 5.0
	//these conversions can alway be reverted without any issues:

	n = static_cast<int>(static_cast<long>(3)); // convert int 3 to lock and back
	std::cout << n << '\n'; // 3
	char c = static_cast<char>(static_cast<double>('c')); // convert char 'c' to double and back
	std::cout << c << '\n'; // c

	//2.Reinterpretive conversion are unsafe numeric conversions so technically no data loss so the bits stay the same but the value changes so if you revert you got the original value back like signed int to unsigned int:
	int n1{ 5 };
	unsigned int u1 = static_cast<unsigned int>(n1); //okay will be converted with the same value / you need to use static_cast<>()
	int n2{ -5 }; 
	unsigned int u2 = static_cast<unsigned int>(n2);// bad will be converted with value that its outside of signed int range bc of overflow (bits stay the same so when reverting back we get -5) / you need static_cast<>()

	int u = static_cast<int>(static_cast<unsigned int>(-5));
	//convert '-5' to unsigned and back
	std::cout << u << '\n'; // -5


	//3.Lossy conversions  are unsafe numeric conversions where data might be lost during the process like double to int or double to float (also cant be reverted properly the value will be diffrent then the initial value) e.g:
	int i = 3.0; // okey will be converted to value 3 and value gets preserved
	int j = 3.5; // bad bc data will be lost and will convert to value 3 (0.5 lost)

	float f = 1.2; // okay thats fine double to float
	float g = 1.23456789; // bad, data will be lost double will be converted to float 1.23457 (precision lost)

	double h{ static_cast<double>(static_cast<int>(3.5)) }; // convert double 3.5 to int and back
	std::cout << h << '\n'; // prints 3 bc 0.5 was lost

	double t{ static_cast<double>(static_cast<float>(1.23456789)) }; // conver double 1.23456789 to float and back
	std::cout << t << '\n'; // prints 1.23457 bc of lost precision

	std::cout << static_cast<long long>(static_cast<double>(10000000000000001LL))<<'\n';
	// this returns 10000000000000000 basically the last digit being lost bc the full range of long long cant be represented in double so converting back will lose a digit


	//In general unsafe conversions should be avoided but there are some cases where its okey e.g signed int to unsigned int if you make sure its positive or int to bool where technically there is data loss but its fine bc the bool is gonna be 0 or 1 (false or true) anyways

	// In all cases, converting a value of type to another type that cant hold the range will lead to a result that is unexpected e.g:
	int o{ 30000 };
	char m = o; //chars range -128 to 127 so this will lead to overflow
	std::cout << static_cast<int>(m) << '\n'; // prints 48 

	// Ofc you can convert from a larger type to smaller type if you make sure that the number that is converted is still in the range e.g:
	int b{ 2 };
	short r = b; //convert int to short
	std::cout << r << '\n'; // prints 2 as expected

	double q{ 0.1234 };
	float e = q;
	std::cout << e << '\n'; // prints 0.1234 as expected


	// in the case of floating point values rounding issues may occur in the smaller types e.g:

	float z = 0.123456789; //has 9 significant digits but float only can hold 7
	std::cout << std::setprecision(9) << z << '\n'; // will print 0.123456791 bc of rounding issues bc normally it can only hold 7 signifant digits


	int h{ 10 };
	float d = h;
	std::cout << d << '\n'; // this prints 10 which is as expected and this is fine

	int t = 3.5;
	std::cout << t << '\n'; // prints 3 and 0.5 is lost

	return 0;
}