#include <iostream>


//You can use also use logical OR in switch statements to avoid the variable being evaluated every time e.g

bool isVowel(char c)
{
	return(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}
// instead of the above you do that :

bool isVowelSwitch(char c)
{
	switch (c)
	{
	case 'a':  // a or e or i or o or u or A or E or I or O or U return true otherwise default to return false
	case 'e':  // fallthrough isnt needed here
	case 'i':
	case 'o':
	case 'u':
	case 'A':
	case 'E':
	case 'I':
	case 'O':
	case 'U':
		return true;
	default:
		return false;

	}
}



int calculate(int x, char o, int y)
{
	switch (o)
	{
	case '+':
		return x + y;
	case '-':
		return x - y;
	case '*':
		return x * y;
	case '/':
		return x / y;
	case '%':
		return x % y;
	default:
		std::cout << "Error invalid operation sign\n";
		return 0;
	}
	
}

int main()
{
#if 0

	switch (2)  // you would expect this to only print 2 but bc we didn't add a break or return this starts at 2 and continues with 3 and 4 and "no number" so dont forget to add either break or return
	{           // we call that fallthrough
	case 1:
		std::cout << 1 << '\n';
		[[fallthrough]];
	
	case 2:
		std::cout << 2 << '\n';
		[[fallthrough]];  // use the attribute fallthrough to tell the compiler that your doing it on purpose so it wont warn and the ; here is to indicate that its a null statements
	case 3:
		std::cout << 3 << '\n';
		[[fallthrough]];
	case 4:
		std::cout << 4 << '\n';
		[[fallthrough]];
	default:
		std::cout << "no number\n";
	}
#endif
	// a big difference of switch and if statements is that the statements aren't implicitly in a block they are all part of the switch block unlike if statements where each if has its own block

	// you can also declare or define (but not initialize) variables inside of a switch statement e.g 
#if 0
	switch (1)
	{
		int a;   // you  can define a variable even outside of the cases but not recommended you rather want to put it inside a case and you could consider giving the cases blocks if you want to give them limited scope
		int b{ 5 }; // error initialization is not allowed before the case labels

	case 1:
		int y; // this is fine but not recommended and the reason why defining is fine but not initialization is that defining doesnt need to be executed so even if it was skipped its fine 
		y = 4; // assignment is fine 
		break;
	case 2:
		int z{ 4 }; // error initialization is not allowed if subsequent cases exist
		y = 5;  // is allowed bc it was defined beforehand
		break;
	case 3:
		int l{ 8 }; // initialization is fine bc no subsequent case labels exist and that includes default which is also a case label
		break;
	}
#endif
#if 0
	// if you rly want to initialize you can use a block bc then its fine bc its scope is limited e.g

	switch (1)
	{
	case 1:
	{
		int x{ 4 }; // even with subsequent case labels this is fine bc of the block in case 1
		std::cout << x << '\n';
		break;
	}
	default:
		std::cout << "default case\n";
		break;
	}
#endif
	std::cout << "Input 2 numbers with the operation sign in between to calculate: ";
	int x{};
	int y{};
	char o{};
	std::cin >> x >> o >> y;
	std::cout << calculate(x, o, y) << '\n';


	return 0;
}