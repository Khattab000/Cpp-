#include <iostream>
#include <vector> // for std::vector


//On this lesson we learn about std::vector and list constructors

int main()
{
	// vector implements an array that is containining 0 in elements / <int> is optional tho bc CTAD (Class Template Argument Deduction) could deduce the type too
	std::vector<int> empty{}; 

	std::vector<int> primes{ 2,3,4,7 }; // vector containing 4 int elements
	std::vector vowels{ "a","e","i","o","u" }; // CDAT deduced the type so no need for <> (preferred way) / vector containing 5 char elements 

	/*
	So lets talk more about how exactly the initialization works.
	It similar to the struct aggregate initialization syntax wise where we input the values seperated bc a comma e.g: {1,2,3,4,...}.
	But container typically have a special constructor called list constructor which does some additional stuff during the initialization. The list constructor does three things:
	- Ensures the container has enough storage to hold all the initialization values (if needed)
	- Sets the length of the container to  the number of elemens in the initializer list (if needed)
	- Initializes the elements to the values in the initializer list (in sequential order)

	So use list initialization wiht a initializer list of values to construct a container with htose element values

	*/

	/*
	we access individual elements with the index starting with 0 we put the index in the subscript []operator which returns a reference to the element we
	then can access or insert a value and do operations with :
	*/
	std::vector grimes{ 2,3,9,11,12,18 };
	std::cout << "The first grimes is " << grimes[0] << '\n';  // 2
	std::cout << "The second grimes is " << grimes[1] << '\n'; // 3
	std::cout << "The last grimes is " << grimes[5] << '\n';   // 18
	std::cout << "The sume of the grimes is " << grimes[0] + grimes[1] + grimes[2] + grimes[3] + grimes[4] + grimes[5] << '\n'; // 55
	/*
	By using arrays we no longer have to define 6 differently named variables to hold 6 values of the same type instead we can define a single array that holds
	those values and we can access them via the index
	*/

	/*
	When using index with the [] operator its important to keep in mind first that to never use negative index and also to keep in mind to not pick an index out of bounds.
	The index needs to be between 0 and N-1 (where N is the length of the array). The [] operator doesnt to  any bounds checking so it wont stop you but this will lead to 
	undefined behavior if you pick an index out of bounds (also dont forget there is no index N bc if you use N then it would be one after the last that why the last index is 
	N-1).
	*/
#if 0
	std::cout << grimes[9] << '\n'; //undefined behavior bc index out of bounds
#endif

	//As we stated earlier the elements are saved contiguous in memory with no gaps lets look at the first three elements of the grimes array e.g:
	std::cout << "The size of an int is " << sizeof(int) << " Bytes.\n"; // 4 Bytes
	std::cout << &(grimes[0]) << '\n';  // 000001EC092D0A30
	std::cout << &(grimes[1]) << '\n';  // 000001EC092D0A34
	std::cout << &(grimes[2]) << '\n';  // 000001EC092D0A38
	/*
	As you can see each of them in their index order are 4 Bytes from each other and each are int so as you can see there are no gaps between them this means there is no Overhead
	per element like: a pointer for each element, size info per element and metadata to track properties. That means its only raw data which means the compliler can quickly 
	calculate the address of any element in the array making them very efficient.

	Arrays are also one of the few container types that allow for random access which means any element in the container can be accessed directly unlike other container type 
	where you need to go through the container with sequential access where elements need to be accessed in a certain order. Random access it typically the more efficient 
	and preferred option and make arrays easy to use which is why arrays are preferred over containers.
	*/

	return 0;
}