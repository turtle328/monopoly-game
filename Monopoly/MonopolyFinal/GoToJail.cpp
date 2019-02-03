#include "GoToJail.h"
#include "Player.h"
#include <iostream>
using namespace std;

extern vector<string> menuDisplay;

void GoToJail::run(Player& p)
{
	menuDisplay.push_back("Go to jail, you do not pass go.");
	p.goToJail();
}

std::string GoToJail::getName() const
{
	return name;
}

std::vector<std::string> GoToJail::boardOut() const
{
	return std::vector<std::string>();
}
