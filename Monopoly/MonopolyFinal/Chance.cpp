#include "Chance.h"
#include "Player.h"
#include "Property.h"
#include "Groups.h"
#include <ctime>
#include <iostream>
using namespace std;

extern vector<string> menuDisplay;

void Chance::run(Player& p)
{
	// random seed
	static bool seeded = false;
	if (!seeded)
	{
		srand(time(NULL));
		seeded = true;
	}
	// generate rand card between 1 and 5
	int randCard = rand() % 5 + 1;

	switch (randCard)
	{
	case 1:
	{
		menuDisplay.push_back("Go back three spaces");
		p.move(-3);
		board[p.getLocation()]->run(p);
		break;
	}
	case 2:
	{
		menuDisplay.push_back("Go to jail. You do not pass go. Do not collect $200.");
		p.goToJail();
		break;
	}
	case 3:
	{
		menuDisplay.push_back("You now hold a get out of jail free card!");
		p.hasJailFreeCard = true;
		break;
	}
	case 4:
	{
		menuDisplay.push_back("Advance to nearest utility.");
		advanceToUtility(p);
		break;
	}

	case 5:
	{
		menuDisplay.push_back("Take a walk on the Boardwalk. Advance to Boardwalk!");
		p.setLocation(39);
		board[p.getLocation()]->run(p);
		break;
	}
	}
	menuDisplay.push_back("");
}

std::string Chance::getName() const
{
	return name;
}

std::vector<std::string> Chance::boardOut() const
{
	return std::vector<std::string>();
}

void Chance::advanceToUtility(Player& p)
{
	while (true)
	{
		Space* s = board[p.getLocation()];
		if (Property* prop = dynamic_cast<Property*>(s))
		{
			if (prop->getGroup() == Utility)
			{
				board[p.getLocation()]->run(p);
				return;
			}
		}
		p.move(1);
	}
}
