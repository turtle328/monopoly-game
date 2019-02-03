#include <iostream>
#include <cstdlib>
#include <string>
#include<array>
#include<vector>
#include<windows.h>
#include "Player.h"
#include "board_out.h"
#include "Groups.h"
#include "Dice.h"
using namespace std;

//----Player vector
extern vector<Player> players;
extern vector <Space*> board;
extern Player& curPlayer;
extern vector <string> menuDisplay;
extern Dice d;
//----Board Dimensions
const int xSize = 64;
const int ySize = 192;
//----Space Dimensions
const int spaceX = 4;
const int spaceY = 13;

int group;
//---Strings
const string MONOPOLY = "MONOPOLY";
const string CURROLL = "CURRENT ROLL";
string propTitle = "";
string price = "";
string rent = "";
string house1 = "";
string house2 = "";
string house3 = "";
string house4 = "";
string w_hotel = "";
string hcost = "";
string Hcost = "";
//---STREETS
string pOne = "Mediterranean";
string pTwo = "Baltic";
string pThree = "Oriental";
string pFour = "Vermont";
string pFive = "Connecticut";
string pSix = "St. Charles";
string pSeven = "States";
string pEight = "Virginia";
string pNine = "St. James";
string pTen = "Tenessee";
string pEleven = "New York";
string pTwelve = "Kentucky";
string pThirteen = "Indiana";
string pFourteen = "Illinois";
string pFifteen = "Atlantic";
string pSixteen = "Ventor";
string pSeventeen = "Marvin";
string pEighteen = "Pacific";
string pNineteen = "N. Carolina";
string pTwenty = "Pennsylvania";
string pTwentyOne = "Park";
string pTwentyTwo = "BoardWalk";
string daMan[11] = {
	"            .---.                               .---.",
	"            |#__|                               |#__|",
	"           =;===;=                             =;===;=",
	"           / - - \\         BANKRUPTED          / - - \\",
	"          ( _'.'_ )              PLAYERS      ( _'.'_ )",
	"       . - `-'^' - `-.                     . - `-'^' - `-.",
	"      |     `>o<'     |                   |     `>o<'     |",
	"      /       :       \\                   /       :       \\",
	"     / /\\     :    /\\ \\                  / /\\     :    /\\ \\",
	"  .-'-/ /    .-.   \\ \\-'-.            .-'-/ /    .-.   \\ \\-'-.",
	"   |_/ /-'        '-\\ \\_|              |_/ /-'        '-\\ \\_|" };
string dieONE[4] = {
	" ______",
	"|      |",
	"|   0  |",
	"|______|" };
string dieTWO[4] = {
	" ______",
	"|     0|",
	"|      |",
	"|0_____|" };
string dieTHR[4] = {
	" ______",
	"|     0|",
	"|   0  |",
	"|0_____|" };
string dieFOU[4] = {
	" ______",
	"|0    0|",
	"|      |",
	"|0____0|" };
string dieFIV[4] = {
	" ______",
	"|0    0|",
	"|  0   |",
	"|0____0|" };
string dieSIX[4] = {
	" ______",
	"|0    0|",
	"|0    0|",
	"|0____0|" };
string dieART[8] = {
	"   _______",
	"  /\\ o o o\\",
	" / o\\ o o o\\_______",
	"<    >------>  o  / |",
	" \\ o /   o  /____/ o|",
	"  \\ /______/     |oo|",
	"         |   o   |o/",
	"         |_______|/"
};
string colors[8] = { "Brown", "Light Blue", "Pink", "Orange", "Red", "Yellow", "Green", "Dark Blue" };
//--GO Corner
string GO[8] = { " _____ _____     ^^",
"|  __ \\  _  |$   ^^",
"| | _\\/ | | | 2  ^^",
"| |_\\ \\ \\_/ /  0 ^^",
" \\____/\\___/    0^^",
"                 ^^",
"   COLLECT       ^^" };
//--goto JAIL Corner
string gotoJail[4] = { " GO TO JAIL! ",
"    _*_.oOO0 ",
" __/_|_\\__   ",
"[(o)_M_(o)]  " };
//--Free Parking Corner
string freeParking[5] = { "FREE         ",
"  ___PARKING ",
" /___\\       ",
".\" | \".      ",
"(0_|_0)      " };
//--BCHC
string bchc[4] = { "J| | | | | | ",
"U -----------",
"S            ",
"T___VISITING_" };
//--Community Chest
string comChest[6] = { "     \\|/     ",
"     /$\\     ",
"    ($$$)    ",
"             " ,
"COMMUNITY",
"CHEST    " };
//--Chance
string chance[5] = { "?????????   ?",
"????????? ? ?",
"?????????? ??",
"          o  " ,
"CHANCE" };
//--Electric Company
string electricCO[4] = { " ELECTRIC    ",
" \\|/ COMPANY ",
" (+)         ",
"  8          " };
//--Water Works
string h2o[4] = { "---+  WATER  ",
"--\\ \\  WORKS ",
" ~||||~      ",
"(((())))     " };
//--Rail Road
string railRoad[7] = { "____  Reading",
"____     Penn",
"____      B&O",
"___Short Line",
"|DD|____T_  R",
"|_      _|< R",
"@-@@-oOWNED: " };
//--Inc/Lux Tax
string luxTax[4] = { "$ Luxury $$$$",
"$$ Tax PAY $$",
"$$$ $100 $$$$",
"$$$        $$" };
string incTax[4] = { "$ Income $$$$",
"$$ Tax PAY $$",
"$$$ $200 $$$$",
"$$$        $$" };
//--Buildings
string houseOne[2] = { "/^\\","|_|" };
string houseTwo[2] = { "/^\\/^\\","|_||_|" };
string houseThree[2] = { "/^\\/^\\/^\\","|_||_||_|" };
string houseFour[2] = { "/^\\/^\\/^\\/^\\","|_||_||_||_|" };
string hotel[2] = { "/^^^^^^^^^^\\","|[]__[]__[]|" };
int buildings[23] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

int ply1LOC = -1;
int ply2LOC = -1;
int ply3LOC = -1;
int ply4LOC = -1;
int ply5LOC = -1;
int ply6LOC = -1;

string boardScreen[xSize][ySize];

