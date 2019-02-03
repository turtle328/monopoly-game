#include "CommunityChest.h"
#include "Player.h"
#include <ctime>
#include <iostream>
using namespace std;

extern vector<string> menuDisplay;

void CommunityChest::run(Player& p)
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
		menuDisplay.push_back("School fees pay $50");
		p.subtractMoney(50);
		break;
	}
	case 2:
	{
		menuDisplay.push_back("Doctor's fees pay $50");
		p.subtractMoney(50);
		break;
	}
	case 3:
	{
		int total{ 0 };
		menuDisplay.push_back("You are assessed for street repairs. Pay $40 per house and pay $115 per hotel.");
		total += 40 * p.getHouses();
		total += 115 * p.getHotels();
		menuDisplay.push_back("You pay a grand total of $" + to_string(total));
		p.subtractMoney(total);
		break;
	}
	case 4:
	{
		menuDisplay.push_back("Life insurance matures. Collect $100.");
		p.addMoney(100);
		break;
	}
	case 5:
	{
		menuDisplay.push_back("You have won a second prize in a beauty contest. Collect $10.");
		p.addMoney(10);
	}
	}
	menuDisplay.push_back("");
}

std::string CommunityChest::getName() const
{
	return name;
}

std::vector<std::string> CommunityChest::boardOut() const
{
	return std::vector<std::string>();
}
