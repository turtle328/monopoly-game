#include "Dice.h"
#include <iostream>
using namespace std;

int Dice::rollDice(std::string name, bool checkFirst)
{
	isDouble = false;
	d1 = rollDie();
	d2 = rollDie();
	total = d1 + d2;
	if (d1 == d2)
		isDouble = true;
	if (checkFirst)
		cout << name << " rolls a " << d1 << " and a " << d2 << " for a total of " << total << endl;
	return total;
}

int Dice::getDice1Result()
{
	return d1;
}

int Dice::getDice2Result()
{
	return d2;
}

int Dice::getTotal()
{
	return total;
}

int Dice::rollDie()
{
	return distribution(generator);
}