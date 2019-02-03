#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <cstdlib>
#include "Includes.h"

using namespace std;

extern vector <Space*> board{ new EmptySpace{ "Go" }, new Property{ "Mediteranean Avenue",
vector<int>{Brown, 60, 50, 2, 10, 30, 90, 160, 250} }, new CommunityChest(),
new Property{"Baltic Avenue", vector <int>{Brown, 60, 50, 4, 20, 60, 180, 320, 450}},
new IncomeTax(), new Property{"Reading Railroad", vector<int>{RailRoad, 200, 0, 0, 0, 0, 0, 0, 0}},
new Property("Oriental Avenue", vector<int>{L_Blue, 100, 50, 6, 30, 90, 270, 400, 550}), new Chance(),
new Property("Vermont Avenue", vector <int>{L_Blue, 100, 50, 6, 30, 90, 270, 400, 550}),
new Property("Connecticut Avenue", vector <int>{L_Blue, 120, 50, 8, 40, 100, 300, 450, 600 }),
new Jail(), new Property("St. Charles Place", vector <int> {Pink, 140, 100, 10, 50, 150, 450, 625, 750}),
new Property("Electric Company", vector<int> {Utility, 150, 0, 0, 0, 0, 0, 0, 0}),
new Property("States Avenue",vector<int> {Pink, 140, 100, 10, 50, 150, 450, 625, 750}),
new Property("Virginia Avenue", vector<int>{Pink, 160, 100, 12, 60, 180, 500, 700, 900}),
new Property("Pennsylvania Railroad", vector<int>{RailRoad, 200, 0, 0, 0, 0, 0, 0, 0}),
new Property("St.James Place", vector<int> {Orange, 180, 100, 14, 70, 200, 550, 750, 950 }),
new CommunityChest(), new Property("Tennessee Avenue", vector<int>{Orange, 180, 100, 14, 70, 200, 550, 750, 950}),
new Property("New York Avenue", vector <int> {Orange ,200, 100, 16, 80, 220, 600, 800, 1000}),
new EmptySpace("Free Parking"), new Property("Kentucky Avenue", vector <int>{Red, 220, 150, 18, 90, 250, 700, 875, 1050 }),
new Chance(), new Property("Indiana Avenue", vector<int> {Red, 220, 150, 18, 90, 250, 700, 875, 1050}),
new Property("Illinois Avenue", vector <int> {Red, 240, 150, 20, 100, 300, 750, 925, 1150}),
new Property("B&O Railroad", vector <int> {RailRoad, 200, 0, 0, 0, 0, 0, 0, 0}),
new Property("Atlantic Avenue", vector <int> {Yellow, 260, 150, 22, 110, 330, 800, 975, 1150}),
new Property("Ventor Avenue", vector <int> {Yellow, 260, 150, 22, 110, 330, 800, 975, 1150}),
new Property("Water Works", vector <int> {Utility, 150, 0, 0, 0, 0, 0, 0, 0}),
new Property("Marvin Gardens", vector <int> {Yellow, 280, 150, 24, 120, 360, 850, 1025, 1200}),
new GoToJail(), new Property("Pacific Avenue", vector <int> {Green, 300, 200, 26, 130, 390, 900, 1100, 1275 }),
new Property("North Carolina Avenue", vector <int>{Green, 300, 200, 26, 130, 390, 900, 1100, 1275}),
new CommunityChest(), new Property("Pennsylvania Avenue", vector <int> {Green, 320, 200, 28, 150, 450, 1000, 1200, 1400}),
new Property("Short Line", vector <int> {RailRoad, 200, 0, 0, 0, 0, 0, 0, 0}),
new Chance(), new Property("Park Place", vector <int> {D_Blue, 350, 200, 35, 175, 500, 1100, 1300, 1500}),
new LuxuryTax(), new Property("Boardwalk", vector <int> {D_Blue, 400, 200, 50, 200, 600, 1400, 1700, 2000 }) };

