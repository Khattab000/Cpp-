#include <iostream>
/*
namespace // unnamed namespace // main use of that is giving everything here internal linkage so it cant be seen outside of the file 
{
	void doSomething() // can only be accessed in this file
	{
		std::cout << "doing\n";
	}
}
*/

/*
  The above function and namespace is the same as 
  static void doSomething() both giving the function internal linkage
  The advantage of unnanmed namespace is that you dont need to give
  each function individually static you can just put it in the same 
  namespace
*/

//inline namespace mostly used for version control
namespace V1 // inline namespace named V1 basically the same as unnamed namespace but diffrence is that it doesnt affect linkage
{ 
	void doSomeone()
	{
		std::cout << "V1\n";
	}
}

inline namespace V2 // normal namespace // with inline V2 is the new pushed version
{

	void doSomeone()
	{
		std::cout << "V2\n";
	}
}


// You can also make a namespace unnamed and inline e.g:
inline namespace // has internal linkage even as inline bc unnamed namespace does that
{// keep in mind tho you cant have an inline unnamed namespace and an unnamed namespace at the same time
	void doSomebody()
	{
		std::cout << "V4\n";
	}
} // doing that tho is not recommended you should rather put the unnamed inline namespace in a named inline namespace e.g:

namespace V6
{
	void doSomewhere()
	{
		std::cout << "V98\n";
	}
}

inline namespace V5
{
	namespace
	{
		void doSomewhere()
		{
			std::cout << "V99\n";  // has internal linkage
		}
	}
}

namespace V3
{
	void doSomebody()
	{
		std::cout << "V3\n";
	}
}

int main()
{
	// doSomething(); // we can call this function without a namespace prefix

	V1::doSomeone();  // calls the V1 version  
	V2::doSomeone();  // calls the V2 version
	doSomeone();      // calls the V1 version // calls V2 after putting inline on V2
	/*
	  this way you can be sure that parts that call the older version can still do so and use V2 if needed
	  and if you want to push the newer version (V2) then just remove inline
	  from V1 and put inline on V2
	  */

	V3::doSomebody();  // calls V3
	doSomebody();      // calls the doSomebody in the unnamed inline function
	
	
	V6::doSomewhere(); 
	V5::doSomewhere();
	doSomewhere();  // calls the inline version of V5
	return 0;
}