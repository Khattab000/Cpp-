#include <iostream>
#include "Vector3d.h" //the order of Vector3d.h and Point3d.h doesnt matter 
#include "Point3d.h"



#if 0
/*
On this lesson we learn about Friend classes and friend member functions which are similar to friend function where both can access the private and protected 
members of another class e.g:
*/

class Storage
{
	int m_nValue{};
	double m_dValue{};

public:
	Storage(int nValue,double dValue)
		:m_nValue{nValue}
		,m_dValue{dValue}
	{ }

	friend class Display; // make the Display class a friend of the class Storage
};


class Display
{
	bool m_displayIntFirst{};
public:
	Display(bool displayIntFirst)
		:m_displayIntFirst{ displayIntFirst }
	{ }

	/*
	Bc Display is a friend of Storage, it can access the private members of Storage like .m_dValue / but keep in mind Display has no access to "this" pointer from Storage 
	so an object needs to be passed / And just bc Display is a friend of Storage doesnt mean Storage is a friend of Display meaning Storage doesnt have access to the private
	members of Display to make two classes be friends of each other then both classes need to declare the other as friend

	Also Class friendships are not transitive meaning if class A is a friend of B and class B is a friend of C that does not mean that that class A is a friend of C.
	Class friendships are also not inherited if class A make B a friend , classes derived from B are not friends of A.

	(btw for friend declaration also acts as the class being forward declared thats why its fine to friend the class before its definition?
	*/
	void displayStorage(const Storage& storage)
	{
		if (m_displayIntFirst)
		{
			std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
		}
		else
		{
			std::cout << storage.m_dValue << ' ' << storage.m_dValue << '\n';
		}
	}

	void setDisplayIntFirst(bool b)
	{
		m_displayIntFirst = b;
	}


};
#endif 

// We can also make a single member function a friend instead of the entire class e.g:

class Storage; // we need this forward declaration so we can reference Storage in our function parameter 

//class Display moved above Storage and the forward declaration of Display is removde
class Display
{
	bool m_displayIntFirst{};
public:
	Display(bool displayIntFirst)
		:m_displayIntFirst{ displayIntFirst }
	{
	}

	void displayStorage(const Storage& storage); // forward declaration and moved outside below the full definition of Storage os .m_nValue and .m_dValue can be accessed

	void setDisplayIntFirst(bool b)
	{
		m_displayIntFirst = b;
	}


};


class Storage
{
	int m_nValue{};
	double m_dValue{};

public:
	Storage(int nValue, double dValue)
		:m_nValue{ nValue }
		, m_dValue{ dValue }
	{
	}
	// make the Display::displayStorage() a friend of Storage
	friend void Display::displayStorage(const Storage& storage); //error bc Storage hasnt seen the full definition of class Display and in this case forward declaration wont cut it
	//but we can easily fix that by defining Display first instead of the forward declaration
};


void Display::displayStorage(const Storage& storage)
{
	if (m_displayIntFirst)
	{
		std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n'; // error to access .m_nValue the full the definition of Storage needs to be seen 
	}
	else
	{
		std::cout << storage.m_dValue << ' ' << storage.m_dValue << '\n'; // works now after it being removed outside and after the full defintion of Storage
	}
}
//With all this now only Display::displayStorage() is a friend of Storage and has access to its private members 


//Quiz Time:
#if 0
class Vector3d;

class Point3d
{
private:
	double m_x{};
	double m_y{};
	double m_z{};

public:
	Point3d(double x, double y, double z)
		: m_x{ x }, m_y{ y }, m_z{ z }
	{
	}

	void print() const
	{
		std::cout << "Point(" << m_x << ", " << m_y << ", " << m_z << ")\n";
	}

	void moveByVector(const Vector3d& v);
};


class Vector3d
{
private:
	double m_x{};
	double m_y{};
	double m_z{};

public:
	Vector3d(double x, double y, double z)
		: m_x{ x }, m_y{ y }, m_z{ z }
	{
	}

	void print() const
	{
		std::cout << "Vector(" << m_x << ", " << m_y << ", " << m_z << ")\n";
	}

	friend void Point3d::moveByVector(const Vector3d& v);
};


void Point3d::moveByVector(const Vector3d& v)
{
	m_x += v.m_x;
	m_y += v.m_y;
	m_z += v.m_z;
}


#endif

int main()
{
	Storage storage{ 3,5.7 };
	Display display{ false };

	display.displayStorage(storage);
	display.setDisplayIntFirst(true);
	display.displayStorage(storage);



	Point3d p{ 1.0, 2.0, 3.0 };
	Vector3d v{ 2.0, 2.0, -3.0 };

	p.print();
	p.moveByVector(v);
	p.print();
	
	/*
	Conclusion: Class forward declaration satisfy references to the class but however accessing members of a class requires that the compiler sees the full class defintion firts
	(Even tho this looks like a pain to do all that there is an easier option by just putting the class definitions in seperate header files and their member functions in
	corresponding cpp files. That way all of the class definitions would be available in the cpp files and no rearanging of classes or functions is necessary.)
	*/

	return 0;
}