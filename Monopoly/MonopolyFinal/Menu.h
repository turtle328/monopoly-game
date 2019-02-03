#pragma once
#include <string>
#include <vector>

class Menu
{
public:
	Menu(std::string prompt = "", std::vector<std::string> menu = std::vector<std::string>{ "" });
	int getChoice();
	std::string getChoiceString();
	int getMoneyOffer(int max);
	static int getGetchCode();

private:
	const std::string arrow{ " <" };
	int arrowLocation{ 0 };
	int moneyOffer{ 0 };
	std::string prompt;
	std::vector <std::string> menu;
	void printMenu();
	void moveUp();
	void moveDown();
	void left();
	void right(int max);
	bool keyDown(int key);
	std::string monopolyText = R"( __       __                                                    __           
|  \     /  \                                                  |  \          
| $$\   /  $$  ______   _______    ______    ______    ______  | $$ __    __ 
| $$$\ /  $$$ /      \ |       \  /      \  /      \  /      \ | $$|  \  |  \
| $$$$\  $$$$|  $$$$$$\| $$$$$$$\|  $$$$$$\|  $$$$$$\|  $$$$$$\| $$| $$  | $$
| $$\$$ $$ $$| $$  | $$| $$  | $$| $$  | $$| $$  | $$| $$  | $$| $$| $$  | $$
| $$ \$$$| $$| $$__/ $$| $$  | $$| $$__/ $$| $$__/ $$| $$__/ $$| $$| $$__/ $$
| $$  \$ | $$ \$$    $$| $$  | $$ \$$    $$| $$    $$ \$$    $$| $$ \$$    $$
 \$$      \$$  \$$$$$$  \$$   \$$  \$$$$$$ | $$$$$$$   \$$$$$$  \$$ _\$$$$$$$
                                           | $$                    |  \__| $$
                                           | $$                     \$$    $$
                                            \$$                      \$$$$$$ )";
};