extern vector <Player> players{};
extern Player& curPlayer = Player("");
extern vector <string> menuDisplay{};
extern Dice d{};

bool playersSort(Player a, Player b) { return a.getCurDiceRoll() > b.getCurDiceRoll(); }
bool propertySort(Property* a, Property* b) { return a->getGroup() <  b->getGroup(); }

char getInput(Player& p)
{
	char keyPressed;
	vector <char> validControls{ ' ', 'p', 'v', 't', 'd' };
	vector <string> controlsDisplay{ " ", "P to manage properties", "V to view properties", "T to trade", "D for debug/cheats" };

	if (p.checkDebt())
	{
		validControls[0] = 'c';
		controlsDisplay[0] = "C to declare bankruptcy";
	}

	else if (p.jailed && p.canRoll)
	{
		validControls[0] = 'j';
		controlsDisplay[0] = "J to enter jail menu";
	}

	else if (p.canRoll)
	{
		validControls[0] = 'r';
		controlsDisplay[0] = "R to roll";
	}
	else
	{
		validControls[0] = 'e';
		controlsDisplay[0] = "E to end turn";
	}

	menuDisplay.push_back("Name: " + p.getName());
	menuDisplay.push_back("Current Money: $" + to_string(p.getCurMoney()));
	menuDisplay.push_back("Current location: " + board[p.getLocation()]->getName());
	menuDisplay.push_back("");
	menuDisplay.push_back("Controls");

	for (string controlToDisplay : controlsDisplay)
		menuDisplay.push_back(controlToDisplay);

	displayBoard();

	while (true)
	{
		keyPressed = _getch();

		for (char validControl : validControls)
		{
			if (keyPressed == validControl)
				return keyPressed;
		}
	}
}

void initPlayers()
{
	vector <string> playerChoices{ "2 Players", "3 Players", "4 Players", "5 Players","6 Players" };
	Menu playerMenu("How many players are going to play?", playerChoices);
	int numPlayers = playerMenu.getChoice() + 2;

	for (int i = 1; i <= numPlayers; i++)
	{
		players.push_back(Player("Player " + to_string(i)));
	}

	system("CLS");

	cout << monopolyText << endl;

	int i = 0;

	for (Player& p : players)
	{
		bool uniqueName;
		bool blankName;
		i++;
		do
		{
			uniqueName = true;
			blankName = false;
			string name = "";

			cout << p.getName() + " what's your name?: ";
			getline(cin, name);
			p.setName(name);

			for (Player& pl : players)
				if (p.getName() == pl.getName() && &p != &pl)
					uniqueName = false;

			if (!uniqueName)
			{
				cout << "Please give a unique name." << endl;
				p.setName("Player " + to_string(i));
			}

			if (name == "")
			{
				cout << "Please give a name." << endl;
				p.setName("Player " + to_string(i));
				blankName = true;
			}

			cout << endl;

		} while (!uniqueName || blankName);
	}

	system("CLS");
	cout << monopolyText << endl;

	for (Player& player : players)
	{
		player.rollDice(d, true);
	}

	sort(players.begin(), players.end(), playersSort);

	i = 0;
	for (Player& player : players)
	{
		player.setPlayerNum(i);
		i++;
	}

	cout << "\n" << players[0].getName() << " goes first." << endl;
	cout << players[1].getName() << " goes second." << endl;
	if (2 < players.size())
	{
		cout << players[2].getName() << " goes third." << endl;
		if (3 < players.size())
		{
			cout << players[3].getName() << " goes fourth." << endl;
			if (4 < players.size())
			{
				cout << players[4].getName() << " goes fifth." << endl;
				if (5 < players.size())
				{
					cout << players[5].getName() << " goes sixth." << endl;
				}
			}
		}
	}

	cout << endl;
	system("pause");
	system("CLS");
}

