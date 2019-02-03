#include "Menu.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Player.h"

using namespace std;

Menu::Menu(string prompt, vector<string> menu)
{
	this->prompt = prompt;
	this->menu = menu;
}

void Menu::printMenu()
{
	system("CLS");
	string out = { monopolyText };
	out += "\n\n\n\t" + prompt + "\n\n";
	for (string option : menu)
	{
		if (option == menu[arrowLocation])
			out += "\t\t" + option + arrow + "\n";
		else
			out += "\t\t" + option + "\n";
	}
	cout << out;
}

int Menu::getChoice()
{
	int key = 0;
	printMenu();
	while (key != 13)
	{
		key = _getch();
		system("CLS");
		if (key == 224)
		{
			key = _getch();
			if (key == 72)
			{
				moveUp();
			}
			else if (key == 80)
			{
				moveDown();
			}
		}
		printMenu();
	}
	return arrowLocation;
}

string Menu::getChoiceString()
{
	int key = 0;
	printMenu();
	while (key != 13)
	{
		key = _getch();
		system("CLS");
		if (key == 224)
		{
			key = _getch();
			if (key == 72)
			{
				moveUp();
			}
			else if (key == 80)
			{
				moveDown();
			}
		}
		printMenu();
	}
	return menu[arrowLocation];
}

int Menu::getMoneyOffer(int max)
{
	int key = 0;
	int maxMoney = max;
	string message = prompt + "\nLeft Arrow to decrement, right arrow to increment"
		"\nShift modifier increments by 10's"
		"\nTab modifier increments by 100's"
		"\n\nCurrent Offer: ";
	cout << message << moneyOffer;
	while (key != 13)
	{
		key = _getch();
		system("CLS");
		if (key == 224)
		{
			key = _getch();
			if (key == 75)
			{
				if (keyDown(VK_SHIFT))
					for (int i = 0; i < 10; i++)
						left();
				else if (keyDown(VK_TAB))
					for (int i = 0; i < 100; i++)
						left();
				else
					left();
			}
			else if (key == 77)
			{
				if (keyDown(VK_SHIFT))
					for (int i = 0; i < 10; i++)
						right(max);
				else if (keyDown(VK_TAB))
					for (int i = 0; i < 100; i++)
						right(max);
				else
					right(maxMoney);
			}
		}
		cout << message << moneyOffer;
	}
	return moneyOffer;
}


int Menu::getGetchCode()
{
	int c = _getch();
	return c;
}


void Menu::moveUp()
{
	if (arrowLocation - 1 < 0)
	{
		arrowLocation = menu.size() - 1;
	}
	else
		arrowLocation -= 1;
}

void Menu::moveDown()
{
	if (arrowLocation + 1 == menu.size())
		arrowLocation = 0;
	else
		arrowLocation += 1;
}

void Menu::left()
{
	if (moneyOffer > 0)
		moneyOffer--;
}

void Menu::right(int max)
{
	if (moneyOffer < max)
		moneyOffer++;
}

bool Menu::keyDown(int key)
{
	return (GetAsyncKeyState(key));
}
