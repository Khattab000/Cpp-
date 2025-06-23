#include <iostream>
#include <string>
#include <string_view>

//In this lesson we cover delegating constructors which helps us reduced redundancy when having multiple constructor which have similar or the same code 

class Employee
{
	std::string m_name{"???"};
	int m_id{0};
	bool m_isManager{ false };
public:
#if 0
	Employee(std::string_view name, int id)  //Employees must have a name and id
		:m_name{ name }
		, m_id{ id }
	{
		std::cout << "Employee " << m_name << " created.\n";  // the same print statement as below
		//btw on another note ist not recommended for your constructor to print smth other than for debugging purposes bc so you cant create an object in cases where you dont wanna print
	}
#endif
#if 0
	Employee(std::string_view name, int id, bool mng) // optionally they can be a manager
		:m_name{ name }
		, m_id{ id }
		, m_isManager{mng}
	{
		std::cout << "Employee " << m_name << " created.\n"; // the same print statement as above 
	}
#endif
	/*
	what we could do to decrease redundancy for the two print statements is to make a private function that prints out that 
	message and then make both call it but this only changed the redundand print statements to redundand functions calls and there is also the
	two constructors initializing both name and id so is there a better way ? YES there is.
	
	Some would think that we maybe could call the other constructor within the constructor like this e.g:
	*/
#if 0
	Employee(std::string_view name, int id, bool mng) // optionally they can be a manager
		:m_isManager{ mng } // only m_isManager the rest will be theoretically done by calling the other constructor
	{
		//doesnt work as expected
		Employee(name, id); // call the other constructor which theoretically should initialize name and id and print the message /creates a temporary object bc its inside a function body
		//bc its in the function body and its like calling a function we use ()
	}
#endif
#if 0
	/*
	the reason the above approach doesnt work is bc once the member list iniialization is exectued the initialization is completed so whatever happens in the constructor 
	body is not part of the initialization and is merely creating a temporary object so the original m_name or m_id never got changed from their default values 
	so its not recommended calling constructor from inside a functions body unless you dont mind the temporary object in this case use list initialization which makes it clear that
	you are intending to create an object.

	Well now whats the best way to solve that ... now we introduce Delegating constructors which basically transfers responsibility to initialize certain members to other
	constructors we call those delegating constructors and to do that is just call the other constructor in the member initialization list but the way it works is 
	that the constructor with the most members to initialize should do the initializing and the one with the fewer ones delegates to the one with the most e.g:
	*/
	Employee(std::string_view name, int id)  //Employees must have a name and id
		:Employee{name,id,false}  //just put the bool as one of the defaults bc still need to pass it even tho we dont have it /btw if we delegate we arent allowed to member initialize anything else on this constructor
	{
		//no need for anything in the function body we this constructor is just delegating
	}

	Employee(std::string_view name, int id, bool mng) //more member initialized here so it delegates too it 
		:m_name{ name}
		,m_id{id}
		,m_isManager{ mng }
	{
		std::cout << "Employee " << m_name << " created.\n";
	}
	/*
	one of the downsides of delegation is that we need to pass the values that arent part of the delegating constructor and we dont always have default rdy for those but in
	case of m_isManager its fine bc we just passed the literal false which also was its default value and we had to do that bc we couldnt just emit it and there wasnt a way to 
	reference its set default value and also keep in mind a constructor that delegates can only delegate not initialize so its either the one or the other. It is possible to 
	delegate to another constructor that is also delegating but its not recommended just delegate to a non delegating constructor.
	So use delegation if you have multiple constructors to reduce multiple code.
	*/
#endif 

	//we can also use default arguments instead of delegating to reduce constructors e.g:
	Employee(std::string_view name, int id, bool mng = false) // bc mng is a default argument with false its optional if we initialize ir or not
		:m_name{ name }
		, m_id{ id }
		, m_isManager{ mng }
	{
		std::cout << "Employee " << m_name << " created.\n";
	}
	/*
	For this approach above , you need to keep smth in mind which is for default values that it must be at the rightmost parameter so you need to start with the
	rightmost parameter if you use defaul so for example foo(int x = 10,int y) would be incorrect foo(int x, int y= 10) or foo(int x = 10 , int y = 3) would be valid , with that
	in mind  put the values the user need to initialize to the left and the once that are optional to  the right.
	
	An issue with this way would be multiple default initialization once as the default member initializer and once as the default argument so some people are discussing if its 
	better to have more constructors and less initialization or more initialization and less constructors but the preferred one is less constructors even if it means more duplication
	of initialization values
	*/
	const std::string& getName() const 
	{
		return m_name;
	}

};

class Ball
{
	std::string m_color{ "black" };
	double m_radius{ 10.0 };
public:
#if 0
	Ball()
	{
		printBall();
	}
	Ball(std::string_view color)
		:m_color{ color }
	{
		printBall();
	}
	Ball(double radius)
		:m_radius{ radius }
	{
		printBall();
	}
	Ball(std::string_view color, double radius)
		:m_color{ color }
		, m_radius{ radius }
	{
		printBall();
	}
#endif 
	Ball(double radius)  //radius delegated constructor needed bc for default only color is fine bc its on the left but only radius is not fine bc its on the right and we start defaults with the right
		:Ball("black", radius)
	{
	}
	Ball(std::string_view color = "black", double radius = 10.0) 
		:m_color{ color }
		, m_radius{ radius }
	{
		printBall();
	}
	void printBall() const
	{
		std::cout << "Ball(" << m_color << ", " << m_radius << ")\n";
	}
};

int main()
{
#if 0
	//both work
	Employee e1{"Jeff",9}; //uses constructor Employee(std::string_view name,int id)
	Employee e2{ "James",44,true }; //uses constructor Employee(std::string_view name,int id, bool mng)
#endif 
#if 0
	Employee e3{ "Dave",3,true }; //prints Employee Dave created 
	std::cout << "e3 has the name: " << e3.getName() << '\n'; //Bc its a temporary object created inside of the constructor the name isnt saved so this prints ??? instead of dave 
#endif 
#if 0
	Employee e4{ "Dave",3,true };
	std::cout << "e4 has the name " << e4.getName() << '\n';
	Employee e5{ "Nat",4 };
	std::cout << "e5 has the name " << e5.getName() << '\n';
#endif

	Employee e6{ "Drey",5 };  //bool is optional bc its a default argument
	std::cout << "e6 has the name " << e6.getName() << '\n';
	Employee e7{ "Rick",5,true };
	std::cout << "e7 has the name " << e7.getName() << '\n';

	Ball def{};
	Ball blue{ "blue" };
	Ball twenty{20.0};
	Ball blueTwenty{ "blue",20.0 };

	return 0;
}