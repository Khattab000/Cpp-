#include <iostream>

/*
Lets say you have a function that adds two integers but then you want one that adds double and then you want one that does it with 3 instead of 2 numbers
so you gotta write a function for each one of them and also give them diffrent names and then you gotta make sure you remember the naming convention used 
and use the correct function all this is a bit too complicated, thats where function overloading comes in. Basically you can name all your functions the same
as long as the parameters are diffrent (or if there is another way for the compiler to diffrentiate them) so now you dont need to bother about remembering the names of 
all the diffrent add functions and the compiler picks the one who is most suited for the paramaeters you put in (but if it cant diffrentiate then this would lead to a compiler error) e.g:
*/


int add(int x, int y)
{
	return x + y;
}

double add(double x, double y)
{
	return x + y;
}

int add(int x, int y, int z)
{
	return x + y + z;
}

#if 0
int add(int x, int y) // this would lead to an error bc it cant diffrentiate 
{
	return x * y;
}
#endif
int main()
{
	std::cout << add(1, 2) << '\n';      // calls int add(int,int)
	std::cout << add(1.5, 1.7) << '\n';  // calls double add(double,double)
	std::cout << add(1, 1, 4) << '\n';    // calls int add(int,int,int)
	return 0;
}