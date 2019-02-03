#pragma once
#include "Space.h"
#include <array>
#include <vector>

extern std::vector<Player> players;

class Property : public Space
{
public:
	Property(std::string name, std::vector<int> values);
	~Property();
	void run(Player&) override;
	std::vector<std::string> boardOut() const override;
	std::string getName() const override;
	std::string toString(bool = false) const;
	int getGroup() const;
	std::string getGroupString() const;
	int getPrice() const;
	int getBuildingCost() const;
	int getBuildings() const;
	int getHouses() const;
	void buyBuilding();
	void sellBuilding();
	bool hasHotel() const;
	std::array<int, 6> getRentArray() const;
	int getCurRent(Player& p) const;
	Player* getOwner();
	void setOwner(Player*);
	void auction();
	bool mortgaged;
private:
	std::string name;
	int group;
	int price;
	int buildingCost;
	int buildings;
	Player* ownerPtr = nullptr;
	std::array <int, 6> rent;
	static const std::array <std::string, 10> groups;
};