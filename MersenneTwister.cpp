#include <iostream>
#include <random> // used for std::mt19937 and std::mt19937_64
#include <chrono> // for  std::chrone so we can use the systems clock for randomization

int main()
{
#if 0
	std::mt19937 mt{}; //Instantiate a 32 bit mersenne twister / if you put a number in there {} you can alter the seed 

	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << mt() << '\t';  // mt() like when we use a function

		if (count % 5 == 0)
		{
			std::cout << '\n';
		}
	}
#endif
	// With the code above we successfully made a random number generator but what if we wanna only use a certain range for that we need to use certain operators bc PRNGs cant do that themselves e.g:
#if 0
	std::mt19937 mt{static_cast<std::mt19937::result_type>(std::chrono::steady_clock::now().time_since_epoch().count())}; //Seeding with system clock /btw default value in curly braces normally is  5489u  
#endif
#if 0
	std::mt19937 mt{ std::random_device{}() }; // Seeding with random devices
#endif
	std::random_device rd{};  // seeding with random devices and seed_seq to give the seed more integers to work with and fill all 624 
	std::seed_seq ss{ rd(),rd(), rd(), rd(), rd(), rd(), rd(), rd() }; // get 8 integers of random numbers from std::random_devices 
	std::mt19937 mt{ ss }; // initialize the mersenne twister with std::seed_seq

	std::uniform_int_distribution die6{ 1,6 }; // with that we created a dice from 1 to 6

	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t';  // instead of mt() we use dice6() and mt name , so we still use the randomizer of mt but its probability is distributed in dice6() from one to 6

		if (count % 10 == 0)
		{
			std::cout << '\n';
		}
	}

	// the problem here tho is that its not rly random bc every time we run its the exact same so we need smth that changes the seed and two prominent ways to achieve that is 1. Systems Clock  2.Systems random device:

	/*
	1.Seeding with Systems Clock by using std::mt19937 mt{static_cast<std::mt19937::result_type>(std::chrono::steady_clock::now().time_since_epoch().count())}; we made mt use the 
	systems clock so now the result are random depending on the time this method tho has a small problem bc if you run it again in quick succession the result might be not too different bc how similar 
	the seed is so in some cases this way might be insufficient (some people use std::chrono::high_resolution_clock instead of steady_clock bc it uses a more granular clock  but unlike steady.clock 
	this clock can be changed and rolled back by the user which might be an issue so steady clock might be recommended in most cases
	*/


	/*
	2. Seeding with random devices is much shorter by using std::mt19937 mt{ std::random_device{}() }; basically asking the OS for a temporary pseudo random number you should prefer this way unless
	you know there are some issues with the Compiler or the OS that might make it so you get the same sequence over and over again but generally this  way is preferred over system clock
	*/


	/*
	Also important dont reseed your number generator to avoid poor random results so for example dont put the generator in a function bc everytime its calles its reseeded e.g:

	int getCard()
	{
	  std::mt19937 randomNumber {std::random_device{}()};
	  std::uniform_int_distribution card {1, 52)

	  return card (randomNumber);
	}

	int main()
	{
	  std::cout << getCard() << '\n';
	  return 0;
	  
	}

	so each time its called you reseed the generator and run the risk of less random results

	*/

	/*
	There is small issue tho the seed is only one integer so from the approximately 624 fillable integers (32 bit) only one is filled and for example the numer 42 will never appear first if we only input 
	one 32 bit integer to counter that and make it even more random we use std::seed_seq{} were we pass a few random numbers using the random device and with that it will fill the 624 more evenly make it
	more random e.g:
	*/

	
	return 0;
}