void rollDice(Player& p, int numRolls)
{
	p.rollDice(d);
	p.canRoll = false;

	menuDisplay.push_back("");

	if (d.isDouble && numRolls == 3)
	{
		menuDisplay.push_back("You've rolled doubles three times in a row, go to jail.");
		p.goToJail();
		menuDisplay.push_back("Press any key to continue");
		system("pause");
		return;
	}

	else if (d.isDouble)
	{
		menuDisplay.push_back("You rolled a double! You can roll the dice again!");
		p.canRoll = true;
	}


	p.move(p.getCurDiceRoll());

	Space* s = board[p.getLocation()];
	bool isUnownedProperty = false;

	if (Property* prop = dynamic_cast<Property*>(s))
	{
		if (prop->getOwner() == nullptr)
			isUnownedProperty = true;
	}

	menuDisplay.push_back(p.getName() + " rolls a " + to_string(d.getDice1Result()) + " and " + to_string(d.getDice2Result()));
	menuDisplay.push_back("");
	menuDisplay.push_back(p.getName() + " lands on the " + board[p.getLocation()]->getName() + " space.");
	menuDisplay.push_back("");
	if (!isUnownedProperty)
		board[p.getLocation()]->run(p);
	menuDisplay.push_back("Press any key to continue.");
	curPlayer = p;
	displayBoard();
	system("pause");
	if (isUnownedProperty)
		board[p.getLocation()]->run(p);
	system("CLS");
}

array<int, 2> getPropertyChoice(string prompt, vector<Property*>& properties, bool isManage=false)
{
	system("CLS");
	vector <string> propPrompt{};
	sort(properties.begin(), properties.end(), propertySort);
	prompt += "\n\t\tProperty Name\t\tGroup\t\tPrice\tIs Mortgaged\tHouse Cost\tNum Houses"
		"\tHas Hotel\tRent\tHouse 1\tHouse 2\tHouse 3\tHouse 4\tHotel\n";
	for (Property* p : properties)
	{
		ostringstream os;
		auto rentArray = p->getRentArray();
		os << left << boolalpha << setw(24) << p->getName() << setw(12) << p->getGroupString() << "\t" << p->getPrice()
			<< "\t" << p->mortgaged << "\t\t" << p->getBuildingCost() << "\t\t" << p->getHouses() << "\t\t" << p->hasHotel() << "\t\t" << rentArray[0] << "\t" << rentArray[1] << "\t"
			<< rentArray[2] << "\t" << rentArray[3] << "\t" << rentArray[4] << "\t" << rentArray[5];
		propPrompt.push_back(os.str());
	}
	if (!(isManage))
	{
		propPrompt.push_back("\n\t\tConfirm");
		propPrompt.push_back("Cancel");
	}
	else
		propPrompt.push_back("\n\t\tExit");

	Menu propertyPickMenu{ prompt, propPrompt };

	int choice = propertyPickMenu.getChoice();
	int vectorSize = propPrompt.size();

	// first variable is int choice, and the second variable is int size of string vector
	array<int, 2> choiceSize{ choice, vectorSize };
	return choiceSize;
}

