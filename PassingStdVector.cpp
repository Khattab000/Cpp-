#include <iostream>
#include <vector>

//On this lesson we talk about passing std::vector

/*
An object of type std::vector can be passed to a function just like any other object but passing it by value results in an expensive copy being made 
instead we pass it with const reference to avoid the copy (btw when we use std::vector as function paramaeter, we have to explicitly specify the element type e.g 
std::vector<int> arr  )
*/

#if 0
//you might consider CTAD an do smth like that for multiple types  const std::vector& arr , but that wont work bc CTAD cant be used to infer function parameters
void passByRef(const std::vector<int>& arr) 
{
	std::cout << arr[0] << '\n';
}
#endif 

#if 0
//use template if you want your function to be able to take multiple element types instead of only being able to be used by one
template<typename T>
void passByRef(const std::vector<T>& arr)
{
	std::cout << arr[0] << '\n';
}
#endif

#if 0
//we can also create a function template  that will accept any type (as long as it has an overloaded []operator ) e.g:
template<typename T>
void passByRef(const T& arr)
{
	std::cout << arr[0] << '\n'; // the passed type need to have an overloaded []operator otherwise compilation error
}
#endif

//we can also create a function template  that will accept any type but using the abreviated function template by using the keyword auto e.g:
void passByRef(const auto& arr) //abreviated function template using the auto keyword 
{
	std::cout << arr[0] << '\n'; // the passed type still needs to have an overloaded []operator otherwise compilation error
}
/*
The(const T& arr) and the(const auto& arr) versions are good if we want to use other types too that arent std::vector like std::array or std::string
(both have overloaded[]operator) but be careful bc this can lead to a type that can be passed and compiles but doesnt make sense semantically leading to bugs.
*/


template<typename T>
void printElement3(const std::vector<T>& arr)
{
	std::cout << arr[3] << '\n';  // can be prune to error if an array is passed that doesnt have an index 3

	/*
	To avoid this issue we could  use assert on arr.size() which will cath those error in the debug build and bc std::vector::size() is a non constexpr function , we can 
	only do runtime assert here (so no static assert)

	A better option would be to avoid using std::vector in cases where you need to assert the array length and instead use a type that support constexpr like std::array, 
	with this you can use stati_assert on the lenght of the constexpr array (we cover this in the future).

	Or the best option is to avoid writing functions that rely on the user passing in a vector with a minimum lenght in the first place when possible.
	*/
}

template<typename T>
void printElement(const std::vector<T>& arr, int index)
{

}


int main()
{
	std::vector primes{ 2,3,5,7,11 };
	passByRef(primes);

#if 1 //reactivated after templates added now it should work too 
	std::vector dbl{ 7.7,5.6,1.5 };
	passByRef(dbl); // compilation error you are passing std::vector with different element types
#endif 

#if 0
	int i{ 8 };
	passByRef(i); //compilation error bc no overloaded [] operator
#endif

	std::vector vier { 1,2,3,4 };
	printElement3(vier);   //fine 

#if 0
	std::vector drei { 1,2,3};
	printElement3(drei);  //undefined behavior bc function prints index [3] and this is out of bounds for this array last valid index is [2] for this array 
#endif 

	std::vector v1{ 0, 1, 2, 3, 4 };
	printElement(v1, 2);
	printElement(v1, 5);

	std::vector v2{ 1.1, 2.2, 3.3 };
	printElement(v2, 0);
	printElement(v2, -1);

	return 0;
}