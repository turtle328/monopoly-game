#include "LuxuryTax.h"
#include "Player.h"
#include <iostream>
using namespace std;

extern vector<string> menuDisplay;

void LuxuryTax::run(Player& p)
{
	menuDisplay.push_back("Pay a luxury tax, pay $100 to the bank.");
	menuDisplay.push_back("");
	p.subtractMoney(100);
}

std::string LuxuryTax::getName() const
{
	return name;
}

std::vector<std::string> LuxuryTax::boardOut() const
{
	return std::vector<std::string>();
}
