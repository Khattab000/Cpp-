#include <iostream>

struct Smth
{
	int x;   // bad no initialization value
	int y{}; // value intitialized by default /most likely 0
	int z{7};  // explicit default value
	
};



int main()
{
	Smth smth; //smth.x is uninitialized not good can lead to issues, smth.y is 0 and smth.z is 7

	Smth smth2 { 2,3,4 }; // even tho smth2.z has a default value , our initialization takes precedence so it smth2.z is 4 now / so no default are used when we pass a value for them


	Smth smth3{}; //in this case smth3.x gets value initialized so smth3.x is zero , smth3.y and smth3.z just use their default values of 0 and 7
	// always prefer smth3{} over smth;  to make sure everything is initiallized 



	return 0;
}