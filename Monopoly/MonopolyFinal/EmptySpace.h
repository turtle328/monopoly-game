#pragma once
#include "Space.h"

class EmptySpace : public Space
{
public:
	explicit EmptySpace(std::string name);
	void run(Player&) override;
	std::string getName() const override;
	std::vector<std::string> boardOut() const override;
private:
	std::string name;
};