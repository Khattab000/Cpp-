#if 1
// used with GlobalRandomNumbers.cpp file / also used in Chapter8Quiz.cpp
#pragma once
#include <chrono>
#include <random>


// This is a self seeding Mersenne Twister
namespace Random
{
	inline std::mt19937 generate()  // we use inline here to avoid ODR violations
	{
		std::random_device rd{};

		std::seed_seq ss{ static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),rd(),rd(),rd(),rd(),rd(),rd(),rd() };

		return std::mt19937{ ss };
	}

	// that is our global st::mt19937 object using the inline keyword meaning we only have one global instance for our whole program
	inline std::mt19937 mt{ generate() };

	//Get the min and max value to chose the random number from gotta be int tho called by Random::get(2,3) this returns int
	inline int get(int min, int max)
	{
		return std::uniform_int_distribution{ min,max }(mt);
	}


	//Get the min and max value typing can be anything numeric but the two variables gotta be the same type called by Random::get(2.1,1.3) and this returns the type of both
	template <typename T>
	T get(T min, T max)
	{
		return std::uniform_int_distribution<T>{min, max}(mt);
	}

	//Get the min and max value typing can be anything and the two variables also can be diffrent called by Random::get<double>(1,1.3) and this returns a double 
	template<typename R, typename S, typename T>
	R get(S min, T max)
	{
		return get<R>(static_cast<R>(min), static_cast<R>(max));
	}
}
#endif