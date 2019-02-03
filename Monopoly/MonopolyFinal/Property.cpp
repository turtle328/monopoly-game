#include "Property.h"
#include "Player.h"
#include "Menu.h"
#include "Groups.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "board_out.h"
using namespace std;

extern vector<string> menuDisplay;

const array<string, 10> Property::groups{ "Brown", "Light Blue", "Pink", "Orange", "Red", "Yellow", "Green", "Dark Blue", "Railroad", "Utility" };

Property::Property(std::string name, std::vector<int> values)
{
	this-> name = name;
	group = values[0];
	price = values[1];
	buildingCost = values[2];
	rent = { values[3], values[4], values[5], values[6], values[7], values[8]};
}

Property::~Property()
{
	delete ownerPtr;
}

void Property::run(Player& p)
{
	if (ownerPtr == nullptr)
	{
		string propertyDetails = this->toString();
		int choice = 1;
		if (p.getCurMoney() >= this->price)
		{
			string prompt = propertyDetails +
				"\n\n" + p.getName() + ", would you like to buy this property or auction it?: ";
			vector <string> choices{ "Buy it", "Auction it" };
			Menu buyProperty{ prompt, choices };
			choice = buyProperty.getChoice();
		}

		else
			cout << "You do not have enough money to buy this property" << endl;

		if (choice == 0)
		{
			cout << "\n" << p.getName() << " buys " << name << " for $" << price << endl;
			p.addProperty(*this);
			p.subtractMoney(price);
			ownerPtr = &p;
			system("pause");
		}

		else
		{
			auction();
		}
	}

	else if (ownerPtr == &p)
		menuDisplay.push_back("This is your property. No need to pay rent!");

	else if (mortgaged)
		menuDisplay.push_back("This property is currently mortgaged. You don't have to pay rent to " + ownerPtr->getName());

	else if (ownerPtr != &p)
	{
		int rent = getCurRent(p);
		menuDisplay.push_back(p.getName() + " pays $" + to_string(rent) + " to " + ownerPtr->getName() +
			" for renting their property " + name);
		p.subtractMoney(rent);
		ownerPtr->addMoney(rent);
	}
}

std::vector<std::string> Property::boardOut() const
{
	vector<string> out{};
	out.push_back(name);
	out.push_back("Group: " + groups[group]);
	out.push_back("Price: $" + to_string(price));
	if (group < RailRoad)
	{
		out.push_back("Rent: $" + to_string(rent[0]));
		for (int i = 1; i <= 4; i++)
			out.push_back("House " + to_string(i) + ": $" + to_string(rent[i]));
		out.push_back("Hotel: $" + to_string(rent[5]));
		out.push_back("Cost per building: $" + to_string(buildingCost));
	}
	else if (group == RailRoad)
	{
		out.push_back("Rent: $25");
		out.push_back("If 2 R.R's are owned: $50");
		out.push_back("If 3 R.R's are owned: $100");
		out.push_back("If 4 R.R's are owned: $200");
	}
	else if (group == Utility)
	{
		out.push_back("One utility owned: 4 times dice roll");
		out.push_back("Two utilities owned: 10 times dice roll");
	}
	return out;
}

std::string Property::getName() const
{
	return name;
}

std::string Property::toString(bool ownerInfo) const
{
	string out;
	out += "Property Name: " + name;
	out += "\n\n\t\tGroup: " + groups[group];
	out += "\n\t\tPrice: $" + to_string(price);
	if (group < 8)
	{
		out += "\n\t\tRent: $" + to_string(rent[0]);
		for (int i = 1; i <= 4; i++)
			out += "\n\t\tHouse " + to_string(i) + ": $" + to_string(rent[i]);
		out += "\n\t\tHotel: $" + to_string(rent[5]);
		out += "\n\t\tCost per house: $" + to_string(buildingCost);
		if (ownerInfo)
		{
			out += "\n\t\tNum houses owned: " + to_string(getHouses());
			out += "\n\t\tHas hotel: ";
			out += hasHotel() ? "true" : "false";
			out += "\n\t\tIs Mortgaged: ";
			out += mortgaged ? "true" : "false";
		}
	}
	else if (group == RailRoad)
	{
		out += "\n\t\tRent: $25";
		out += "\n\t\tIf 2 R.R's are owned: $50";
		out += "\n\t\tIf 3 R.R's are owned: $100";
		out += "\n\t\tIf 4 R.R's are owned: $200";
	}
	else if (group == Utility)
	{
		out += "\n\t\tOne utility owned: 4 times dice roll";
		out += "\n\t\tTwo utilities owned: 10 times dice roll";
	}
	return out;
}

