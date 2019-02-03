#include "EmptySpace.h"

EmptySpace::EmptySpace(std::string name)
{
	this->name = name;
}

void EmptySpace::run(Player &)
{
	return;
}

std::string EmptySpace::getName() const
{
	return name;
}

std::vector<std::string> EmptySpace::boardOut() const
{
	std::vector <std::string> out{};
	out.push_back(getName());
	return out;
}
