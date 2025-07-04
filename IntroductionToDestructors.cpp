#include <iostream>

//On this lesson we learn about Destructors
#if 0
/*
Lets say you want to write a program that sends some data over a network but establishing a connection to the network is expensive which is why you want to collect bunch of data
and send it all at once so this class could look like this e.g:
*/
class NetworkData
{
	std::string m_serverName{};
	DataStore m_dataQueue{};

public:
	NetworkData(std::string_view serverName)
		:m_serverName{serverName}
	{ }

	void addData(std::string_view data)
	{
		m_dataQueue.add(data);
	}

	void sendData()
	{
		//connect to server - send all data - clear data
	}
};
/*
The problem here is tho that the program relies on the fact that.sendData() is explicitly called before the program shuts down. So if the user of NetwordData 
forgets to do that the data will not be send to the server and will be lost when the program exits lets give an example where you easily could forget it e.g:
*/

bool someFunction()
{
	NetworkData n{ "someIPAddress" };
	n.addData("someData1");
	n.addData("someData2");
	if (someCondition)
	{
		return false; //bc of that the program ends early and sends false instead of true but it also means it skips the call to .sendData()
	}

	n.sendData();

	return true;
}
#endif
/*
Objects that manage resources (like memory, files, or network connections) often need to release those resources before being destroyed. Doing this cleanup manually is error-prone.
Destructors help automate this process.

A destructor has the same name as the class, prefixed with a ~ (e.g., ~NetworkData()), takes no parameters, and has no return type. It is automatically called when the object goes
out of scope or is explicitly deleted.

The destructor is used to perform cleanup tasks, such as releasing memory or closing files. It's also safe to call other member functions from within the destructor.

Lets see a simple example for a destructor
*/

class Simple
{
	int m_id{};

public: 
	//Constructor initializes first and then executes the lines in its function body
	Simple(int id)
		:m_id{ id }
	{
		std::cout << "Construction Simple " << m_id << '\n';
	};

	//Destructor executes the lines in its function body first and then destroys
	~Simple() // thats our destructor
	{
		std::cout << "Destruction Simple " << m_id << '\n';
	}

	int getID() const
	{
		return m_id;
	}
};

//lets add our destructor to our NetworkData program e.g:
class NetworkData
{
	std::string m_serverName{};
	DataStore m_dataQueue{};

public:
	NetworkData(std::string_view serverName)
		:m_serverName{ serverName }
	{
	}
	~NetworkData() // added destructo 
	{
		sendData();   // this way the user doesnt need to call sendData() explicitly anymore 
	}

	void addData(std::string_view data)
	{
		m_dataQueue.add(data);
	}

	void sendData()
	{
		//connect to server - send all data - clear data
	}
};

int main()
{
#if 0
	NetworData n{ "someIpAddress" };
	n.addData("someData1");
	n.addData("someData2");

	n.sendData();
#endif 

	Simple simple1{ 1 };

	{
		Simple simple2{ 2 };
	} //simple2 dies here and triggers the destructor

	//now the version of the NetworkData code after adding destructor
	NetworData n{ "someIpAddress" };
	n.addData("someData1");
	n.addData("someData2");
	//this time we dont call .sendData() anymore bc the destructor already does it automatically so the chances for error are less and we can be sure that the data was send before destruction of the object

	
	/*
	Btw for non aggregate classs types if no explicit destructor is declared, then the compiler generates a destructor with empty body basically being a placeholder so if no
	cleanup or extra steps are needed before destruction of the object its fine to let the compiler generate an implicit destructor

	IMPORTANT: When using std::exit() or and unhandled exception causes the program to terminate immediatley , the programm just ends and local vartiables are not destroyed first 
	and because of this the destructor will not be triggered so be wary if you rely on your destructors to do nexessary cleanup work in such cases 
	(unhandlede exceptions might let the program unwind the stack in this case the destructor is called but thats not always the case so dont count on it)
	*/


	return 0;
} // simple1 dies here and triggers the destructor