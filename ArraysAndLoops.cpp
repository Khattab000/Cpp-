#include <iostream>
#include <vector>
#include <limits>
#include<string_view>
#include<string>

using namespace std::literals;
/*
Now combining templates,loops and arrays so we can operae on a container
of elements regardless of the element type or number of elements in the
container
*/
template<typename T>
T calculateAverage(const std::vector<T>& arr)
{
	std::size_t length{ arr.size() };
	T average{ 0 };
	for (std::size_t index{ 0 }; index < length; ++index) //< not <= bc the latter leads to out of bounds index
	{
		average += arr[index];
	}

	average /= static_cast<int>(length); //length to int instead of T bc the count is a integral value
	return average;
}

template<typename T>
void printArray(const std::vector<T>& arr)
{
	std::size_t length{ arr.size() };
	for (std::size_t index{ 0 }; index < length; ++index)
	{
		std::cout << arr[index] << ' ';
	}

	if (arr.size() > 0)
	{
		std::cout << '\n';
	}
}

template<typename T>
void inArray(T input, const std::vector<T>& arr)
{
	std::size_t length{ arr.size() };
	for (std::size_t index{ 0 }; index < length; ++index)
	{
		if (arr[index] == input)
		{
			std::cout << "The number " << input << " has index " << index << '\n';
			return;
		}
	}
	std::cout << "The number " << input << " was not found\n";
}

template<typename T>
T askForNumber(T low,T high) //passing low and high allows the compiler to infer the type of the input it cant do that without arguments
{
	T input{};
	do
	{
		std::cout << "Enter a number between " << low << " and " << high << ": ";
		std::cin >> input;
		if (std::cin.fail())
		{
			std::cin.clear();
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (input > high || input < low);

	return input;
}

template<typename T>
T findMax(const std::vector<T>& arr)
{
	std::size_t length{ arr.size() };
	if (length <= 0)
	{
		return T{}; //no name required bc its temporary 
	}

	T max{arr[0]};
	
	for (std::size_t index{ 1 }; index < length; ++index)
	{
		if (max < arr[index])
		{
			max = arr[index];
		}
	}

	return max;
}


void fizzbuzz(int num)
{
	const std::vector div{ 3,5,7,11,13,17,19 };
	const std::vector words{ "fizz"sv,"buzz"sv,"pop"sv,"bang"sv,"jazz"sv,"pow"sv,"boom"sv};

	std::size_t length{ div.size() };
	bool p{ false };
	for (int i{ 1 }; i <= num; ++i) 
	{
	
		for (std::size_t index{ 0 }; index < length; ++index)
		{
			if (i % div[index] == 0)
			{
				std::cout << words[index];
				p = true;
			}
		}
	}
	if (!p)
	{
		std::cout << num;
	}
	std::cout << '\n';
}


int main()
{
	std::vector testScore{ 84,92,76,81,56 };
	std::size_t length{ testScore.size()};

	int average{ (testScore[0] + testScore[1] + testScore[2] + testScore[3] + testScore[4]) / static_cast<int>(length) };
	std::cout << "The class average is: " << average << '\n';
	/*
	So this is better than having each test score be their own variable
	but its still a lot of typing to access each individual testScore so
	we need a way to access each array element without listing them 
	explicitly
	*/

	//we use a for loop instead so we dont need to list each array element explicitly
	int average2{ 0 };
	for (std::size_t index{ 0 }; index < length; ++index)
	{
		average2 += testScore[index];
	}

	average2 /= static_cast<int>(length); //calculate the average 
	std::cout << "The class average is: " << average2 << '\n';

	std::vector price{ 3.4,7.6,8.9 };
	auto average3{ calculateAverage(price) };
	std::cout << "The price average is: " << average3 << '\n';

	/*
	So what are the most commom use cases for arrays with loops:
	-calculate new value based on the value of existing elements like
	 average value
	-search for an exisiting element like highest value 
	-operate on each element like output each element
	-reorder the elements like sort the elements in ascending order
	 (this one a bit more tricky we cover that in a future chapter)
	*/

	std::vector arr5{ 4,6,7,3,8,2,1,9 };
	std::size_t length5{ arr5.size() };
	for (std::size_t index{ 0 }; index < length5; ++index)
	{
		std::cout << arr5[index] << ' ';
	}
	
	if (arr5.size() > 0)
	{
		std::cout << '\n';
	}


	auto input{askForNumber(1,9)}; //we can use auto here bc we are passing arguments which helps the compiler infer the type
	printArray(arr5);
	inArray(input, arr5);


	std::vector arr7{ 3.5,6.7,9.9,1.2 };
	auto input2{ askForNumber(1.0,9.9) };
	printArray(arr7);
	inArray(input2, arr7);


	std::vector data1{ 84, 92, 76, 81, 56 };
	std::cout << findMax(data1) << '\n';

	std::vector data2{ -13.0, -26.7, -105.5, -14.8 };
	std::cout << findMax(data2) << '\n';

	std::vector<int> data3{ };
	std::cout << findMax(data3) << '\n';

	for (int i{ 0 }; i <= 21; ++i)
	{
		fizzbuzz(i);
	}
	

	return 0;
}