int Property::getGroup() const
{
	return group;
}

std::string Property::getGroupString() const
{
	return groups[group];
}

int Property::getPrice() const
{
	return price;
}

int Property::getBuildingCost() const
{
	return buildingCost;
}

int Property::getBuildings() const
{
	return buildings;
}

int Property::getHouses() const
{
	if (buildings == 5)
		return 4;
	else
		return buildings;
}

void Property::buyBuilding()
{
	buildings++;
}

void Property::sellBuilding()
{
	buildings--;
}

bool Property::hasHotel() const
{
	if (buildings == 5)
		return true;
	else
		return false;
}

array<int, 6> Property::getRentArray() const
{
	return rent;
}

int Property::getCurRent(Player& p) const
{
	int curRent;
	if (group < 8) // if it's not a railroad or utility
	{
		curRent = rent[buildings];
		if (buildings == 0 && p.hasMonopoly(group))
			return curRent * 2;
		else
			return curRent;
	}
	else if (group == RailRoad) // if it's a railroad
		return 25 * pow(2, ownerPtr->getNumInGroup(RailRoad) - 1);

	else if (group == Utility)
	{
		int diceRoll = p.getCurDiceRoll();
		cout << "You rolled a " << diceRoll << " when you landed on this property." << endl;
		if (ownerPtr->getNumInGroup(Utility) == 1)
		{
			cout << "The owner owns only one utility. Pay 4 times your dice roll." << endl;
			return 4 * diceRoll;
		}
		else
		{
			cout << "The owner owns both utilities. Pay 10 times your dice roll." << endl;
			return 10 * diceRoll;
		}
	}
}

Player* Property::getOwner()
{
	return ownerPtr;
}

void Property::setOwner(Player* newOwner)
{
	ownerPtr = newOwner;
}

void Property::auction()
{
	vector <Player*> bidders{};
	for (Player& p : players)
	{
		p.removeProperty(*this);
		if (!p.bankrupt)
			bidders.push_back(&p);
	}

	vector<string> auctionOptions{ "Bid $1", "Bid $10", "Bid $100", "Withdraw" };
	int highestBid = 0;
	Player* highestBidder = bidders[0];

	while (bidders.size() > 1)
	{
		for (int i = 0; i < bidders.size() && bidders.size() > 1; i++)
		{
			if (bidders[i]->getCurMoney() >= highestBid)
			{
				Menu bidMenu(toString() +
					"\n\n\tCurrent highest bid: $" + to_string(highestBid) +
					"\n\tHighest bidder: " + highestBidder->getName() +
					"\n\tYou currently have: $" + to_string(bidders[i]->getCurMoney()) +
					"\n\t" + bidders[i]->getName() + " your turn to bid.\n", auctionOptions);
				system("CLS");
				int choice = bidMenu.getChoice();
				bool withdraw = false;

				if (choice == 0)
				{
					highestBid += 1;
					highestBidder = bidders[i];
				}
				else if (choice == 1)
				{
					highestBid += 10;
					highestBidder = bidders[i];
				}
				else if (choice == 2)
				{
					highestBid += 100;
					highestBidder = bidders[i];
				}
				else
				{
					cout << "\nYou withdraw." << endl;
					withdraw = true;
					bidders.erase(bidders.begin() + i--);
					system("pause");
				}

				if (!withdraw && highestBid > bidders[i]->getCurMoney())
				{
					highestBid = bidders[i]->getCurMoney();
				}
			}
			else
			{
				cout << "\n" << bidders[i]->getName() << ", you do not have enough money to beat this bid, automatically kicked out." << endl;
				bidders.erase(bidders.begin() + i--);
				if (bidders.size() == 1)
					highestBidder = bidders[0];
				system("pause");
			}
		}
	}
	cout << "\n" << highestBidder->getName() << " wins " << name << " for $" << highestBid << "!" << endl;
	highestBidder->subtractMoney(highestBid);
	highestBidder->addProperty(*this);
	ownerPtr = highestBidder;
	system("pause");
}