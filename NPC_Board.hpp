#ifndef NPC_BOARD_HPP
#define NPC_BOARD_HPP


#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#include <conio.h>
#include "Board.hpp"

using namespace std;

/** Board class specific for the computer non-human player */
class NPC_Board : public Board
{
	int nextx, nexty, tanks, ships, planes;
	stack<pair<int, int>> xy;
	vector<pair<int, int>> finished;
	bool direction[4], available[10];
	string predict[10];

public:
	NPC_Board();
	pair<int, int> getCoords();
	int play(Board opponent);
};


#endif