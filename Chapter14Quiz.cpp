#include <iostream>
#include <cmath>

//Question 1
class Point2d
{
	double m_x{ 0.0 };
	double m_y{ 0.0 };
public:
	Point2d() = default;

	Point2d(double x, double y)
		:m_x{ x }
		,m_y{ y }
	{ }

	void print() const
	{
		std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
	}

	double distanceeTo(const Point2d& x2) const
	{
		return std::sqrt((m_x - x2.m_x) * (m_x - x2.m_x) + (m_y - x2.m_y) * (m_y - x2.m_y));  // no need for doubel{} bc of implicit conversion
	}
};


//Question 2
class Fraction
{
	int m_numerator{ 0 };
	int m_denominator{ 1 };
	
public:
	
	explicit Fraction(int x = 0, int y = 1) //explicit here just in case that the default values reduce it to 1 argument only and as we stated use explicit when only 1 argument
		:m_numerator{x}
		,m_denominator{y}
	{ }

	void getFraction() //preferred as non member function we can define and intialize a Fraction in a single step but as a member function we need two steps first the creation of the Object and then calling this member function
	{

		std::cout << "Enter a value for numerator: ";
		std::cin >> m_numerator;
		std::cout << "Enter a value for denominator: ";
		std::cin >> m_denominator;
		std::cout << '\n';
	}
	Fraction multiply(const Fraction& f2) const
	{
		return Fraction {m_numerator * f2.m_numerator, m_denominator * f2.m_denominator }; //if using explicit on the constructor its important to specify bc type conversion or deduction cant be used
	}
	void printFraction() const //preferred as a non member function just so the interface of the class is less cluttered and if the implemementation of the class is changed we dont need to worry about print as long as the interface is the same
	{
		std::cout << m_numerator << '/' << m_denominator << '\n';
	}

};




int main()
{
	//Question 1
	Point2d first{};
	Point2d second{ 3.0,4.0 };
#if 0 
	Point2d third{ 4.0 }; //should not compile
#endif
	first.print();
	second.print();

	std::cout << "The Distance between the two points is: " << first.distanceeTo(second) << '\n';


	//Question 2
	Fraction f1{};
	f1.getFraction();
	Fraction f2{};
	f2.getFraction();

	std::cout << "Your fractions multiplied together: ";
	Fraction f3 { f1.multiply(f2) };
	f3.printFraction();
	// printFraction(multiply(f1, f2));

	return 0;
}