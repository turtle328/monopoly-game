#pragma once
#include "Space.h"
#include <vector>

extern std::vector<Space*> board;

class Chance : public Space
{
public:
	void run(Player&) override;
	std::string getName() const override;
	std::vector<std::string> boardOut() const override;
private:
	void advanceToUtility(Player&);
	std::string prompt;
	std::string name{ "Chance" };
};