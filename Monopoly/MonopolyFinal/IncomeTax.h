#pragma once
#include "Space.h"

class IncomeTax : public Space
{
public:
	void run(Player&) override;
	std::string getName() const override;
	std::vector<std::string> boardOut() const override;
private:
	std::string name{ "Income Tax" };
};