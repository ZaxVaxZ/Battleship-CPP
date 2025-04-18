#ifndef HUMAN_BOARD_HPP
#define HUMAN_BOARD_HPP

#include <iostream>
#include <stdlib.h>
#include <limits>
#include <algorithm>
#include <conio.h>
#include "Board.hpp"

using namespace std;

/** Board class specific for the human player */
class Human_Board : public Board
{
public:
	void start_up();
	bool mark(int x, int y, Board opponent);
};

#endif