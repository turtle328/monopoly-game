#pragma once
#include <array>
#include "Space.h"

class Jail : public Space
{
public:
	void run(Player&) override;
	std::string getName() const override;
	std::vector<std::string> boardOut() const override;
private:
	std::string name{ "Jail" };
	std::array<int, 6> tries{};
	void removeFromJail(Player&);
};