void viewProperties()
{
	string prompt = "Select a player to view their properties";
	vector<string> playerNames{};
	for (Player& p : players)
	{
		if (!p.bankrupt)
			playerNames.push_back(p.getName());
	}
	Menu propertiesMenuSelection{ prompt, playerNames };
	string playerChoice = propertiesMenuSelection.getChoiceString();

	Player* player = nullptr;

	for (Player& p : players)
	{
		if (p.getName() == playerChoice)
			player = &p;
	}

	auto propertiesOfSelectedPlayer = player->getOwnedProperties();
	sort(propertiesOfSelectedPlayer.begin(), propertiesOfSelectedPlayer.end(), propertySort);

	system("CLS");

	cout << "Name: " << player->getName() << endl;
	cout << "Current $$$: $" << player->getCurMoney() << endl;

	if (!(propertiesOfSelectedPlayer.size() == 0))
	{
		cout << "\nProperty Name\t\tGroup\t\tPrice\tIs Mortgaged\tHouse Cost\tNum Houses\tHas Hotel\tRent\tHouse 1\tHouse 2\tHouse 3\tHouse 4\tHotel\n" << endl;
		for (Property* p : propertiesOfSelectedPlayer)
		{
			auto rentArray = p->getRentArray();
			cout << left << boolalpha << setw(24) << p->getName() << setw(12) << p->getGroupString() << "\t" << p->getPrice()
			<< "\t" << p->mortgaged << "\t\t" << p->getBuildingCost() << "\t\t" << p->getHouses() << "\t\t" << p->hasHotel() << "\t\t" << rentArray[0] << "\t" << rentArray[1] << "\t"
			<< rentArray[2] << "\t" <<  rentArray[3] << "\t" << rentArray[4] << "\t" << rentArray[5] << endl;
		}
	}
	else
		cout << "\nThis player doesn't own any properties yet." << endl;
	
	cout << endl;
	system("pause");
}

void manageProperties(Player& p)
{
	while (true)
	{
		string prompt = "Select a property to buy houses, sell houses, or mortgage.\n";
		vector<Property*>& ownedProperties = p.getOwnedProperties();

		array<int, 2> choiceSize = getPropertyChoice(prompt, ownedProperties, true);

		int choice = choiceSize[0];
		int stringVectorSize = choiceSize[1];


		// if exit
		if (stringVectorSize == 0)
		{
			cout << "You don't own any properties yet." << endl;
			cout << endl;
			system("pause");
			break;
		}

		else if (choice + 1 != stringVectorSize)
		{
			int choice2 = -1;
			while (true)
			{
				system("CLS");
				string prompt2 = ownedProperties[choice]->toString(true) + "\n\n";
				vector<string> choices = { "Buy House", "Sell House", "Mortgage/Unmortgage", "Exit" };
				Menu manageMenu{ prompt2, choices };
				choice2 = manageMenu.getChoice();

				cout << endl;

				if (choice2 == 0)
				{
					p.buyBuilding(*ownedProperties[choice]);
				}
				else if (choice2 == 1)
				{
					p.sellBuilding(*ownedProperties[choice]);
				}
				else if (choice2 == 2)
				{
					p.mortgage(*ownedProperties[choice]);
				}

				if (choice2 == 3)
				{
					system("CLS");
					break;
				}
				else
				{
					cout << endl;
					system("pause");
				}
			}
		}
		else
			break;
	}
}

