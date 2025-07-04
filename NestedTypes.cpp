#include <iostream>
#include <string>
#include <string_view>

//In this lesson we conver Nested members 
#if 0
enum class FruitType
{
	apple,
	banana,
	cherry,
};

class Fruit
{
	FruitType m_type{};
	int m_percentageEaten{ 0 };

public:
	Fruit(FruitType type)
		:m_type{type}
	{}

	FruitType getType()
	{
		return m_type;
	}

	int percentageEaten()
	{
		return m_percentageEaten;
	}

	bool isCherry()
	{
		return m_type == FruitType::cherry;
	}
};
//Doing this is fine but bc enum class FruitType is meant to be used together wiht class Fruit having it be seperated from the class leaves us infer how they are connected 
#endif 

//This is where nested types also called member types come in e.g
class Fruit
{
public: 
	/*
	We moved FruitType inside the class Fruit and made it public and not a enum class anymore this way we dont need to deal with the specifiers in the class bc we dont need 
	to worry about name conflicts bc the enum is inside the class BUT we still need to use the spcifier Type:: outside the class to access the things inside the enum.

	And the reason its defined at the top in this class  is that nested types need to be fully defined before they can be used so always define your nested types at the top 
	*/
	enum Type
	{
		apple,
		banana,
		cherry,
	};
private:
	Type m_type{};
	int m_percentageEaten{ 0 };

public:
	Fruit(Type type)
		:m_type{ type }
	{
	}

	Type getType()
	{
		return m_type;
	}

	int percentageEaten()
	{
		return m_percentageEaten;
	}

	bool isCherry()
	{
		return m_type == cherry;
	}
};

//clases can also contain nested typedefs or type aliases
class Employee
{
public:
	using IDType = int;

private:
	std::string m_name{};
	IDType m_id{};  // again inside the class we can just use IDType but outside we need the prefix so we need to use Employee::IDType
	double m_wage{};

public:
	Employee(std::string_view name, IDType id , double wage)
		:m_name{name}
		,m_id{id}
		,m_wage{wage}
	{ }

	const std::string& getName()
	{
		return m_name;
	}

	IDType getID()
	{
		return m_id;
	}
};


//Its also possible but very uncommon to define a class inside  a class making it a nested class e.g 
class Arbeiter
{
public:
	using IDType = int;
	class Printer
	{
		/*
		bc Printer is an nested class it doesnt have direct access to the "this" pointer meaning to access the private members directly BUT if we 
		pass him a Arbeiter object he can access the private members through that bc Printer is a member of Arbeiter so instead of m_name and m_id it becomes e.m_name and e.m_id
		*/
	public:
		void print(const Arbeiter& e) const
		{
			std::cout << e.m_name << " has the id: " << e.m_id << '\n';
		}
	};
private:
	std::string m_name{};
	IDType m_id{};
	double m_wage{};

public:
	Arbeiter(std::string_view name,IDType id, double wage)
		:m_name{name}
		,m_id{id}
		,m_wage{wage}
	{ }
};


//Lastly you can forward declare nested types e.g:

class Outer
{
public:
	class Inner1;   // okay: forward declaration of the nested type class inside the enclosing class
	class Inner1{}; // okay: definition of the forward declared nested type class inside the enclosing class

	class Inner2; // okay: forward declaration of the nested type class inside the enclosing class
};
class Inner2{}; // okay: definition of the nested type class outside of the enclosing class

#if 0 // but you cant forward declare a nested type prior to  the definition of the enclosing class e.g
class Outer; // okay can be forward declared bc its not a nested class 
class Outer::Inner1; // error cant forward declare a nested type BEFORE the definition of the enclosing class so keep that in mind too when working with multiple files

class Outer
{
public:
	class Inner1 {}; // declared and defined here
};
class Outer::Inner1; // okay but redundant since the nested type is already declared and defined as part of the Outer class definition
#endif

int main()
{
	Fruit apple{ Fruit::apple }; // we access apple not by Type::aplle but from Fruit::apple bc Type is now part of the class Fruit and its not an enum class anymore
	if (apple.getType() == Fruit::apple)
	{
		std::cout << "i am an apple\n";
	}
	else
	{
		std::cout << " i am not an apple\n";
	}
	
	Employee marik{ "Marik" ,1,6700 };
	Employee::IDType id{ marik.getID() }; //you need to use Employee:: if you want to use the type alias inside the class 
	std::cout << marik.getName() << " has the id " << id << '\n';

	const Arbeiter michael{ "Michael",2,789.0 };
	const Arbeiter::Printer p {}; //instantiated an object of the innter class
	p.print(michael);

	return 0;
}