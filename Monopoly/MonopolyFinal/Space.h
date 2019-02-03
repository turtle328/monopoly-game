#pragma once
#include <string>
#include <vector>

class Player;

class Space
{
public:
	virtual void run(Player&) = 0;
	virtual std::string getName() const = 0;
	virtual std::vector<std::string> boardOut() const = 0;
};