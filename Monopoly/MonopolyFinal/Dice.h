#pragma once
#include <string>
#include <random>
#include <ctime>

class Dice
{
public:
	int rollDice(std::string, bool=false);
	bool isDouble;
	int getDice1Result();
	int getDice2Result();
	int getTotal();
private:
	int rollDie();
	int d1;
	int d2;
	int total;
	std::default_random_engine generator{ static_cast<unsigned int> (time(0)) };
	std::uniform_int_distribution<int> distribution{ 1, 6 };
};