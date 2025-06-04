#include <iostream>

//In this lesson we will talk about passing and returning structs

struct Employee
{
	int id{};
	int age{};
	double wage{};
};

void printEmployee(const Employee& e)  // we use const reference to avoid making copies and we arent planning to change anything in the struct
{
	std::cout << "id: " << '\t' << e.id << '\n';
	std::cout << "age: " << '\t' << e.age << '\n';
	std::cout << "wage: " << '\t' << e.wage << '\n';
	std::cout << '\n';
}

struct Point3D
{
	double x{ 0.0 };
	double y{ 0.0 };
	double z{ 0.0 };
};
//The big advantage of returning structs are we are able to return multiple values , normally a function only returns one value 
Point3D getZeroPoint()   // we can just return struct 
{
#if 0
	Point3D temp{ 0.0,0.0,0.0 }; // create the struct
	return temp; // return the struct
	//we dont return by value not by reference to avoid dangnling reference but you could but you need to make the struct defined here static
#endif
	// you can also return a temporary struct which is actually preferred bc this  just a one liner and temp doesnt rly serve any purpose and might be confusing:
	return Point3D{ 0.0,0.0,0.0 };  

	/*
	As we already mentioned with temporary struct is that it deduces the type and in the functions case as long as the return type is named in the function we dont need to name it
	again e.g:
	return { 0.0,0.0,0.0 }; // no need for Point3D bc Point3D is in the function header but this is considered a implicit conversion

	we can go even further bc we only are passing zero values here we can just emit the zeros too e.g:
	return{}; // this value initializes all members instead
	
	*/

}



struct AdRev
{
	int adsWatched{};
	int percentageClicked{};
	double averageEarning{};
};


AdRev inputAdRevData()
{
	AdRev temp;
	std::cout << "Input how many ads where watched: ";
	std::cin >> temp.adsWatched;
	std::cout << "Input how much percentage of users clicked on an ad: ";
	std::cin >> temp.percentageClicked;
	std::cout << "Input the average earning per clicked ad: ";
	std::cin >> temp.averageEarning;
	return temp;
}

void printAdRevData(const AdRev& adrev)
{
	std::cout << "Ads Watched:              " << '\t' << adrev.adsWatched << '\n';
	std::cout << "Percentage who clicked:   " << '\t' << adrev.percentageClicked << "%\n";
	std::cout << "Average earnings per click" << '\t' << adrev.averageEarning << "$\n";
	std::cout << "Earnings today:           " << '\t' << (adrev.adsWatched * adrev.percentageClicked/100 * adrev.averageEarning) << "$\n";
	std::cout << '\n';
}


struct Fraction
{
	int numerator{};
	int denominator{};
};

Fraction inputFraction()
{
	Fraction temp{};
	std::cout << "Input a numerator: ";
	std::cin >> temp.numerator;
	std::cout << "Input a denominator: ";
	std::cin >> temp.denominator;
	return temp;


}

Fraction operator* (Fraction f1, Fraction f2)
{
	Fraction temp{ .numerator{f1.numerator * f2.numerator},.denominator{f1.denominator * f2.denominator} };
	return temp;
}
#if 0
constexpr Fraction multiply(const Fraction& f1, const Fraction& f2)
{
	return { f1.numerator * f2.numerator, f1.denominator * f2.denominator };
}
// other way to do it without overloading 
#endif 
void printFraction(const Fraction& f)
{
	std::cout << f.numerator << '/' << f.denominator << '\n';
}


int main()
{
	Employee jeff{ 4,34,50000.00 };
	printEmployee(jeff); 
	//big advantage of struct is that when passing them instead passing for example 3 different variables we can just pass the struct instead 
	
	Employee frank{};
	printEmployee(frank);
	//and if we want to add a member variable the function taking the struct doesnt need to change the amount of arguments it still takes the same argument

	//You can also a pass a temporary struct e.g:
	printEmployee(Employee{ 5,22,100.90 }); // to pass a temporary struct we just use the name of struct and then {} like we normally would initialize it /this way is preferred
	// you can also emit the name of the struct and it is deduced but this is not recommended but it works but we still need {} to make it workd:
	printEmployee({ 8,31,1000.20 }); //not preferred 
	//also keep in mind this only work where implicit conversion is allowed and bc its and rvalue non const reference cant bind with it or pointers wont work on it either 


	Point3D zero{ getZeroPoint() };

	if (zero.x == 0.0 && zero.y == 0.0 && zero.z == 0.0)
	{
		std::cout << "The point is zero\n";
	}
	else
	{
		std::cout << "The point is not zero\n";
	}


	AdRev advertisingData{ inputAdRevData() };
	printAdRevData(advertisingData);
	

	Fraction f1{ inputFraction() };
	Fraction f2{ inputFraction() };
	Fraction fresult{ f1 * f2 };
	std::cout << "Your fractions multiplied are ";
	printFraction(fresult);



	return 0;
}