void trade(Player& p)
{
	string prompt = "Select a player to trade with";
	vector<string> playerNames{};
	
	for (Player& pString : players)
	{
		if (pString.getName() != p.getName() && !pString.bankrupt)
			playerNames.push_back(pString.getName());
	}

	Menu propertiesMenuSelection{ prompt, playerNames };
	
	string playerChoice = propertiesMenuSelection.getChoiceString();

	Player* playerPtr = nullptr;

	for (Player& p : players)
	{
		if (p.getName() == playerChoice)
			playerPtr = &p;
	}

	vector<Property*>& properties = playerPtr->getOwnedProperties();
	vector<Property*>& yourProps = p.getOwnedProperties();

	vector <Property*> tradeWanted{};
	vector <Property*> tradeOffer{};

	while (true)
	{
		string prompt = "Select properties you want from this player, confirm to continue to money offer\n";

		array<int, 2> choiceSize = getPropertyChoice(prompt, properties);

		int choice = choiceSize[0];
		int stringVectorSize = choiceSize[1];

		if (choice + 1 == stringVectorSize) // if exit
		{
			exit:
			for (Property* p : tradeWanted)
			{
				properties.push_back(p);
			}

			for (Property* p : tradeOffer)
			{
				yourProps.push_back(p);
			}

			cout << "You decide to bail out on the trade." << endl;
			system("pause");
			break;
		}

		else if (choice + 2 == stringVectorSize) // if confirm
		{
			system("CLS");
			int moneyWant;
			Menu money{ "How much money do you want from this player?\n" };

			moneyWant = money.getMoneyOffer(playerPtr->getCurMoney());
		
			string prompt = "What are you willing to offer? Confirm to continue with your money offer.";


			while (true)
			{
				auto choiceSize = getPropertyChoice(prompt, yourProps);

				int choice = choiceSize[0];
				int stringVectorSize = choiceSize[1];

				if (choice + 1 == stringVectorSize) // if cancel
				{
					goto exit;
				}

				else if (choice + 2 == stringVectorSize) // if confirm
				{
					system("CLS");
					int moneyOffer;
					Menu money{ "How much money are you willing to offer?\n" };

					moneyOffer = money.getMoneyOffer(p.getCurMoney());

					string propertiesWanted = "";

					for (Property* p : tradeWanted)
					{
						propertiesWanted += p->getName() + " ";
					}

					string propertiesOffered = "";

					for (Property* pr : tradeOffer)
					{
						propertiesOffered += pr->getName() + " ";
					}

					// get confirmation
					system("CLS");
					string prompt = "Are these terms to your liking " + playerPtr->getName()  + "?\n\n";
					prompt += p.getName() + " wants these items from " + playerPtr->getName() + "\n";
					prompt += "Cash: $" + to_string(moneyWant) + "\n";
					prompt += "Properties wanted: " + propertiesWanted + "\n\n";
					prompt += p.getName() + "'s offer\n";
					prompt += "Cash: $" + to_string(moneyOffer) + "\n";
					prompt += "Properties offered: " + propertiesOffered + "\n";

					vector <string> confirm{ "Accept", "Refuse" };

					Menu tradeMenu{ prompt, confirm };

					int choice = tradeMenu.getChoice();

					if (choice == 0)
					{
						cout << "\n" << playerPtr->getName() << " has accepted the trade, money and properties will now be exchanged!" << endl;
						
						for (Property* pr : tradeWanted)
						{
							yourProps.push_back(pr);
							pr->setOwner(&p);
						}

						for (Property* pr : tradeOffer)
						{
							properties.push_back(pr);
							pr->setOwner(playerPtr);
						}

						p.addMoney(moneyWant);
						playerPtr->subtractMoney(moneyWant);

						playerPtr->addMoney(moneyOffer);
						p.subtractMoney(moneyOffer);
						
						system("pause");

						return;
					}
					else
					{
						for (Property* p : tradeWanted)
						{
							properties.push_back(p);
						}

						for (Property* p : tradeOffer)
						{
							yourProps.push_back(p);
						}

						cout << "The offer has been refused." << endl;
						system("pause");
						return;
					}
				}

				else
				{
					tradeOffer.push_back(yourProps[choice]);
					yourProps.erase(yourProps.begin() + choice);
				}
			}
		}

		else
		{
			tradeWanted.push_back(properties[choice]);
			properties.erase(properties.begin() + choice);
		}
	}
}

