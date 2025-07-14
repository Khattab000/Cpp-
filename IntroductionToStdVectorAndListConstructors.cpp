#include <iostream>
#include <vector> // for std::vector


//On this lesson we learn about std::vector and list constructors

struct Foo
{
#if 0
	std::vector<int> v0( 8 ); // compiler error direct initialization () not allowed for member default initializers
#endif
	//when providing a default inititializer for a member class type we need to use either copy = or list{} initialization also CDAT not allowed so <> has to be used for the type
	//but there is a way to get the desired result of lenght 8 and all elements zero initialized e.g:
	std::vector<int>v0{ std::vector<int>(8) }; //creates a vector with length 8 and its elements zero initialized and initializes v0 with it through list initialization
};

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

	/*
	But lets say we want to create a vector that can take 10 numbers how would we do that ? We could put it in placeholders but thats too much work and inefficient, instead we use
	an explicit constructor std::vector<>(std::size_t) that takes a single std::size_t that determines the length of the vector e.g:
	*/
	//this constructor needs to be called with () and also you need to specify the the type so <> is also mandetory
	std::vector<int> p1(10); //zero initialized (default constructor for class types) a vector containing 10 elements (can hold 10 int elements)

	p1[0] = 2;
	std::cout << p1[0]; 

	//so you might ask yourself why we need to use () (direct initialization) to make an empty vector with a certain size here is an example:
	std::vector<int> p2{ 10 }; //soo what does that do ? it either could be a vector with a length 1 and the element is 10 or length 10 with elements zero initialized ?
	/*
	In other cases this would lead to an ambiguous match and compilation error but C++ has a special rule that if a initilaizer is non empty and list initialized then the list
	initialization {} takes precedence over std::vector<>(std::size_t) so in the above example std::vector<int> p2{ 10 }; its a a vector with a length 1 and the element is 10

	so to recap:
	std::vector<int> p1{};   // default constructor is called / creates empty vector
	std::vector<int> p1{7};  // matching list constructor is called / length 1 with the element 7
	std::vector<int> p1(7);  // std::vector<T>(std::size_t) constructor called / length 7 with elements zero initialized 
	std::vector<int> p1(7,5);// similar to std::vector<T>(std::size_t) constructor called but this one takes two parameters length and what to fill the elements with instead of 
	                            zero inititialization / length 7 with all elements initialized to 5

	Lets look at some examples of initializing vectors e.g:
	*/
#if 0
	std::vector<int> v1 = 10; //copy initialization wont match any constructor in this case so compilation error
#endif 

	std::vector<int> v2(10); // direct initialization so doesnt match list constructor meaning std::vector<T>(std::size_t) constructor called

	std::vector<int> v3 = { 10 }; //interpreted as initializer list matches list constructor 
	std::vector<int> v4({10 });   //interpreted as initializer list matches list constructor 

	std::vector<int> v6{};         //empty initializer list matches default constructor
	std::vector<int> v7 = {};      //empty initializer list matches default constructor

	/*
	You can assume that each container has a list constructor but if you have a class that doesnt have one and adds one later then be aware of possible changes of which 
	constructor is called for object initialization.

	Tip: Use direct initialization () when constructing smth that has a list constructor with initializers that are not element values
	*/


	/*
	There are some special rules when std::vector is a member of a class type look above to the struct Foo e.g:
	*/

	const std::vector<int> prime{ 2,3,5,7,11 }; //you can also make a vector const this has to be initialized and cannot be modified and its elements are treated as if they were const
	//std::vector<const int> prime is disallowed the elements get the const from the container

	//One big disadvantage of std::vector is that it cant be made constexpr if you still want constexpr you can use std::array (we cover that in the future)


	//Small Quiz:
	std::vector squares { 1,4,9,16,25 };

	std::vector<double> high_temp(365);

	std::cout << "Enter 3 integers: ";
	std::vector<int> calc(3);
	std::cin >> calc[0] >> calc[1] >> calc[2];
	std::cout << "The sum is: " << calc[0] + calc[1] + calc[2] << '\n' << "The product is: " << calc[0] * calc[1] * calc[2] << '\n';

	return 0;
}