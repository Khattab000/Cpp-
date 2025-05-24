#include <iostream>
#include "goo.h"  // include this so we can use Goo::doSomething
#include "foo.h"  // include this so we can use Foo::doSomething

int doSomething(int x, int y); // forward declare doSomething bc mistakingly put it under other functions that check for it
namespace Doo
{
	int doSomething(int x, int y)
	{
		return x * y;

	}
}

namespace Loo
{
	int doSomething(int x, int y)
	{
		return x % y;
	} 

	int doSomething2(int x, int y)
	{
		int i{ doSomething(x,y) };       // doSomething from the namespace Loo  x % y
		int k{ ::doSomething(x, y) };    // do someting from the global namespace x / y  
		return k + i;
		/* 
		in this case :: is actually required bc it looks for the definition in the current scope first if ::isnt there it looks through other namespaces that are included
		and then as the last option it looks into the global space, so then it would take the doSomething from Loo but with :: it would look in the global space first
		*/
	}

}

int doSomething(int x, int y)
{
	return x / y;
}
// small tip to avoid naming collisions try to define identifiers in the smallest scope possible

// foo.cpp and goo.cpp are used for the example here to showcase naming collisions and how to fix it 
#if 0
int doSomething(int x, int y); // forward declaration of the function doSomething / after putting doSomething in a namespace this forward declaration wont work anymore bc doSomething isnt in the global name space anymore
#endif
int main()
{
#if 0
	std::cout << doSomething(4, 3) << '\n';   // this will give an error bc doSomething is defined in foo and goo and compiler doesnt know which to use
#endif
	// to fix the naming collision we can create our own namepaces we will do that in foo.cpp and goo.cpp /naming convention for namespaces is to start with an capital letter to avoid any issues

	std::cout << Foo::doSomething(4, 3) << '\n'; // use the doSomething in the namespace Foo in foo.cpp /we need to create Header Files for each of them so they can be included
	std::cout << Goo::doSomething(4, 3) << '\n'; // use the doSomething in the namespace Goo in goo.cpp /we need to create Header Files for each of them so they can be included

	// namespaces can be also defined in the same file e.g

	std::cout << Doo::doSomething(4, 3) << '\n'; // we call doSomething from the namespace Doo
	std::cout << Loo::doSomething(4, 3) << '\n'; // we call doSomething from the namespace Loo
	std::cout << Loo::doSomething2(4, 3) << '\n'; // we call doSomething2 from the namespace Loo this one calls doSomething from the namespace Loo and doSomething from the global namespace 
	std::cout << ::doSomething(4, 3) << '\n';    // we call doSomthing that was defined in this file and ::doSomething(4,3) is the same as doSomething(4,3) this can be useful to make it clear which doSomething is called if there are multiple

	/*
	  btw its also allowed declaring namespace blocks of the same namespace  in multiple locations  e.g 

	  circle.h
	  #pragma once

	  namespace BasicMath
	  {
	    constexpr double pi{3.17};
	  }

	  
	  growth.h
	  #pragma once

	  namespace BasicMath
	  {
	    constexpr double e{ 2.7};
	  }




	*/

	// Please dont add new functionalities to the std namespace that just leads to undefined behaviour bc the std namespace has some special rules

	/*
	You can also create Nested Namespaces e.g

	namespace Foo 
	{
	    namespace Goo   // Goo is a namespace inside the Foo namespace
		{ 
		int add (int x, int y)
		{
		    return x + y;
		}
	}

	You access Goo by using Foo::Goo::add() e.g
	
	std::cout << Foo::Goo::add(1,2) << '\n';

	You can also declare Goo like that since C++17 :

	namespace Foo::Goo
	{
	   int add (int x, int y)
		{
		    return x + y;
		}
	}
	// Is the exact same as above and if you only want to add a function to Foo you just do the usual:
	namespace Foo
	{
	   void someFcn()  // this function is only in the Foo namespace not in the Goo namespace
	   {}
	}
	but if you want to use add you need to write the full hirarchy Foo::add wouldnt work you need to use Foo::Goo::add but Foo::someFcn would work bc someFcn is part of the Foo namespace ( but not part of the Goo namespace)   
	

	But if namespace hirarchy get to long you can give it an alias e.g
	
	namespace Active = Foo::Goo; // Active refers to Foo::Goo now
	std::cout << Active::add(1,2) << '\n'; // Active::add() is the same ass Foo::Goo::add()

	Also an advantage of that is that if we want to change every instance off Active we can do that e.g
	namespace Active = V2  // V2 being another namespace / so only that needs to be changed if we changed the code above that so Active refers to V2 now
	std::cout << Active::add(1,2) << '\n'; // this stays the same assuming V2 has a add function in its namespace


	Conclusion: Namespaces are mostly used to avoid naming collisions as evidence of that most of the standart library is in std
	so in smaller projects making your own namespaces isnt rly needed but for bigger projects that also uses 3rd party libraries it might be smart take advantage of them to avoid naming collisions
	and code that is distributed to others should be also namespaced to prevent conflicts with other codes or even code that you wanna reuse for others like namespace for Physics but try to avoid deeply nested namespaves (more than 3 Levels)
	*/


	return 0;
}