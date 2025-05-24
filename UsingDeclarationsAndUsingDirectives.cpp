#include <iostream>
#include "Foolib.h"  // for third party libraries outside of the project directory uses < > brackets
// is used with Foolib.h
int cout()
{
	return 5;
}
// using namespace std; // not recommended tho bc of possible naming collisions

/*
There are qualified and unqualified names.
Qualified  names are names that include a scope mostly using the :: operator  eg.
std::cout // itentifier cout is a qualified name by the namespace std
::foo // identifier foo is a qualified name by the global namespace

and unqualified names dont include a scoping qualifier (no ::) e.g
x  // unqualified
cout // unqualified
*/

void print()
{
	std::cout << "Hello\n";
}

int get(long)
{
	return 1;
}

int main()
{
	using std::cout; // this tells the compiler that cout should resolve to std::cout
	// doing this is fine less way to get naming collision
	cout << "Hello world!\n";
	using namespace std;  // with this one all names from std are able to be used without std:: prefix ( not recommended tho)
	cout << "Hello World!\n";  // would normally cause an error bc we have function called cout but bc we have using std::cout there isnt 

	// also a big issue with using namespaces is that if the directive/library/namespace got updated it might introduce new naming collisions that wherent there yet

	using namespace Foo;

	std::cout << a << '\n'; // uses Foo::a 
	print(); // would call ::print() but bc Foolib.h got updated it gets us an error

	std::cout << get(0) << '\n'; 
	/*
	calls Foo::get in this case no error, normally it would bc of
	naming conflicts but in this case bc there is a function he 
	prefers (Foo::get) bc no conversion is needed bc this one takes
	an int variable instead of a long and we pass an int too it so
	this one is preferred BUT keep in mind if the the using namespace was
	before the inclusion of its respective file (where the namspace is located)
	it would have used the function/namespace with long even if its not 
	the most efficient thing so keet that in mind (all that only
	works and doesnt cause naming collision if it has diffrent distinctive
	types)
	*/

	/* 
	another disatvantag of using, using namespace is that its
	not clear which namespace certain functions/variables refer to
	*/

	/*
	Conclusion: Try to avoid using namespace and prefer explicit
	namespace qualifier over using statements.
	Exception would be using namespace std::literals to use s and sv literal suffixes
	*/
	return 0;
}