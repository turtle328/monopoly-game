#pragma once
#include <string>
#include <vector>
#include <functional>
#include "Dice.h"
#include "Property.h"

class Player
{
public:
	explicit Player(std::string name);
	std::vector <Property*>& getOwnedProperties();
	std::string getName() const;
	std::string toString() const;
	void setName(std::string newName);
	void subtractMoney(int amount);
	void addMoney(int amount);
	int getCurMoney() const;
	void setLocation(int newLocation);
	int getLocation() const;
	int getCurDiceRoll() const;
	void move(int num);
	void addProperty(Property& p);
	void removeProperty(Property& p);
	void mortgage(Property& p);
	int getHouses();
	int getHotels();
	int getNetWorth();
	void goToJail();
	void rollDice(Dice& d, bool checkFirst=false);
	void buyBuilding(Property& p);
	void sellBuilding(Property& p);
	std::vector <Property*> getOwnedPropertiesInGroup(int group);
	int getNumInGroup(int group);
	int checkBuildings(Property& p, bool lowest);
	bool hasMonopoly(int group);
	bool jailed{ false };
	bool hasJailFreeCard{ false };
	bool canRoll{ true };
	bool bankrupt{ false };
	int getPlayerNum() const;
	void setPlayerNum(int num);
	bool checkDebt();
private:
	int curMoney{ 1500 };
	int curLocation{ 0 };
	int playerNum{ 0 };
	std::string name;
	std::vector<Property*> ownedProperties{};
	int curDiceRoll;
};