void createBoard()
{
	//---Creation
	for (int x = 0; x < xSize; x++)
	{
		for (int y = 0; y < ySize; y++)
		{
			//-----Base Lines
			if (y == 159 && x > 1 && x < 52) boardScreen[x][y] = "|";
			else if (y == 163 && x > 51 && x < 60) boardScreen[x][y] = "|";
			else if (y == 165 && x > 52 && x < 61) boardScreen[x][y] = "|";
			else if (x == 0 && y > 17 && y < 158)boardScreen[x][y] = "_";
			else if (y == 158 && x > 0 && x < 52)boardScreen[x][y] = "\\";
			else if (y == 164 && x > 51 && x < 61)boardScreen[x][y] = "\\";
			else if (x == 58 && y > 4 && y < 143) boardScreen[x][y] = "-";

			//-----Game Board
			else if (y == 3 && x < 57)boardScreen[x][y] = "|";
			else if (y == 157 && x > 1 && x < 52)boardScreen[x][y] = "|";
			else if (y == 17 && x < 56)boardScreen[x][y] = "|";
			else if (y == 18 && x > 6 && x < 51)boardScreen[x][y] = "\\";
			else if (y == 19 && x > 7 && x < 51)boardScreen[x][y] = "|";
			else if (y == 143 && x > 1 && x < 60)boardScreen[x][y] = "|";
			else if (x == 0 && y > 3 && y < 17)boardScreen[x][y] = "H";
			else if (x == 1 && y > 17 && y < 157)boardScreen[x][y] = "H";
			else if (x == 7 && y > 18 && y < 143)boardScreen[x][y] = "\\";
			else if (x == 8 && y > 19 && y < 143)boardScreen[x][y] = "-";
			else if (x == 56 && y > 3 && y < 143)boardScreen[x][y] = "H";
			else if (x == 6 && y > 17 && y < 143)boardScreen[x][y] = "H";
			else if (x == 51 && y > 17 && y < 143)boardScreen[x][y] = "H";
			else if (x == 57 && y > 3 && y < 143)boardScreen[x][y] = "\\";
			else if (x == 9 && y >= 75 && y <= 138)boardScreen[x][y] = "_";
			else if (x == 33 && y > 75 && y < 138)boardScreen[x][y] = "_";
			else if (y == 75 && x >= 9 && x < 34)boardScreen[x][y] = "|";
			else if (y == 138 && x >= 9 && x < 34)boardScreen[x][y] = "|";

			//-----Squares
			else if (y == 31 && x > 1 && x < 6)boardScreen[x][y] = "|";
			else if (y == 45 && x > 1 && x < 6)boardScreen[x][y] = "|";
			else if (y == 59 && x > 1 && x < 6)boardScreen[x][y] = "|";
			else if (y == 73 && x > 1 && x < 6)boardScreen[x][y] = "|";
			else if (y == 87 && x > 1 && x < 6)boardScreen[x][y] = "|";
			else if (y == 101 && x > 1 && x < 6)boardScreen[x][y] = "|";
			else if (y == 115 && x > 1 && x < 6)boardScreen[x][y] = "|";
			else if (y == 129 && x > 1 && x < 6)boardScreen[x][y] = "|";
			else if (y == 31 && x > 51 && x < 56)boardScreen[x][y] = "|";
			else if (y == 45 && x > 51 && x < 56)boardScreen[x][y] = "|";
			else if (y == 59 && x > 51 && x < 56)boardScreen[x][y] = "|";
			else if (y == 73 && x > 51 && x < 56)boardScreen[x][y] = "|";
			else if (y == 87 && x > 51 && x < 56)boardScreen[x][y] = "|";
			else if (y == 101 && x > 51 && x < 56)boardScreen[x][y] = "|";
			else if (y == 115 && x > 51 && x < 56)boardScreen[x][y] = "|";
			else if (y == 129 && x > 51 && x < 56)boardScreen[x][y] = "|";
			else if (x == 6 && y > 3 && y < 17)boardScreen[x][y] = "-";
			else if (x == 11 && y > 3 && y < 17)boardScreen[x][y] = "-";
			else if (x == 16 && y > 3 && y < 17)boardScreen[x][y] = "-";
			else if (x == 21 && y > 3 && y < 17)boardScreen[x][y] = "-";
			else if (x == 26 && y > 3 && y < 17)boardScreen[x][y] = "-";
			else if (x == 31 && y > 3 && y < 17)boardScreen[x][y] = "-";
			else if (x == 36 && y > 3 && y < 17)boardScreen[x][y] = "-";
			else if (x == 41 && y > 3 && y < 17)boardScreen[x][y] = "-";
			else if (x == 46 && y > 3 && y < 17)boardScreen[x][y] = "-";
			else if (x == 51 && y > 3 && y < 17)boardScreen[x][y] = "-";
			else if (x == 6 && y > 143 && y < 157)boardScreen[x][y] = "-";
			else if (x == 11 && y > 143 && y < 157)boardScreen[x][y] = "-";
			else if (x == 16 && y > 143 && y < 157)boardScreen[x][y] = "-";
			else if (x == 21 && y > 143 && y < 157)boardScreen[x][y] = "-";
			else if (x == 26 && y > 143 && y < 157)boardScreen[x][y] = "-";
			else if (x == 31 && y > 143 && y < 157)boardScreen[x][y] = "-";
			else if (x == 36 && y > 143 && y < 157)boardScreen[x][y] = "-";
			else if (x == 41 && y > 143 && y < 157)boardScreen[x][y] = "-";
			else if (x == 46 && y > 143 && y < 157)boardScreen[x][y] = "-";
			else if (x == 51 && y > 143 && y < 157)boardScreen[x][y] = "-";
			else if (x == 51 && y > 159 && y < 163)boardScreen[x][y] = "_";
			else if (x == 59 && y > 144 && y < 162)boardScreen[x][y] = "-";
			else if (x == 60 && y > 143 && y < 165)boardScreen[x][y] = "\\";


			//------Community Chest
			else if (x == 10 && y > 23 && y < 53)boardScreen[x][y] = "C";
			else if (x == 16 && y > 23 && y < 53)boardScreen[x][y] = "C";
			else if (y == 24 && x > 10 && x < 16)boardScreen[x][y] = "C";
			else if (y == 52 && x > 10 && x < 16)boardScreen[x][y] = "C";



			//------Chance
			else if (x == 19 && y > 23 && y < 53)boardScreen[x][y] = "?";
			else if (x == 25 && y > 23 && y < 53)boardScreen[x][y] = "?";
			else if (y == 24 && x > 19 && x < 25)boardScreen[x][y] = "?";
			else if (y == 52 && x > 19 && x < 25)boardScreen[x][y] = "?";



			//------Property Card
			else if (x == 0 && y > 162 && y < 189) boardScreen[x][y] = "_";
			else if (x == 3 && y > 162 && y < 189) boardScreen[x][y] = "_";
			else if (x == 17 && y > 162 && y < 189) boardScreen[x][y] = "_";
			else if (x == 18 && y > 162 && y < 190) boardScreen[x][y] = "\\";
			else if (y == 162 && x > 0 && x < 18)boardScreen[x][y] = "|";
			else if (y == 189 && x > 0 && x < 18)boardScreen[x][y] = "|";
			else if (y == 190 && x > 0 && x < 19)boardScreen[x][y] = "\\";
			else if (y == 191 && x > 1 && x < 19)boardScreen[x][y] = "|";





			//-----Dead Space
			else
				boardScreen[x][y] = " ";





			//-----OTHER
			boardScreen[59][144] = "<";
			boardScreen[59][145] = "<";
			boardScreen[59][162] = "<";
			boardScreen[59][161] = "<";
		}
	}
}

void updateBuildings()
{
	int i = 0;
	for (Space* s : board)
	{
		if (Property* prop = dynamic_cast<Property*>(s))
		{
			int group = prop->getGroup();

			if (group < RailRoad)
			{
				buildings[i] = prop->getBuildings();
				i++;
			}
		}
	}
}

void updatePropertyInfo()
{
	Space* s = board[curPlayer.getLocation()];

	auto stringVector = s->boardOut();

	group = -1;

	if (Property* prop = dynamic_cast<Property*>(s))
	{
		group = prop->getGroup();
	}

	if (group > -1)
	{
		propTitle = stringVector[0];
		price = stringVector[2];
	}

	if (group > -1 && group < RailRoad)
	{
		rent = stringVector[3];
		house1 = stringVector[4];
		house2 = stringVector[5];
		house3 = stringVector[6];
		house4 = stringVector[7];
		w_hotel = stringVector[8];
		hcost = stringVector[9];
	}
	else if (group == RailRoad)
	{
		rent = stringVector[3];
		house1 = stringVector[4];
		house2 = stringVector[5];
		house3 = stringVector[6];
	}

	else if (group == Utility)
	{
		rent = stringVector[3];
		house1 = stringVector[4];
	}

	if (group > -1)
	{
		for (int i = 0; i < propTitle.size(); i++)
		{
			char chr = propTitle.at(i);
			if (propTitle.size() > 12)
				boardScreen[2][164 + i] = chr;
			else
				boardScreen[2][169 + i] = chr;
		}
		for (int i = 0; i < price.size(); i++)
		{
			char chr = price.at(i);
			boardScreen[5][169 + i] = chr;
		}
	}
	//--Prop Card>>>>Not Property---Money
	if (group == RailRoad)
	{
		for (int i = 0; i < rent.size(); i++)
		{
			char chr = rent.at(i);
			boardScreen[6][170 + i] = chr;
		}
		for (int i = 0; i < house1.size(); i++)
		{
			char chr = house1.at(i);
			boardScreen[8][163 + i] = chr;
		}
		for (int i = 0; i < house2.size(); i++)
		{
			char chr = house2.at(i);
			boardScreen[9][163 + i] = chr;
		}
		for (int i = 0; i < house3.size(); i++)
		{
			char chr = house3.at(i);
			boardScreen[10][163 + i] = chr;
		}
	}
	else if (group == Utility)
	{
		for (int i = 0; i < rent.size(); i++)
		{
			char chr = rent.at(i);
			if (rent.size() > 10)
				boardScreen[6][163 + i] = chr;
			else
				boardScreen[6][170 + i] = chr;
		}
		for (int i = 0; i < house1.size(); i++)
		{
			char chr = house1.at(i);
			boardScreen[8][163 + i] = chr;
		}
	}
	//----Prop Card>>>> Property---Money
	else if (group > -1 && group < RailRoad)
	{
		for (int i = 0; i < rent.size(); i++)
		{
			char chr = rent.at(i);
			boardScreen[6][170 + i] = chr;
		}
		for (int i = 0; i < house1.size(); i++)
		{
			char chr = house1.at(i);
			boardScreen[8][166 + i] = chr;
		}
		for (int i = 0; i < house2.size(); i++)
		{
			char chr = house2.at(i);
			boardScreen[9][166 + i] = chr;
		}
		for (int i = 0; i < house3.size(); i++)
		{
			char chr = house3.at(i);
			boardScreen[10][166 + i] = chr;
		}
		for (int i = 0; i < house4.size(); i++)
		{
			char chr = house4.at(i);
			boardScreen[11][166 + i] = chr;
		}
		for (int i = 0; i < w_hotel.size(); i++)
		{
			char chr = w_hotel.at(i);
			boardScreen[13][169 + i] = chr;
		}
		for (int i = 0; i < hcost.size(); i++)
		{
			char chr = hcost.at(i);
			boardScreen[14][165 + i] = chr;
		}
	}
}

