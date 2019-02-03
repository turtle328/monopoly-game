#include "Player.h"
#include "Groups.h"
#include <iostream>
#include <algorithm>
using namespace std;

extern vector<Space*> board;
extern vector<string> menuDisplay;

Player::Player(std::string name)
{
	this->name = name;
}

std::vector<Property*>& Player::getOwnedProperties()
{

	return ownedProperties;
}

std::string Player::getName() const
{
	return name;
}

std::string Player::toString() const
{
	string out = "";
	out += "Name: " + name + "\n";
	out += "Cash: $" + to_string(curMoney) + '\n';
	out += "Owned properties: ";
	for (Property* p : ownedProperties)
		out += p->getName() + " ";
	return out;
}

void Player::setName(std::string newName)
{
	name = newName;
}

void Player::subtractMoney(int amount)
{
	curMoney -= amount;
}

void Player::addMoney(int amount)
{
	curMoney += amount;
}

int Player::getCurMoney() const
{
	return curMoney;
}

void Player::setLocation(int newLocation)
{
	curLocation = newLocation;
}

int Player::getLocation() const
{
	return curLocation;
}

int Player::getCurDiceRoll() const
{
	return curDiceRoll;
}

void Player::move(int num)
{
	curLocation += num;
	if (curLocation > 39)
	{
		curLocation = curLocation - 40;
		menuDisplay.push_back("You passed go! Collect $200.");
		addMoney(200);
	}
}

void Player::addProperty(Property& p)
{
	ownedProperties.push_back(&p);
}

void Player::removeProperty(Property& p)
{
	ownedProperties.erase(find(ownedProperties.begin(), ownedProperties.end(), &p), ownedProperties.end());
}

void Player::mortgage(Property& p)
{
	if (p.mortgaged)
	{
		int unmortgagePrice = p.getPrice() / 2 * 1.1;
		if (getCurMoney() >= unmortgagePrice)
		{
			cout << "You unmortgage the property at 10% interest of the price." << endl;
			cout << "You pay $" << unmortgagePrice << endl;
			subtractMoney(unmortgagePrice);
			p.mortgaged = false;
		}
		else
		{
			cout << "You don't have enough money to unmortgage this property" << endl;
			cout << "You can unmortgage it once you have at least $" << unmortgagePrice << endl;
		}
	}
	else
	{
		if (p.getBuildings() == 0)
		{
			int mortgagePrice = p.getPrice() / 2;
			cout << "You mortgage this property for $" << mortgagePrice << endl;
			addMoney(mortgagePrice);
			p.mortgaged = true;
		}
		else
			cout << "You can't mortgage a property with buildings, sell them first!" << endl;
	}
}

int Player::getHouses()
{
	int totalHouses = 0;
	for (Property* p : ownedProperties)
		totalHouses += p->getHouses();
	return totalHouses;
}

int Player::getHotels()
{
	int totalHotels = 0;
	for (Property* p : ownedProperties)
		if (p->hasHotel())
			totalHotels++;
	return totalHotels;
}

int Player::getNetWorth()
{
	int netWorth = curMoney;
	for (Property* p : ownedProperties)
	{
		if (p->mortgaged)
			netWorth += p->getPrice() / 2;
		else
			netWorth += p->getPrice();
		netWorth += p->getBuildings() * p->getBuildingCost();
	}
	return netWorth;
}

void Player::goToJail()
{
	jailed = true;
	canRoll = false;
	setLocation(10);
}

void Player::rollDice(Dice& d, bool checkFirst)
{
	curDiceRoll = d.rollDice(name, checkFirst);
}

void Player::buyBuilding(Property& p)
{
	int numBuildings = p.getBuildings();
	
	cout << endl;

	if (p.getGroup() < RailRoad)
	{
		if (hasMonopoly(p.getGroup()))
		{
			if (curMoney >= p.getBuildingCost())
			{
				if (numBuildings == checkBuildings(p, true))
				{
					if (!(p.hasHotel()))
					{
						p.buyBuilding();
						subtractMoney(p.getBuildingCost());
						if (numBuildings == 4)
						{
							cout << "You buy a hotel!";
						}
						else
							cout << "You buy a house!";
					}
					else
						cout << "You already have a hotel.";
				}
				else
					cout << "You need to buy buildings evenly.";
			}
			else
				cout << "You don't have enough money to buy this building.";
		}
		else
			cout << "You need a monopoly on this group in order to build buildings.";
	}
	else
		cout << "You can't buy/sell houses on railroads or utilities.";
}

void Player::sellBuilding(Property &p)
{
	int numBuildings = p.getBuildings();
	if (numBuildings == checkBuildings(p, false))
		if (p.hasHotel())
		{
			p.sellBuilding();
			addMoney(p.getBuildingCost() / 2);
			cout << "You sell a hotel.";
		}
		else if (numBuildings > 0)
		{
			p.sellBuilding();
			addMoney(p.getBuildingCost() / 2);
			cout << "You sell a house.";
		}
		else
			cout << "You have no houses to sell on this property.";
	else
		cout << "You must sell houses evenly.";
}

std::vector<Property*> Player::getOwnedPropertiesInGroup(int group)
{
	vector <Property*> propertiesInGroup{};
	for (Property* p : ownedProperties)
		if (p->getGroup() == group)
			propertiesInGroup.push_back(p);
	return propertiesInGroup;
}

int Player::getNumInGroup(int group)
{
	int numProperties{ 0 };
	for (Property* p : ownedProperties)
		if (p->getGroup() == group)
			numProperties++;
	return numProperties;
}

int Player::checkBuildings(Property& p, bool lowest)
{
	vector<Property*> ownedPropertiesInGroup = getOwnedPropertiesInGroup(p.getGroup());
	vector<int> buildingsInEachProperty{};
	for (Property* p : ownedPropertiesInGroup)
		buildingsInEachProperty.push_back(p->getBuildings());
	if (lowest)
	{
		int lowestBuilding = 5;
		for (int buildings : buildingsInEachProperty)
		{
			if (lowestBuilding > buildings)
				lowestBuilding = buildings;
		}
		return lowestBuilding;
	}
	else
	{
		int highestBuilding = 0;
		for (int buildings : buildingsInEachProperty)
		{
			if (highestBuilding < buildings)
				highestBuilding = buildings;
		}
		return highestBuilding;
	}
}

bool Player::hasMonopoly(int group)
{
	int numInGroup = getNumInGroup(group);
	if (group == Brown || group == D_Blue)
	{
		if (numInGroup == 2)
			return true;
		else
			return false;
	}
	else if (numInGroup == 3)
		return true;
	else
		return false;
}

int Player::getPlayerNum() const
{
	return playerNum;
}

void Player::setPlayerNum(int num)
{
	playerNum = num;
}

bool Player::checkDebt()
{
	if (curMoney < 0)
	{
		Space* s = board[curLocation];
		Player* creditor = nullptr;
		if (Property* p = dynamic_cast<Property*>(s))
		{
			creditor = p->getOwner();
		}

		string person;
		if (creditor == nullptr)
			person = "the Bank";
		else
			person = creditor->getName();

		menuDisplay.push_back("You've gone into debt! Sell or trade your");
		menuDisplay.push_back("assets in order to avoid going bankrupt!");
		menuDisplay.push_back("If you do not manage to scrap up enough money ");
		menuDisplay.push_back(person + " will recieve all your assets.");
		menuDisplay.push_back("And you will be kicked from the game.");
		menuDisplay.push_back("");
		return true;
	}
	else return false;
}