void debugMenu(Player& p)
{
	string prompt = "\tCheats\n";
	vector<string> choices = { "Add/Steal property", "Auction a property", "Add buildings to property", "Remove buildings from property", "Goto space", "Inject cash", "Subtract cash", "Madoff", "Exit" };
	Menu cheatMenu{ prompt, choices };

	int choice = cheatMenu.getChoice();

	cout << endl;

	if (choice == 0)
	{
		int boardNumber = -1;

		while (!(boardNumber >= 0 && boardNumber <= 39))
		{
			cout << "\nGive a number between 0-39: ";
			cin >> boardNumber;
		}
		Space* s = board[boardNumber];
		if (Property* prop = dynamic_cast<Property*>(s))
		{
			cout << "You attempt to take the " << prop->getName() << endl;
			
			if (prop->getOwner() == nullptr)
			{
				cout << "You add the " << prop->getName() << " to your owned properties." << endl;
				prop->setOwner(&p);
				p.addProperty(*prop);
			}

			else if (prop->getOwner() == &p)
				cout << "You already own this property." << endl;

			else
			{
				cout << "You steal the " << prop->getName() << " from " << prop->getOwner()->getName() << endl;
				prop->getOwner()->removeProperty(*prop);
				p.addProperty(*prop);
				prop->setOwner(&p);
			}
		}
		else
			cout << "This space is not a property." << endl;
	}
	else if (choice == 1)
	{
		int boardNumber = -1;

		while (!(boardNumber >= 0 && boardNumber <= 39))
		{
			cout << "\nGive a number between 0-39: ";
			cin >> boardNumber;
		}
		Space* s = board[boardNumber];
		if (Property* prop = dynamic_cast<Property*>(s))
		{
			prop->auction();
			return;
		}
		else
			cout << "This space is not a property." << endl;
	}
	else if (choice == 2)
	{
		int boardNumber = -1;

		while (!(boardNumber >= 0 && boardNumber <= 39))
		{
			cout << "\nGive a number between 0-39: ";
			cin >> boardNumber;
		}

		Space* s = board[boardNumber];
		if (Property* prop = dynamic_cast<Property*>(s))
		{
			cout << "How many buildings do you want to add to " << prop->getName() << "?: ";
			int numBuildings;
			cin >> numBuildings;

			while (numBuildings < 0)
			{
				cout << "Please give a positive number.";
				cin >> numBuildings;
			}
			
			if (numBuildings > 5)
				numBuildings = 5;

			cout << "You add " << numBuildings << " buildings" << endl;

			for (int i = 0; i < numBuildings; i++)
				if (prop->getBuildings() < 5)
					prop->buyBuilding();

			if (prop->hasHotel())
				cout << "The property now has a hotel." << endl;
			else
				cout << "The property now has " << prop->getHouses() << " houses." << endl;
		}
	}
	else if (choice == 3)
	{
		int boardNumber = -1;

		while (!(boardNumber >= 0 && boardNumber <= 39))
		{
			cout << "\nGive a number between 0-39: ";
			cin >> boardNumber;
		}

		Space* s = board[boardNumber];
		if (Property* prop = dynamic_cast<Property*>(s))
		{
			cout << "How many buildings do you want to remove from " << prop->getName() << "?: ";
			int numBuildings;
			cin >> numBuildings;

			while (numBuildings < 0)
			{
				cout << "Please give a positive number.";
				cin >> numBuildings;
			}

			if (numBuildings > 5)
				numBuildings = 5;

			cout << "You remove " << numBuildings << " buildings" << endl;

			for (int i = 0; i < numBuildings; i++)
				if (prop->getBuildings() > 0)
					prop->sellBuilding();

			if (prop->hasHotel())
				cout << "The property now has a hotel." << endl;
			else
				cout << "The property now has " << prop->getHouses() << " houses." << endl;
		}
	}
	else if (choice == 4)
	{
		int boardNumber = -1;

		while (!(boardNumber >= 0 && boardNumber <= 39))
		{
			cout << "\nGive a number between 0-39: ";
			cin >> boardNumber;
		}
		p.setLocation(boardNumber);
		menuDisplay.push_back("");
		menuDisplay.push_back("You go to the " + board[p.getLocation()]->getName() + " space.");
		board[p.getLocation()]->run(p);
		displayBoard();
	}
	else if (choice == 5)
	{
		int cashInjection;
		cout << "How much cash you want to inject?: ";
		cin >> cashInjection;
		while (cashInjection < 0)
		{
			cout << "\nPlease give a positive number: ";
			cin >> cashInjection;
		}

		p.addMoney(cashInjection);

		cout << "You gain $" << cashInjection << " you now have $" << p.getCurMoney() << endl;
	}
	else if (choice == 6)
	{
		int cashSubtraction;
		cout << "How much cash you want to subtract?: ";
		cin >> cashSubtraction;
		while (cashSubtraction < 0)
		{
			cout << "\nPlease give a positive number: ";
			cin >> cashSubtraction;
		}

		p.subtractMoney(cashSubtraction);

		cout << "You lose $" << cashSubtraction << " you now have $" << p.getCurMoney() << endl;
	}
	else if (choice == 7)
	{
		cout << "You steal everyone's money!" << endl;
		
		for (Player& pl : players)
			if (&p != &pl && !pl.bankrupt)
			{
				int totalMoney = pl.getCurMoney();
				pl.subtractMoney(totalMoney);
				p.addMoney(totalMoney);
			}
	}
	else return;

	system("pause");
}

