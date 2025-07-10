#include <iostream>

//QUESTION 1 : MONSTER GENERATOR


class Monster
{
public:
	/*
	Reminder for the scoped enum to be used you need to use  MonsterType:: like: MonsterType daniel{MonsterType::orc} (or now that its nested inside
	the class Monster and its unscoped you need to use Monster::Type like: Monster::Type daniel{Monster::orc}) and it has no implicit int conversion so you 
	need to use static_cast<>()
	*/
	enum Type //drop the class we dont want it scoped inside a class 
	{
		dragon,
		goblin,
		ogre,
		orc,
		skeleton,
		troll,
		vampire,
		zombie,
		maxMonsterTypes, // this here to to count how many Monstertypes there are bc its int is the value of the amount of how many are before 
	};
private:
	Type m_type{};
	std::string m_name{"???"};
	std::string m_roar{"???"};
	int m_hitPoints{};

public:
	Monster(Type type, std::string_view name,std::string_view roar, int hitPoints)
		:m_type{type}
		,m_name{name}
		,m_roar{roar}
		,m_hitPoints{hitPoints}
	{ }

	constexpr std::string_view getTypeString() const
	{
		switch (m_type)
		{
		case dragon:
			return "dragon";
		case goblin:
			return "goblin";
		case ogre:
			return "ogre";
		case skeleton:
			return "skeleton";
		case troll:
			return "troll";
		case vampire:
			return "vampire";
		case zombie:
			return "zombie";
		default:
			return "???";
		}
	}

	void print() const
	{
		if (m_hitPoints <= 0)
		{
			std::cout << m_name << " the " << getTypeString() << " is dead.\n";
		}
		else
		{
			std::cout << m_name << " the  " << getTypeString() << " has " << m_hitPoints << " hit points and says " << m_roar << ".\n";
		}
	}

};

int main()
{
	Monster skeleton{ Monster::skeleton,"Larry","*rattle*",4 };
	skeleton.print();

	Monster vampire{ Monster::vampire,"James","*hiss*",0 };
	vampire.print();

	return 0;
}