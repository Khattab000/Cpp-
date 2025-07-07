#include <iostream>
#include <ios> // for std::boolalpha
#include <string>


//On this lesson we learn about Class templats with member functions 


//Quick reminder of a function template:
template <typename T>
T smth(T x, T y)
{
	return(x == y) ? x : y;
}

//Quick remidner of a class template:
template <typename T>
struct Pair
{
	T first{};
	T second{};
};

template <typename T>
constexpr T max( Pair<T> p )
{
	return (p.first > p.second) ? p.first : p.second;
}


//now lets have a look for a class type template:
template <typename T>
class Pairing
{
	T m_first{};
	T m_second{};

public:
	Pairing(const T& first, const T& second)
		:m_first{ first }
		, m_second{ second }
	{}
	// Ás you can see template parameters for a class can be used both for the data types and member functions


	bool isEqual(const Pairing<T>& pair); // forward declaration 

	
	/*
	You might get confused why its fine to call the constructor Pairing even tho technincally the correct name is Pairing<T> bc its a template,
	the reason for that is smth we call injected class names, which take place in this case where we create a class template in this case the name Pairing is injected into the class
	making it that every use of the word Pairing insided the class means Pairing<T> this is also fine to be used in function parameters where we said that deduction isnt allowed 
	but in this case no deduction takes place.

	Also important to note to the example below of the definition being outside of the class:
	
	The declaration:
	bool isEqual(const Pairing<T>& pair); can be rewritten to bool isEqual(const Pairing& pair); bc as we said Pairing = Pairing<T> inside the class 

	The definition outside of the class 
	bool Pairing<T>::isEqual(const Pairing<T>& pair) can be rewritten to bool Pairing<T>::isEqual(const Pairing& pair) , as you can see the Pairing<T>:: cant be 
	rewritten without the <T> bc its not inside the class, the Pairing<T>:: makes the function inside the class and bc of that we can rewrite the Pairing<T> inside the parameter
	tho
	*/
};

template<typename T>  //bc this member function was defined outside of the class the template needs to be resuplied
bool Pairing<T>::isEqual(const Pairing<T>& pair)    // Pairing is not the correct type bc its a template thats why we use Pairing<T> here
{
	return (m_first == pair.m_first) && (m_second == pair.m_second);
}


/*
About the placement of member functions of template class, either inside or right below it(recommended) and also in the same file(even same header file and dont worry each 
instantiated template function is implicitly inline so its fine and no ODR will be broken)
*/


//small quiz:
template<typename T, typename U, typename V>
class Triad
{
	T m_first{};
	U m_second{};
	V m_third{};

public:
	Triad(const T& first, const U& second, const V& third)
		:m_first{first}
		,m_second{second}
		,m_third{third}
	{ }

	const T& first() const
	{
		return m_first;
	}
	const U& second() const
	{
		return m_second;
	}
	const V& third() const
	{
		return m_third;
	}

	void print() const;
};

template<typename T,typename U,typename V>
void Triad<T, U, V>::print() const
{
	std::cout << "[" << m_first << ", " << m_second << ", " << m_third << "]\n";
}


int main()
{
	Pair<int> paar1{ 3,5 };  // instantiates Pair<int> and creates object
	std::cout << max(paar1) << '\n';

	Pair<double> paar2{ 7.7,8.0 }; // instantiates Pair<double> and creates object
	Pair<double> paar3{ 8.8,9.3 }; // uses earlier definition of Pair<double> and creates object

	Pairing<int> p1{ 5,6 };   // <int> not needed bc it can deduced it itself
	std::cout << std::boolalpha << p1.isEqual(Pairing{5,6}) << '\n';
	std::cout << std::boolalpha << p1.isEqual(Pairing{ 7,8 }) << '\n';


	Triad <int, int, int> t1{ 1,2,4 };
	t1.print();
	std::cout << t1.first() << '\n';

	using namespace std::literals::string_literals;
	const Triad t2{ 1,2.3,"Hello"s };
	t2.print();

	return 0;
}
