#include "Jail.h"
#include "Player.h"
#include "Menu.h"
#include "Dice.h"
#include <iostream>
#include <vector>
using namespace std;

extern vector<Space*> board;
extern vector<string> menuDisplay;
void Jail::run(Player& p)
{
	if (p.jailed)
	{
		if (p.hasJailFreeCard)
		{
			cout << "You use a get out of jail free card." << endl;
			removeFromJail(p);
			p.hasJailFreeCard = false;
			p.canRoll = true;
		}
		else
		{
			string prompt = p.getName() + " you are currently in jail. What would you like to do?\n";
			vector<string> jailOptions{ "Roll for doubles - tries: " + to_string(tries[p.getPlayerNum()]) + "/3", "Pay the $50 bail"};
			Menu jailMenu{ prompt, jailOptions };
			int choice = jailMenu.getChoice();

			cout << endl;

			if (choice == 0)
			{
				Dice d{};
				int num = d.rollDice(p.getName());
				tries[p.getPlayerNum()]++;
				if (d.isDouble)
				{
					cout << "You successfully rolled a double!" << endl;
					removeFromJail(p);
					cout << "You move by " << num << " spaces." << endl;
					system("CLS");
					p.move(num);
					board[p.getLocation()]->run(p);
				}
				else if (tries[p.getPlayerNum()] == 3)
				{
					cout << "You have run out of attempts. You paid the $50 bail instead." << endl;
					p.subtractMoney(50);
					removeFromJail(p);
					p.canRoll = true;
				}
				else
				{
					int triesLeft = 3 - tries[p.getPlayerNum()];
					cout << "You failed to roll doubles " << triesLeft << " tries left." << endl;
				}
			}
			else if (choice == 1)
			{
				cout << "You paid the bail to get out of jail." << endl;
				p.subtractMoney(50);
				removeFromJail(p);
				p.canRoll = true;
			}
		}
		system("pause");
	}
	else
	{
		
		menuDisplay.push_back(p.getName() + " visits the jail.");
		menuDisplay.push_back("glad your not on the other side of the bars!");
		menuDisplay.push_back("");
	}
}

std::string Jail::getName() const
{
	return name;
}

std::vector<std::string> Jail::boardOut() const
{
	return std::vector<std::string>();
}

void Jail::removeFromJail(Player& p)
{
	p.jailed = false;
	tries[p.getPlayerNum()] = 0;
}
