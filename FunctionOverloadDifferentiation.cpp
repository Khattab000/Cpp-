#include <iostream>

/*
In the prior lesson we started talking about function overloading now we get into details how you need to differentiate them so the compiler doesnt issue a compiler warning e.g
- Number of parameters (yes counts): 
int add(int,int);
int add(int,int,int);


- Type of parameters (yes counts):
int add(int,int);
double add(double,double);
double add(int,double);
double add(double,int);

- return type (no this doesnt count as differentiation):
double print();
int print();

so if you called it it would look like this
print() // so the compiler doesnt know which one to pick in this case just give the functions unique names

- different type alliases (or typedef) of the same type (no this doesnt count as differentiation):
typedef int Max;
using Mey = int;
void print(int);
void print(Max);
void print(Mey);
//compiler error bc no differentiation

- const or volatile functions (yes even if paramterts are the same) // here we are talking about the function being const not the parameters bc the parameters being const is not differentiation
const void print(int); 
void print(int); // this is fine and counts as differentiations to the const version
void print(const int) // compiler error no differentiation here

- ref-qualifiers (yes)

- ellipsis in the parameter (yes)
int read(int x, int y);
int read(intx,...); // ellipsis counts as differentiation / we will cover later on what an ellipsis even is
*/




int main()
{
	return 0;
}