void declareBankruptcy(Player& p)
{
	menuDisplay.clear();
	Space* s = board[p.getLocation()];
	Player* creditor = nullptr;

	string person{ "the Bank" };

	if (Property* p = dynamic_cast<Property*>(s))
	{
		creditor = p->getOwner();
		person = creditor->getName();
	}

	menuDisplay.push_back("You didn't manage to gather enough money to get out of debt.");
	menuDisplay.push_back(person + " will recieve all your assets.");
	menuDisplay.push_back("Thanks for playing " + p.getName() + "!");

	p.bankrupt = true;

	if (creditor == nullptr)
	{
		menuDisplay.push_back("The bank unmortgages all of " + p.getName() + "'s properties"); 
		menuDisplay.push_back("and auctions them one by one.");
		menuDisplay.push_back("Press any key to continue.");
		displayBoard();

		system("pause");

		for (Property* prop : p.getOwnedProperties())
		{
			prop->mortgaged = false;
			prop->auction();
		}
	}

	else
	{
		menuDisplay.push_back(creditor->getName() + " recieves all of your properties.");
		
		for (Property* prop : p.getOwnedProperties())
		{
			creditor->addProperty(*prop);
			prop->setOwner(creditor);
			p.removeProperty(*prop);
		}

		menuDisplay.push_back("Press any key to continue.");

		system("pause");
	}
}

bool gameEnd()
{
	int totalPlayers = players.size();
	int totalBankrupt = 0;
	for (Player& p : players)
	{
		bool bankrupt = p.bankrupt;
		if (bankrupt)
			totalBankrupt++;
	}
	if (totalPlayers - totalBankrupt == 1)
		return true;

	else return false;
}

int main()
{
	initPlayers();

	//players[0].setLocation(39);
	//players[0].jailed = true;
	//players[1].setLocation(39);
	//players[2].setLocation(7);

	while (!gameEnd())
	{
		for (Player& p : players)
		{
			bool turnEnd = false;
			int numRolls = 0;
			p.canRoll = true;
			while (!turnEnd  && !gameEnd() && !p.bankrupt)
			{
				curPlayer = p;
				char action = getInput(p);

				if (action == 'r')
					rollDice(p, ++numRolls);
				else if (action == 'j')
				{
					p.canRoll = false;
					board[p.getLocation()]->run(p);
				}
				else if (action == 'e')
					turnEnd = true;
				else if (action == 'c')
				{
					declareBankruptcy(p);
					turnEnd = true;
				}
				else if (action == 'p')
					manageProperties(p);
				else if (action == 'v')
					viewProperties();
				else if (action == 't')
					trade(p);
				else if (action == 'd')
					debugMenu(p);
				else if (action == 'b')
					displayBoard();
				menuDisplay.clear();
			}
		}
	}

	system("CLS");

	Player* winner = nullptr;
	for (Player& p : players)
	{
		if (!p.bankrupt)
			winner = &p;
	}

	cout << monopolyText << endl;
	cout << "Congratulations " << winner->getName() << "! You have won!" << endl;
	cout << "\nPlayer Stats" << endl;
	cout << winner->toString() << endl;

	for (int i = 0; i < board.size(); i++) // deallocate pointers
	{
		delete board[i];
	}

	cout << endl;
	system("pause");
}