#include "IncomeTax.h"
#include "Player.h"
#include <iostream>
using namespace std;

extern vector<string> menuDisplay;

void IncomeTax::run(Player& p)
{
	menuDisplay.push_back("Income tax due, pay $200.");
	menuDisplay.push_back("");
	p.subtractMoney(200);
}

std::string IncomeTax::getName() const
{
	return name;
}

std::vector<std::string> IncomeTax::boardOut() const
{
	return std::vector<std::string>();
}