void updatePlayerLocations()
{
	int playersSize = players.size();


	ply1LOC = players[0].getLocation();


	ply2LOC = players[1].getLocation();

	if (playersSize > 2)
	{
		ply3LOC = players[2].getLocation();
		if (playersSize > 3)
		{
			ply4LOC = players[3].getLocation();
			if (playersSize > 4)
			{
				ply5LOC = players[4].getLocation();
				if (playersSize > 5)
					ply6LOC = players[5].getLocation();
			}
		}
	}
}

void displayBoard()
{
	system("CLS");
	int lineNumX = 11;
	int spaceNumY = 80;
	createBoard();
	updatePlayerLocations();
	updatePropertyInfo();
	updateBuildings();
	
	//------------------------DECALS----------------------
	//---Side Display
	//--------CORNER SQUARES
	//---GO
	for (int i = 0; i < spaceY + 6; i++)
	{
		string l1 = GO[0];
		string l2 = GO[1];
		string l3 = GO[2];
		string l4 = GO[3];
		string l5 = GO[4];
		string l6 = GO[5];
		string l7 = GO[6];
		char L1 = l1.at(i);
		char L2 = l2.at(i);
		char L3 = l3.at(i);
		char L4 = l4.at(i);
		char L5 = l5.at(i);
		char L6 = l6.at(i);
		char L7 = l7.at(i);
		boardScreen[52][144 + i] = L1;
		boardScreen[53][144 + i] = L2;
		boardScreen[54][144 + i] = L3;
		boardScreen[55][144 + i] = L4;
		boardScreen[56][144 + i] = L5;
		boardScreen[57][144 + i] = L6;
		boardScreen[58][144 + i] = L7;

	}
	//             |||
	//---JAIL \m/ dO.0b \m/ -- Inmate ID:2361 FUCK RECIDIVISM!!
	for (int i = 0; i < spaceY; i++)
	{
		string l1 = bchc[0];
		string l2 = bchc[1];
		string l3 = bchc[2];
		string l4 = bchc[3];
		char L1 = l1.at(i);
		char L2 = l2.at(i);
		char L3 = l3.at(i);
		char L4 = l4.at(i);
		boardScreen[52][4 + i] = L1;
		boardScreen[53][4 + i] = L2;
		boardScreen[54][4 + i] = L3;
		boardScreen[55][4 + i] = L4;
	}
	//--GO TO JAIL
	for (int i = 0; i < spaceY; i++)
	{
		string l1 = gotoJail[0];
		string l2 = gotoJail[1];
		string l3 = gotoJail[2];
		string l4 = gotoJail[3];
		char L1 = l1.at(i);
		char L2 = l2.at(i);
		char L3 = l3.at(i);
		char L4 = l4.at(i);
		boardScreen[2][144 + i] = L1;
		boardScreen[3][144 + i] = L2;
		boardScreen[4][144 + i] = L3;
		boardScreen[5][144 + i] = L4;

	}
	//--FREE PARKING
	for (int i = 0; i < spaceY; i++)
	{
		string l1 = freeParking[0];
		string l2 = freeParking[1];
		string l3 = freeParking[2];
		string l4 = freeParking[3];
		string l5 = freeParking[4];
		char L1 = l1.at(i);
		char L2 = l2.at(i);
		char L3 = l3.at(i);
		char L4 = l4.at(i);
		char L5 = l5.at(i);
		boardScreen[1][4 + i] = L1;
		boardScreen[2][4 + i] = L2;
		boardScreen[3][4 + i] = L3;
		boardScreen[4][4 + i] = L4;
		boardScreen[5][4 + i] = L5;

	}
	//Menu
	for (string line : menuDisplay)
	{
		for (int i = 0; i < line.size(); i++)
		{
			char chr = line.at(i);
			boardScreen[lineNumX][spaceNumY + i] = chr;
		}
		lineNumX++;
	}
	//--daMAN
	for (int x = 0; x < 11; x++)
	{
		for (int i = 0; i < daMan[x].size(); i++)
		{
			char MM = daMan[x].at(i);
			boardScreen[37 + x][74 + i] = MM;
		}
	}

	switch (players[0].bankrupt)
	{
	case true:
		boardScreen[43][107] = '1';
		break;
	default:
		break;
	}

	switch (players[1].bankrupt)
	{
	case true:
		boardScreen[43][108] = '2';
		break;
	default:
		break;
	}

	if (players.size() > 2)
	{
		switch (players[2].bankrupt)
		{
		case true:
			boardScreen[43][109] = '3';
			break;
		default:
			break;
		}
	}

	if (players.size() > 3)
	{
		switch (players[3].bankrupt)
		{
		case true:
			boardScreen[43][110] = '4';
			break;
		default:
			break;
		}
	}

	if (players.size() > 4)
	{
		switch (players[4].bankrupt)
		{
		case true:
			boardScreen[43][111] = '5';
			break;
		default:
			break;
		}
	}

	if (players.size() > 5)
	{
		switch (players[5].bankrupt)
		{
		case true:
			boardScreen[43][112] = '6';
			break;
		default:
			break;
		}
	}

	//-----DICE DISPLAY
	for (int i = 0; i < CURROLL.size(); i++)
	{
		char chr = CURROLL.at(i);
		boardScreen[34][167 + i] = chr;
	}
	for (int x = 0; x < 8; x++)
	{
		for (int i = 0; i < dieART[x].size(); i++)
		{
			char BigOLd = dieART[x].at(i);
			boardScreen[23 + x][166 + i] = BigOLd;
		}
	}
	switch (d.getDice1Result())
	{
	case 1:
		for (int x = 0; x < 4; x++)
		{
			for (int i = 0; i < dieONE[x].size(); i++)
			{
				char d1 = dieONE[x].at(i);
				boardScreen[36 + x][166 + i] = d1;
			}
		}
		break;
	case 2:
		for (int x = 0; x < 4; x++)
		{
			for (int i = 0; i < dieTWO[x].size(); i++)
			{
				char d1 = dieTWO[x].at(i);
				boardScreen[36 + x][166 + i] = d1;
			}
		}
		break;
	case 3:
		for (int x = 0; x < 4; x++)
		{
			for (int i = 0; i < dieTHR[x].size(); i++)
			{
				char d1 = dieTHR[x].at(i);
				boardScreen[36 + x][166 + i] = d1;
			}
		}
		break;
	case 4:
		for (int x = 0; x < 4; x++)
		{
			for (int i = 0; i < dieFOU[x].size(); i++)
			{
				char d1 = dieFOU[x].at(i);
				boardScreen[36 + x][166 + i] = d1;
			}
		}
		break;
	case 5:
		for (int x = 0; x < 4; x++)
		{
			for (int i = 0; i < dieFIV[x].size(); i++)
			{
				char d1 = dieFIV[x].at(i);
				boardScreen[36 + x][166 + i] = d1;
			}
		}
		break;
	case 6:
		for (int x = 0; x < 4; x++)
		{
			for (int i = 0; i < dieSIX[x].size(); i++)
			{
				char d1 = dieSIX[x].at(i);
				boardScreen[36 + x][166 + i] = d1;
			}
		}
		break;
	default:
		break;
	}
	switch (d.getDice2Result())
	{
	case 1:
		for (int x = 0; x < 4; x++)
		{
			for (int i = 0; i < dieONE[x].size(); i++)
			{
				char d2 = dieONE[x].at(i);
				boardScreen[42 + x][175 + i] = d2;
			}
		}
		break;
	case 2:
		for (int x = 0; x < 4; x++)
		{
			for (int i = 0; i < dieTWO[x].size(); i++)
			{
				char d2 = dieTWO[x].at(i);
				boardScreen[42 + x][175 + i] = d2;
			}
		}
		break;
	case 3:
		for (int x = 0; x < 4; x++)
		{
			for (int i = 0; i < dieTHR[x].size(); i++)
			{
				char d2 = dieTHR[x].at(i);
				boardScreen[42 + x][175 + i] = d2;
			}
		}
		break;
	case 4:
		for (int x = 0; x < 4; x++)
		{
			for (int i = 0; i < dieFOU[x].size(); i++)
			{
				char d2 = dieFOU[x].at(i);
				boardScreen[42 + x][175 + i] = d2;
			}
		}
		break;
	case 5:
		for (int x = 0; x < 4; x++)
		{
			for (int i = 0; i < dieFIV[x].size(); i++)
			{
				char d2 = dieFIV[x].at(i);
				boardScreen[42 + x][175 + i] = d2;
			}
		}
		break;
	case 6:
		for (int x = 0; x < 4; x++)
		{
			for (int i = 0; i < dieSIX[x].size(); i++)
			{
				char d2 = dieSIX[x].at(i);
				boardScreen[42 + x][175 + i] = d2;
			}
		}
		break;
	default:
		break;
	}
	//--MONOPOLY CENTER
	for (int i = 0; i < 6; i++)
	{
		boardScreen[39 + i][33] = 'M';
		boardScreen[39 + i][39] = 'M';
		boardScreen[40][35] = 'M';
		boardScreen[41][36] = 'M';
		boardScreen[40][37] = 'M';
		boardScreen[33][44 + (i % 3)] = 'O';
		boardScreen[34][43] = 'O';
		boardScreen[34][47] = 'O';
		boardScreen[35 + (i % 2)][42] = 'O';
		boardScreen[35 + (i % 2)][48] = 'O';
		boardScreen[37][43] = 'O';
		boardScreen[37][47] = 'O';
		boardScreen[38][44 + (i % 3)] = 'O';
		boardScreen[28 + i][51] = 'N';
		boardScreen[28 + i][56] = 'N';
		boardScreen[28 + i][51 + i] = 'N';
		boardScreen[23][61 + (i % 3)] = 'O';
		boardScreen[24][60] = 'O';
		boardScreen[24][64] = 'O';
		boardScreen[25 + (i % 2)][59] = 'O';
		boardScreen[25 + (i % 2)][65] = 'O';
		boardScreen[27][60] = 'O';
		boardScreen[27][64] = 'O';
		boardScreen[28][61 + (i % 3)] = 'O';
		boardScreen[41 + i][45] = 'P';
		boardScreen[42 + (i % 2)][50] = 'P';
		boardScreen[41][45 + i] = 'P';
		boardScreen[44][45 + i] = 'P';
		boardScreen[35][56 + (i % 3)] = 'O';
		boardScreen[36][59] = 'O';
		boardScreen[36][55] = 'O';
		boardScreen[37 + (i % 2)][54] = 'O';
		boardScreen[37 + (i % 2)][60] = 'O';
		boardScreen[39][55] = 'O';
		boardScreen[39][59] = 'O';
		boardScreen[40][56 + (i % 3)] = 'O';
		boardScreen[30 + i][64] = 'L';
		boardScreen[35][64 + i] = 'L';
		boardScreen[25][73] = 'Y';
		boardScreen[25][69] = 'Y';
		boardScreen[26][70] = 'Y';
		boardScreen[26][72] = 'Y';
		boardScreen[27 + (i % 4)][71] = 'Y';
	}
	//------Grouping Guides
	boardScreen[0][87] = "I";
	boardScreen[0][73] = "I";
	boardScreen[0][143] = "I";
	boardScreen[59][73] = "I";
	boardScreen[59][101] = "I";
	boardScreen[59][17] = "I";
	boardScreen[6][0] = "-";
	boardScreen[6][1] = "-";
	boardScreen[6][2] = "-";
	boardScreen[26][0] = "-";
	boardScreen[26][1] = "-";
	boardScreen[26][2] = "-";
	boardScreen[31][0] = "-";
	boardScreen[31][1] = "-";
	boardScreen[31][2] = "-";
	boardScreen[51][0] = "-";
	boardScreen[51][1] = "-";
	boardScreen[51][2] = "-";
	boardScreen[6][160] = "-";
	boardScreen[6][161] = "-";
	boardScreen[26][160] = "-";
	boardScreen[26][161] = "-";
	boardScreen[36][160] = "-";
	boardScreen[36][161] = "-";
	//BROWN
	for (int i = 0; i < colors[0].size(); i++)
	{
		char x = colors[0].at(i);
		boardScreen[59][121 + i] = x;
	}
	//LBLUE
	for (int i = 0; i < colors[1].size(); i++)
	{
		char x = colors[1].at(i);
		boardScreen[59][44 + i] = x;
	}
	//PINK
	for (int i = 0; i < colors[2].size(); i++)
	{
		char x = colors[2].at(i);
		boardScreen[37 + i][1] = x;
	}
	//ORANGE
	for (int i = 0; i < colors[3].size(); i++)
	{
		char x = colors[3].at(i);
		boardScreen[11 + i][1] = x;
	}
	//RED
	for (int i = 0; i < colors[4].size(); i++)
	{
		char x = colors[4].at(i);
		boardScreen[0][44 + i] = x;
	}
	//YELLOW
	for (int i = 0; i < colors[5].size(); i++)
	{
		char x = colors[5].at(i);
		boardScreen[0][111 + i] = x;
	}
	//GREEN
	for (int i = 0; i < colors[6].size(); i++)
	{
		char x = colors[6].at(i);
		boardScreen[11 + i][160] = x;
	}
	//DBLUE
	for (int i = 0; i < colors[7].size(); i++)
	{
		char x = colors[7].at(i);
		boardScreen[40 + i][160] = x;
	}
	//-------------PROPERTIES------------------
	//---Mediterranean Ave.
	for (int i = 0; i < pOne.size(); i++)
	{
		char chr = pOne.at(i);
		boardScreen[52][130 + i] = chr;
	}
	//---Baltic Ave.
	for (int i = 0; i < pTwo.size(); i++)
	{
		char chr = pTwo.at(i);
		boardScreen[52][105 + i] = chr;
	}
	//---Oriental Ave.
	for (int i = 0; i < pThree.size(); i++)
	{
		char chr = pThree.at(i);
		boardScreen[52][63 + i] = chr;
	}
	//---Vermont Ave.
	for (int i = 0; i < pFour.size(); i++)
	{
		char chr = pFour.at(i);
		boardScreen[52][35 + i] = chr;
	}
	//---Connecticut Ave.
	for (int i = 0; i < pFive.size(); i++)
	{
		char chr = pFive.at(i);
		boardScreen[52][19 + i] = chr;
	}
	//---St. Charles Place
	for (int i = 0; i < pSix.size(); i++)
	{
		char chr = pSix.at(i);
		boardScreen[47][5 + i] = chr;
	}
	//---States Ave.
	for (int i = 0; i < pSeven.size(); i++)
	{
		char chr = pSeven.at(i);
		boardScreen[37][7 + i] = chr;
	}
	//---Virginia Ave.
	for (int i = 0; i < pEight.size(); i++)
	{
		char chr = pEight.at(i);
		boardScreen[32][6 + i] = chr;
	}
	//---St. James Place
	for (int i = 0; i < pNine.size(); i++)
	{
		char chr = pNine.at(i);
		boardScreen[22][6 + i] = chr;
	}
	//---Tennessee Ave.
	for (int i = 0; i < pTen.size(); i++)
	{
		char chr = pTen.at(i);
		boardScreen[12][6 + i] = chr;
	}
	//---New York Ave.
	for (int i = 0; i < pEleven.size(); i++)
	{
		char chr = pEleven.at(i);
		boardScreen[7][6 + i] = chr;
	}
	//---Kentucky Ave.
	for (int i = 0; i < pTwelve.size(); i++)
	{
		char chr = pTwelve.at(i);
		boardScreen[2][21 + i] = chr;
	}
	//---Indiana Ave.
	for (int i = 0; i < pThirteen.size(); i++)
	{
		char chr = pThirteen.at(i);
		boardScreen[2][49 + i] = chr;
	}
	//---Illinois Ave.
	for (int i = 0; i < pFourteen.size(); i++)
	{
		char chr = pFourteen.at(i);
		boardScreen[2][63 + i] = chr;
	}
	//---Atlantic Ave.
	for (int i = 0; i < pFifteen.size(); i++)
	{
		char chr = pFifteen.at(i);
		boardScreen[2][91 + i] = chr;
	}
	//---Ventor Ave.
	for (int i = 0; i < pSixteen.size(); i++)
	{
		char chr = pSixteen.at(i);
		boardScreen[2][105 + i] = chr;
	}
	//---Marvin 
	for (int i = 0; i < pSeventeen.size(); i++)
	{
		char chr = pSeventeen.at(i);
		boardScreen[2][133 + i] = chr;
	}
	//---Pacific Ave.
	for (int i = 0; i < pEighteen.size(); i++)
	{
		char chr = pEighteen.at(i);
		boardScreen[7][147 + i] = chr;
	}
	//---North Carolina Ave.
	for (int i = 0; i < pNineteen.size(); i++)
	{
		char chr = pNineteen.at(i);
		boardScreen[12][145 + i] = chr;
	}
	//---Pennsylvania Ave.
	for (int i = 0; i < pTwenty.size(); i++)
	{
		char chr = pTwenty.at(i);
		boardScreen[22][145 + i] = chr;
	}
	//---Park Place
	for (int i = 0; i < pTwentyOne.size(); i++)
	{
		char chr = pTwentyOne.at(i);
		boardScreen[37][149 + i] = chr;
	}
	//---Board Walk
	for (int i = 0; i < pTwentyTwo.size(); i++)
	{
		char chr = pTwentyTwo.at(i);
		boardScreen[47][146 + i] = chr;
	}
	//---Community Chest
	for (int i = 0; i < comChest[4].size(); i++)
	{
		string l1 = comChest[4];
		string l2 = comChest[5];
		char L1 = l1.at(i);
		char L2 = l2.at(i);
		boardScreen[12][42 + i] = L1;
		boardScreen[13][42 + i] = L2;
	}
	for (int i = 0; i < spaceY; i++)
	{
		string l1 = comChest[0];
		string l2 = comChest[1];
		string l3 = comChest[2];
		string l4 = comChest[3];
		char L1 = l1.at(i);
		char L2 = l2.at(i);
		char L3 = l3.at(i);
		char L4 = l4.at(i);
		boardScreen[17][4 + i] = L1;
		boardScreen[18][4 + i] = L2;
		boardScreen[19][4 + i] = L3;
		boardScreen[20][4 + i] = L4;
		boardScreen[17][144 + i] = L1;
		boardScreen[18][144 + i] = L2;
		boardScreen[19][144 + i] = L3;
		boardScreen[20][144 + i] = L4;
		boardScreen[52][116 + i] = L1;
		boardScreen[53][116 + i] = L2;
		boardScreen[54][116 + i] = L3;
		boardScreen[55][116 + i] = L4;
		boardScreen[12][27 + i] = L1;
		boardScreen[13][27 + i] = L2;
		boardScreen[14][27 + i] = L3;
		boardScreen[15][27 + i] = L4;
	}
	//---Chance
	for (int i = 0; i < chance[4].size(); i++)
	{
		string l1 = chance[4];
		char L1 = l1.at(i);
		boardScreen[22][43 + i] = L1;
	}
	for (int i = 0; i < spaceY; i++)
	{
		string l1 = chance[0];
		string l2 = chance[1];
		string l3 = chance[2];
		string l4 = chance[3];
		char L1 = l1.at(i);
		char L2 = l2.at(i);
		char L3 = l3.at(i);
		char L4 = l4.at(i);
		boardScreen[52][46 + i] = L1;
		boardScreen[53][46 + i] = L2;
		boardScreen[54][46 + i] = L3;
		boardScreen[55][46 + i] = L4;
		boardScreen[2][32 + i] = L1;
		boardScreen[3][32 + i] = L2;
		boardScreen[4][32 + i] = L3;
		boardScreen[5][32 + i] = L4;
		boardScreen[32][144 + i] = L1;
		boardScreen[33][144 + i] = L2;
		boardScreen[34][144 + i] = L3;
		boardScreen[35][144 + i] = L4;


		boardScreen[21][27 + i] = L1;
		boardScreen[22][27 + i] = L2;
		boardScreen[23][27 + i] = L3;
		boardScreen[24][27 + i] = L4;
	}
	//--Electric Co.
	for (int i = 0; i < spaceY; i++)
	{
		string l1 = electricCO[0];
		string l2 = electricCO[1];
		string l3 = electricCO[2];
		string l4 = electricCO[3];
		char L1 = l1.at(i);
		char L2 = l2.at(i);
		char L3 = l3.at(i);
		char L4 = l4.at(i);
		boardScreen[42][4 + i] = L1;
		boardScreen[43][4 + i] = L2;
		boardScreen[44][4 + i] = L3;
		boardScreen[45][4 + i] = L4;
	}
	//--Water Works
	for (int i = 0; i < spaceY; i++)
	{
		string l1 = h2o[0];
		string l2 = h2o[1];
		string l3 = h2o[2];
		string l4 = h2o[3];
		char L1 = l1.at(i);
		char L2 = l2.at(i);
		char L3 = l3.at(i);
		char L4 = l4.at(i);
		boardScreen[2][116 + i] = L1;
		boardScreen[3][116 + i] = L2;
		boardScreen[4][116 + i] = L3;
		boardScreen[5][116 + i] = L4;
	}
	//---Rail Roads
	for (int i = 0; i < spaceY; i++)
	{
		string l1 = railRoad[0];
		string l2 = railRoad[1];
		string l3 = railRoad[2];
		string l4 = railRoad[3];
		string l5 = railRoad[4];
		string l6 = railRoad[5];
		string l7 = railRoad[6];
		char L1 = l1.at(i);
		char L2 = l2.at(i);
		char L3 = l3.at(i);
		char L4 = l4.at(i);
		char L5 = l5.at(i);
		char L6 = l6.at(i);
		char L7 = l7.at(i);
		boardScreen[52][74 + i] = L1;
		boardScreen[53][74 + i] = L5;
		boardScreen[54][74 + i] = L6;
		boardScreen[55][74 + i] = L7;
		boardScreen[2][74 + i] = L2;
		boardScreen[3][74 + i] = L5;
		boardScreen[4][74 + i] = L6;
		boardScreen[5][74 + i] = L7;
		boardScreen[27][144 + i] = L3;
		boardScreen[28][144 + i] = L5;
		boardScreen[29][144 + i] = L6;
		boardScreen[30][144 + i] = L7;
		boardScreen[27][4 + i] = L4;
		boardScreen[28][4 + i] = L5;
		boardScreen[29][4 + i] = L6;
		boardScreen[30][4 + i] = L7;
	}
	//Income/Luxury Tax
	for (int i = 0; i < spaceY; i++)
	{
		string i1 = incTax[0];
		string i2 = incTax[1];
		string i3 = incTax[2];
		string i4 = incTax[3];
		char I1 = i1.at(i);
		char I2 = i2.at(i);
		char I3 = i3.at(i);
		char I4 = i4.at(i);
		string l1 = luxTax[0];
		string l2 = luxTax[1];
		string l3 = luxTax[2];
		string l4 = luxTax[3];
		char L1 = l1.at(i);
		char L2 = l2.at(i);
		char L3 = l3.at(i);
		char L4 = l4.at(i);
		boardScreen[42][144 + i] = L1;
		boardScreen[43][144 + i] = L2;
		boardScreen[44][144 + i] = L3;
		boardScreen[45][144 + i] = L4;
		boardScreen[52][88 + i] = I1;
		boardScreen[53][88 + i] = I2;
		boardScreen[54][88 + i] = I3;
		boardScreen[55][88 + i] = I4;
	}
	//---Building Locations
	for (int i = 0; i < 23; i++)
	{
		switch (i)
		{
		case 0:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[53][130 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[54][130 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[53][130 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[54][130 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[53][130 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[54][130 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[53][130 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[54][130 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[53][130 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[54][130 + i] = chr;
				}
			}
			break;
		case 1:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[53][102 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[54][102 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[53][102 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[54][102 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[53][102 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[54][102 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[53][102 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[54][102 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[53][102 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[54][102 + i] = chr;
				}
			}
			break;
		case 2:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[53][60 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[54][60 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[53][60 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[54][60 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[53][60 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[54][60 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[53][60 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[54][60 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[53][60 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[54][60 + i] = chr;
				}
			}
			break;
		case 3:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[53][32 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[54][32 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[53][32 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[54][32 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[53][32 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[54][32 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[53][32 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[54][32 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[53][32 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[54][32 + i] = chr;
				}
			}
			break;
		case 4:
		{
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[53][18 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[54][18 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[53][18 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[54][18 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[53][18 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[54][18 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[53][18 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[54][18 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[53][18 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[54][18 + i] = chr;
				}
			}
			break;
		}
		case 5:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[48][4 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[49][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[48][4 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[49][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[48][4 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[49][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[48][4 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[49][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[48][4 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[49][4 + i] = chr;
				}
			}
			break;
		case 6:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[38][4 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[39][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[38][4 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[39][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[38][4 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[39][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[38][4 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[39][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[38][4 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[39][4 + i] = chr;
				}
			}
			break;
		case 7:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[33][4 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[34][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[33][4 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[34][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[33][4 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[34][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[33][4 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[34][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[33][4 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[34][4 + i] = chr;
				}
			}
			break;
		case 8:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[23][4 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[24][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[23][4 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[24][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[23][4 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[24][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[23][4 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[24][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[23][4 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[24][4 + i] = chr;
				}
			}
			break;
		case 9:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[13][4 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[14][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[13][4 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[14][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[13][4 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[14][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[13][4 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[14][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[13][4 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[14][4 + i] = chr;
				}
			}
			break;
		case 10:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[8][4 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[9][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[8][4 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[9][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[8][4 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[9][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[8][4 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[9][4 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[8][4 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[9][4 + i] = chr;
				}
			}
			break;
		case 11:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[3][18 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[4][18 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[3][18 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[4][18 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[3][18 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[4][18 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[3][18 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[4][18 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[3][18 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[4][18 + i] = chr;
				}
			}
			break;
		case 12:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[3][46 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[4][46 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[3][46 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[4][46 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[3][46 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[4][46 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[3][46 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[4][46 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[3][46 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[4][46 + i] = chr;
				}
			}
			break;
		case 13:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[3][60 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[4][60 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[3][60 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[4][60 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[3][60 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[4][60 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[3][60 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[4][60 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[3][60 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[4][60 + i] = chr;
				}
			}
			break;
		case 14:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[3][88 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[4][88 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[3][88 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[4][88 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[3][88 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[4][88 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[3][88 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[4][88 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[3][88 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[4][88 + i] = chr;
				}
			}
			break;
		case 15:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[3][102 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[4][102 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[3][102 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[4][102 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[3][102 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[4][102 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[3][102 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[4][102 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[3][102 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[4][102 + i] = chr;
				}
			}
			break;
		case 16:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[3][130 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[4][130 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[3][130 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[4][130 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[3][130 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[4][130 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[3][130 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[4][130 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[3][130 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[4][130 + i] = chr;
				}
			}
			break;
		case 17:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[8][144 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[9][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[8][144 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[9][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[8][144 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[9][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[8][144 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[9][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[8][144 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[9][144 + i] = chr;
				}
			}
			break;
		case 18:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[13][144 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[14][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[13][144 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[14][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[13][144 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[14][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[13][144 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[14][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[13][144 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[14][144 + i] = chr;
				}
			}
			break;
		case 19:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[23][144 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[24][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[23][144 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[24][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[23][144 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[24][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[23][144 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[24][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[23][144 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[24][144 + i] = chr;
				}
			}
			break;
		case 20:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[38][144 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[39][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[38][144 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[39][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[38][144 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[39][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[38][144 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[39][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[38][144 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[39][144 + i] = chr;
				}
			}
			break;
		case 21:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[48][144 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[49][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[48][144 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[49][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[48][144 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[49][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[48][144 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[49][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[48][144 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[49][144 + i] = chr;
				}
			}
			break;
		case 22:
			if ((int)buildings[i] == 1)
			{
				for (int i = 0; i < houseOne[0].size(); i++)
				{
					char chr = houseOne[0].at(i);
					boardScreen[58][144 + i] = chr;
				}
				for (int i = 0; i < houseOne[1].size(); i++)
				{
					char chr = houseOne[1].at(i);
					boardScreen[59][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 2)
			{
				for (int i = 0; i < houseTwo[0].size(); i++)
				{
					char chr = houseTwo[0].at(i);
					boardScreen[58][144 + i] = chr;
				}
				for (int i = 0; i < houseTwo[1].size(); i++)
				{
					char chr = houseTwo[1].at(i);
					boardScreen[59][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 3)
			{
				for (int i = 0; i < houseThree[0].size(); i++)
				{
					char chr = houseThree[0].at(i);
					boardScreen[58][144 + i] = chr;
				}
				for (int i = 0; i < houseThree[1].size(); i++)
				{
					char chr = houseThree[1].at(i);
					boardScreen[59][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 4)
			{
				for (int i = 0; i < houseFour[0].size(); i++)
				{
					char chr = houseFour[0].at(i);
					boardScreen[58][144 + i] = chr;
				}
				for (int i = 0; i < houseFour[1].size(); i++)
				{
					char chr = houseFour[1].at(i);
					boardScreen[59][144 + i] = chr;
				}
			}
			if ((int)buildings[i] == 5)
			{
				for (int i = 0; i < hotel[0].size(); i++)
				{
					char chr = hotel[0].at(i);
					boardScreen[58][144 + i] = chr;
				}
				for (int i = 0; i < hotel[1].size(); i++)
				{
					char chr = hotel[1].at(i);
					boardScreen[59][144 + i] = chr;
				}
			}
			break;
		default:
			break;
		}
	}
	//-----Bankrupt
	bool player3Bankrupt = true;
	if (players.size() > 2)if (!players[2].bankrupt)player3Bankrupt = false;
	bool player4Bankrupt = true;
	if (players.size() > 3)if (!players[3].bankrupt)player4Bankrupt = false;
	bool player5Bankrupt = true;
	if (players.size() > 4)if (!players[4].bankrupt)player5Bankrupt = false;
	bool player6Bankrupt = true;
	if (players.size() > 5)if (!players[5].bankrupt)player6Bankrupt = false;
	//-----------PLAYER LOCATIONS-----------	
	//----P1
	if (ply1LOC < 40 && !players[0].bankrupt)
	{
		switch (ply1LOC)
		{
		case 0:
			boardScreen[59][151] = '1';
			break;
		case 1:
			boardScreen[55][130] = '1';
			break;
		case 2:
			boardScreen[55][116] = '1';
			break;
		case 3:
			boardScreen[55][102] = '1';
			break;
		case 4:
			boardScreen[55][92] = '1';
			break;
		case 5:
			boardScreen[54][76] = '1';
			break;
		case 6:
			boardScreen[55][60] = '1';
			break;
		case 7:
			boardScreen[55][46] = '1';
			break;
		case 8:
			boardScreen[55][32] = '1';
			break;
		case 9:
			boardScreen[55][18] = '1';
			break;
		case 10:
			if (!players[0].jailed)
				boardScreen[54][6] = '1';
			else
				boardScreen[52][6] = '1';
			break;
		case 11:
			boardScreen[50][4] = '1';
			break;
		case 12:
			boardScreen[45][8] = '1';
			break;
		case 13:
			boardScreen[40][4] = '1';
			break;
		case 14:
			boardScreen[35][4] = '1';
			break;
		case 15:
			boardScreen[29][6] = '1';
			break;
		case 16:
			boardScreen[25][4] = '1';
			break;
		case 17:
			boardScreen[20][4] = '1';
			break;
		case 18:
			boardScreen[15][4] = '1';
			break;
		case 19:
			boardScreen[10][4] = '1';
			break;
		case 20:
			boardScreen[4][12] = '1';
			break;
		case 21:
			boardScreen[5][18] = '1';
			break;
		case 22:
			boardScreen[5][32] = '1';
			break;
		case 23:
			boardScreen[5][46] = '1';
			break;
		case 24:
			boardScreen[5][60] = '1';
			break;
		case 25:
			boardScreen[4][76] = '1';
			break;
		case 26:
			boardScreen[5][88] = '1';
			break;
		case 27:
			boardScreen[5][102] = '1';
			break;
		case 28:
			boardScreen[5][125] = '1';
			break;
		case 29:
			boardScreen[5][130] = '1';
			break;
		case 30:
			boardScreen[4][148] = '1';
			break;
		case 31:
			boardScreen[10][144] = '1';
			break;
		case 32:
			boardScreen[15][144] = '1';
			break;
		case 33:
			boardScreen[20][144] = '1';
			break;
		case 34:
			boardScreen[25][144] = '1';
			break;
		case 35:
			boardScreen[29][146] = '1';
			break;
		case 36:
			boardScreen[35][144] = '1';
			break;
		case 37:
			boardScreen[40][144] = '1';
			break;
		case 38:
			boardScreen[45][148] = '1';
			break;
		case 39:
			boardScreen[50][144] = '1';
		default:
			break;
		}
	}
	//----P2
	if (ply2LOC < 40 && !players[1].bankrupt)
	{
		switch (ply2LOC)
		{
		case 0:
			boardScreen[59][152] = '2';
			break;
		case 1:
			boardScreen[55][131] = '2';
			break;
		case 2:
			boardScreen[55][117] = '2';
			break;
		case 3:
			boardScreen[55][103] = '2';
			break;
		case 4:
			boardScreen[55][93] = '2';
			break;
		case 5:
			boardScreen[54][77] = '2';
			break;
		case 6:
			boardScreen[55][61] = '2';
			break;
		case 7:
			boardScreen[55][47] = '2';
			break;
		case 8:
			boardScreen[55][33] = '2';
			break;
		case 9:
			boardScreen[55][19] = '2';
			break;
		case 10:
			if (!players[1].jailed)
				boardScreen[54][8] = '2';
			else
				boardScreen[52][8] = '2';
			break;
		case 11:
			boardScreen[50][5] = '2';
			break;
		case 12:
			boardScreen[45][9] = '2';
			break;
		case 13:
			boardScreen[40][5] = '2';
			break;
		case 14:
			boardScreen[35][5] = '2';
			break;
		case 15:
			boardScreen[29][7] = '2';
			break;
		case 16:
			boardScreen[25][5] = '2';
			break;
		case 17:
			boardScreen[20][5] = '2';
			break;
		case 18:
			boardScreen[15][5] = '2';
			break;
		case 19:
			boardScreen[10][5] = '2';
			break;
		case 20:
			boardScreen[4][13] = '2';
			break;
		case 21:
			boardScreen[5][19] = '2';
			break;
		case 22:
			boardScreen[5][33] = '2';
			break;
		case 23:
			boardScreen[5][47] = '2';
			break;
		case 24:
			boardScreen[5][61] = '2';
			break;
		case 25:
			boardScreen[4][77] = '2';
			break;
		case 26:
			boardScreen[5][89] = '2';
			break;
		case 27:
			boardScreen[5][103] = '2';
			break;
		case 28:
			boardScreen[5][126] = '2';
			break;
		case 29:
			boardScreen[5][131] = '2';
			break;
		case 30:
			boardScreen[4][148] = '2';
			break;
		case 31:
			boardScreen[10][145] = '2';
			break;
		case 32:
			boardScreen[15][145] = '2';
			break;
		case 33:
			boardScreen[20][145] = '2';
			break;
		case 34:
			boardScreen[25][145] = '2';
			break;
		case 35:
			boardScreen[29][147] = '2';
			break;
		case 36:
			boardScreen[35][145] = '2';
			break;
		case 37:
			boardScreen[40][145] = '2';
			break;
		case 38:
			boardScreen[45][149] = '2';
			break;
		case 39:
			boardScreen[50][145] = '2';
			break;
		default:
			break;
		}
	}
	//----P3
	if (ply3LOC < 40 && ply3LOC != -1 && !player3Bankrupt)
	{
		switch (ply3LOC)
		{
		case 0:
			boardScreen[59][153] = '3';
			break;
		case 1:
			boardScreen[55][132] = '3';
			break;
		case 2:
			boardScreen[55][118] = '3';
			break;
		case 3:
			boardScreen[55][104] = '3';
			break;
		case 4:
			boardScreen[55][94] = '3';
			break;
		case 5:
			boardScreen[54][78] = '3';
			break;
		case 6:
			boardScreen[55][62] = '3';
			break;
		case 7:
			boardScreen[55][48] = '3';
			break;
		case 8:
			boardScreen[55][34] = '3';
			break;
		case 9:
			boardScreen[55][20] = '3';
			break;
		case 10:
			if (!players[2].jailed)
				boardScreen[54][10] = '3';
			else
				boardScreen[52][10] = '3';
			break;
		case 11:
			boardScreen[50][6] = '3';
			break;
		case 12:
			boardScreen[45][10] = '3';
			break;
		case 13:
			boardScreen[40][6] = '3';
			break;
		case 14:
			boardScreen[35][6] = '3';
			break;
		case 15:
			boardScreen[29][8] = '3';
			break;
		case 16:
			boardScreen[25][6] = '3';
			break;
		case 17:
			boardScreen[20][6] = '3';
			break;
		case 18:
			boardScreen[15][6] = '3';
			break;
		case 19:
			boardScreen[10][6] = '3';
			break;
		case 20:
			boardScreen[4][14] = '3';
			break;
		case 21:
			boardScreen[5][20] = '3';
			break;
		case 22:
			boardScreen[5][34] = '3';
			break;
		case 23:
			boardScreen[5][48] = '3';
			break;
		case 24:
			boardScreen[5][62] = '3';
			break;
		case 25:
			boardScreen[4][78] = '3';
			break;
		case 26:
			boardScreen[5][90] = '3';
			break;
		case 27:
			boardScreen[5][104] = '3';
			break;
		case 28:
			boardScreen[5][127] = '3';
			break;
		case 29:
			boardScreen[5][132] = '3';
			break;
		case 30:
			boardScreen[4][148] = '3';
			break;
		case 31:
			boardScreen[10][146] = '3';
			break;
		case 32:
			boardScreen[15][146] = '3';
			break;
		case 33:
			boardScreen[20][146] = '3';
			break;
		case 34:
			boardScreen[25][146] = '3';
			break;
		case 35:
			boardScreen[29][148] = '3';
			break;
		case 36:
			boardScreen[35][146] = '3';
			break;
		case 37:
			boardScreen[40][146] = '3';
			break;
		case 38:
			boardScreen[45][150] = '3';
			break;
		case 39:
			boardScreen[50][146] = '3';
			break;
		default:
			break;
		}
	}
	//----P4
	if (ply4LOC < 40 && ply4LOC != -1 && !player4Bankrupt)
	{
		switch (ply4LOC)
		{
		case 0:
			boardScreen[59][154] = '4';
			break;
		case 1:
			boardScreen[55][133] = '4';
			break;
		case 2:
			boardScreen[55][119] = '4';
			break;
		case 3:
			boardScreen[55][105] = '4';
			break;
		case 4:
			boardScreen[55][95] = '4';
			break;
		case 5:
			boardScreen[54][79] = '4';
			break;
		case 6:
			boardScreen[55][63] = '4';
			break;
		case 7:
			boardScreen[55][49] = '4';
			break;
		case 8:
			boardScreen[55][35] = '4';
			break;
		case 9:
			boardScreen[55][21] = '4';
			break;
		case 10:
			if (!players[2].jailed)
				boardScreen[54][12] = '4';
			else
				boardScreen[52][12] = '4';
			break;
		case 11:
			boardScreen[50][7] = '4';
			break;
		case 12:
			boardScreen[45][11] = '4';
			break;
		case 13:
			boardScreen[40][7] = '4';
			break;
		case 14:
			boardScreen[35][7] = '4';
			break;
		case 15:
			boardScreen[29][9] = '4';
			break;
		case 16:
			boardScreen[25][7] = '4';
			break;
		case 17:
			boardScreen[20][7] = '4';
			break;
		case 18:
			boardScreen[15][7] = '4';
			break;
		case 19:
			boardScreen[10][7] = '4';
			break;
		case 20:
			boardScreen[5][12] = '4';
			break;
		case 21:
			boardScreen[5][21] = '4';
			break;
		case 22:
			boardScreen[5][35] = '4';
			break;
		case 23:
			boardScreen[5][49] = '4';
			break;
		case 24:
			boardScreen[5][63] = '4';
			break;
		case 25:
			boardScreen[4][79] = '4';
			break;
		case 26:
			boardScreen[5][91] = '4';
			break;
		case 27:
			boardScreen[5][105] = '4';
			break;
		case 28:
			boardScreen[4][125] = '4';
			break;
		case 29:
			boardScreen[5][133] = '4';
			break;
		case 30:
			boardScreen[4][148] = '4';
			break;
		case 31:
			boardScreen[10][147] = '4';
			break;
		case 32:
			boardScreen[15][147] = '4';
			break;
		case 33:
			boardScreen[20][147] = '4';
			break;
		case 34:
			boardScreen[25][147] = '4';
			break;
		case 35:
			boardScreen[29][149] = '4';
			break;
		case 36:
			boardScreen[35][147] = '4';
			break;
		case 37:
			boardScreen[40][147] = '4';
			break;
		case 38:
			boardScreen[45][151] = '4';
			break;
		case 39:
			boardScreen[50][147] = '4';
			break;
		default:
			break;
		}
	}
	//----P5
	if (ply5LOC < 40 && ply5LOC != -1 && !player5Bankrupt)
	{
		switch (ply5LOC)
		{
		case 0:
			boardScreen[59][155] = '5';
			break;
		case 1:
			boardScreen[55][134] = '5';
			break;
		case 2:
			boardScreen[55][120] = '5';
			break;
		case 3:
			boardScreen[55][106] = '5';
			break;
		case 4:
			boardScreen[55][96] = '5';
			break;
		case 5:
			boardScreen[54][80] = '5';
			break;
		case 6:
			boardScreen[55][64] = '5';
			break;
		case 7:
			boardScreen[55][50] = '5';
			break;
		case 8:
			boardScreen[55][36] = '5';
			break;
		case 9:
			boardScreen[55][22] = '5';
			break;
		case 10:
			if (!players[2].jailed)
				boardScreen[54][14] = '5';
			else
				boardScreen[52][14] = '5';
			break;
		case 11:
			boardScreen[50][8] = '5';
			break;
		case 12:
			boardScreen[45][12] = '5';
			break;
		case 13:
			boardScreen[40][8] = '5';
			break;
		case 14:
			boardScreen[35][8] = '5';
			break;
		case 15:
			boardScreen[29][10] = '5';
			break;
		case 16:
			boardScreen[25][8] = '5';
			break;
		case 17:
			boardScreen[20][8] = '5';
			break;
		case 18:
			boardScreen[15][8] = '5';
			break;
		case 19:
			boardScreen[10][8] = '5';
			break;
		case 20:
			boardScreen[5][13] = '5';
			break;
		case 21:
			boardScreen[5][22] = '5';
			break;
		case 22:
			boardScreen[5][36] = '5';
			break;
		case 23:
			boardScreen[5][50] = '5';
			break;
		case 24:
			boardScreen[5][64] = '5';
			break;
		case 25:
			boardScreen[4][80] = '5';
			break;
		case 26:
			boardScreen[5][92] = '5';
			break;
		case 27:
			boardScreen[5][106] = '5';
			break;
		case 28:
			boardScreen[4][126] = '5';
			break;
		case 29:
			boardScreen[5][134] = '5';
			break;
		case 30:
			boardScreen[4][148] = '5';
			break;
		case 31:
			boardScreen[10][148] = '5';
			break;
		case 32:
			boardScreen[15][148] = '5';
			break;
		case 33:
			boardScreen[20][148] = '5';
			break;
		case 34:
			boardScreen[25][148] = '5';
			break;
		case 35:
			boardScreen[29][150] = '5';
			break;
		case 36:
			boardScreen[35][148] = '5';
			break;
		case 37:
			boardScreen[40][148] = '5';
			break;
		case 38:
			boardScreen[45][152] = '5';
			break;
		case 39:
			boardScreen[50][148] = '5';
			break;
		default:
			break;
		}
	}
	//----P6
	if (ply6LOC < 40 && ply6LOC != -1 && !player6Bankrupt)
	{
		switch (ply6LOC)
		{
		case 0:
			boardScreen[59][156] = '6';
			break;
		case 1:
			boardScreen[55][135] = '6';
			break;
		case 2:
			boardScreen[55][121] = '6';
			break;
		case 3:
			boardScreen[55][107] = '6';
			break;
		case 4:
			boardScreen[55][97] = '6';
			break;
		case 5:
			boardScreen[54][81] = '6';
			break;
		case 6:
			boardScreen[55][64] = '6';
			break;
		case 7:
			boardScreen[55][51] = '6';
			break;
		case 8:
			boardScreen[55][37] = '6';
			break;
		case 9:
			boardScreen[55][23] = '6';
			break;
		case 10:
			if (!players[2].jailed)
				boardScreen[54][16] = '6';
			else
				boardScreen[52][16] = '6';
			break;
		case 11:
			boardScreen[50][9] = '6';
			break;
		case 12:
			boardScreen[45][13] = '6';
			break;
		case 13:
			boardScreen[40][9] = '6';
			break;
		case 14:
			boardScreen[35][9] = '6';
			break;
		case 15:
			boardScreen[29][11] = '6';
			break;
		case 16:
			boardScreen[25][9] = '6';
			break;
		case 17:
			boardScreen[20][9] = '6';
			break;
		case 18:
			boardScreen[15][9] = '6';
			break;
		case 19:
			boardScreen[10][9] = '6';
			break;
		case 20:
			boardScreen[5][14] = '6';
			break;
		case 21:
			boardScreen[5][23] = '6';
			break;
		case 22:
			boardScreen[5][37] = '6';
			break;
		case 23:
			boardScreen[5][51] = '6';
			break;
		case 24:
			boardScreen[5][65] = '6';
			break;
		case 25:
			boardScreen[4][81] = '6';
			break;
		case 26:
			boardScreen[5][93] = '6';
			break;
		case 27:
			boardScreen[5][107] = '6';
			break;
		case 28:
			boardScreen[4][127] = '6';
			break;
		case 29:
			boardScreen[5][135] = '6';
			break;
		case 30:
			boardScreen[4][148] = '6';
			break;
		case 31:
			boardScreen[10][149] = '6';
			break;
		case 32:
			boardScreen[15][149] = '6';
			break;
		case 33:
			boardScreen[20][149] = '6';
			break;
		case 34:
			boardScreen[25][149] = '6';
			break;
		case 35:
			boardScreen[29][151] = '6';
			break;
		case 36:
			boardScreen[35][149] = '6';
			break;
		case 37:
			boardScreen[40][149] = '6';
			break;
		case 38:
			boardScreen[45][153] = '6';
			break;
		case 39:
			boardScreen[50][149] = '6';
			break;
		default:
			break;
		}
	}

	//-----TO SCREEN
	//------------------------------------------------------------------
	cout << "\n\n\n";
	for (int x = 0; x < xSize; x++)
	{
		for (int y = 0; y < ySize; y++)
		{
			cout << boardScreen[x][y];
		}
		cout << "\n";
	}
}
