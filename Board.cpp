#include "Board.hpp"

/** Board base class default constructor */
Board::Board()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			opponent_predict[i][j] = cell[i][j] = 0;
}

/** Checks if there is available space to place a certain ship in a certain place on the tactical map */
int Board::available_space(int x, int y, int ship, int direction)
{
	switch (ship)
	{
	case SUBMARINE:
		for (int i = x - (x > 0); i <= x + (x < 9); i++)
			for (int j = y - (y > 0); j <= y + (y < 9); j++)
				if (cell[i][j])
					return 0;
		return 1;
	case BATTLESHIP:
		switch (direction)
		{
		case LEFT:
			if (y - 3 < 0)
				return -1;
			for (int i = x - (x > 0); i <= x + (x < 9); i++)
				for (int j = y - 3 - (y > 3); j <= y + (y < 9); j++)
					if (cell[i][j])
						return 0;
			return 1;
		case RIGHT:
			if (y + 3 > 9)
				return -1;
			for (int i = x - (x > 0); i <= x + (x < 9); i++)
				for (int j = y - (y > 0); j <= y + 3 + (y < 6); j++)
					if (cell[i][j])
						return 0;
			return 1;
		case UP:
			if (x - 3 < 0)
				return -1;
			for (int i = y - (y > 0); i <= y + (y < 9); i++)
				for (int j = x - 3 - (x > 3); j <= x + (x < 9); j++)
					if (cell[j][i])
						return 0;
			return 1;
		case DOWN:
			if (x + 3 > 9)
				return -1;
			for (int i = y - (y > 0); i <= y + (y < 9); i++)
				for (int j = x - (x > 0); j <= x + 3 + (x < 6); j++)
					if (cell[j][i])
						return 0;
			return 1;
		}
	case FIGHTERJET:
		switch (direction)
		{
		case LEFT:
			if (y - 2 < 0 || x < 1 || x > 8)
				return -1;
			for (int i = x - 1; i <= x + 1; i++)
				for (int j = y - 2 - (y > 2); j <= y + (y < 9); j++)
					if (cell[i][j])
						return 0;
			for (int i = x - 1 - (x > 1); i <= x + 1 + (x < 8); i++)
				for (int j = y - 1; j <= y + (y < 9); j++)
					if (cell[i][j])
						return 0;
			return 1;
		case RIGHT:
			if (y + 2 > 9 || x < 1 || x > 8)
				return -1;
			for (int i = x - 1; i <= x + 1; i++)
				for (int j = y - (y > 0); j <= y + 2 + (y < 7); j++)
					if (cell[i][j])
						return 0;
			for (int i = x - 1 - (x > 1); i <= x + 1 + (x < 8); i++)
				for (int j = y - 1; j <= y + (y < 9); j++)
					if (cell[i][j])
						return 0;
			return 1;
		case UP:
			if (x - 2 < 0 || y < 1 || y > 8)
				return -1;
			for (int i = y - 1; i <= y + 1; i++)
				for (int j = x - 2 - (x > 2); j <= x + (x < 9); j++)
					if (cell[j][i])
						return 0;
			for (int i = y - 1 - (y > 1); i <= y + 1 + (y < 8); i++)
				for (int j = x - 1; j <= x + (x < 9); j++)
					if (cell[j][i])
						return 0;
			return 1;
		case DOWN:
			if (x + 2 > 9 || y < 1 || y > 8)
				return -1;
			for (int i = y - 1; i <= y + 1; i++)
				for (int j = x - (x > 0); j <= x + 2 + (x < 7); j++)
					if (cell[j][i])
						return 0;
			for (int i = y - 1 - (y > 1); i <= y + 1 + (y < 8); i++)
				for (int j = x - (x > 0); j <= x + 1; j++)
					if (cell[j][i])
						return 0;
			return 1;
		}
	}
	return -2;
}

void Board::place_submarine(int x, int y)
{
	cell[x][y] = 1;
}

void Board::place_fighterjet(int x, int y, int direction)
{
	switch (direction)
	{
	case LEFT:
		for (int k = y - 2; k <= y; k++)
			cell[x][k] = 1;
		for (int k = x - 1; k <= x + 1; k++)
			cell[k][y] = 1;
		break;
	case RIGHT:
		for (int k = y; k <= y + 2; k++)
			cell[x][k] = 1;
		for (int k = x - 1; k <= x + 1; k++)
			cell[k][y] = 1;
		break;
	case UP:
		for (int k = y - 1; k <= y + 1; k++)
			cell[x][k] = 1;
		for (int k = x - 2; k <= x; k++)
			cell[k][y] = 1;
		break;
	case DOWN:
		for (int k = y - 1; k <= y + 1; k++)
			cell[x][k] = 1;
		for (int k = x; k <= x + 2; k++)
			cell[k][y] = 1;
		break;
	}
}

void Board::place_battleship(int x, int y, int direction)
{
	switch (direction)
	{
	case LEFT:
		for (int k = y - 3; k <= y; k++)
			cell[x][k] = 1;
		break;
	case RIGHT:
		for (int k = y; k <= y + 3; k++)
			cell[x][k] = 1;
		break;
	case UP:
		for (int k = x - 3; k <= x; k++)
			cell[k][y] = 1;
		break;
	case DOWN:
		for (int k = x; k <= x + 3; k++)
			cell[k][y] = 1;
		break;
	}
}

/** Checks the validity of the coordinates chosen at random */
void Board::check(int &x, int &y)
{
	if (opponent_predict[x][y] != 0)
		x = y = -1;
}

/** Prints the tactical board of the player and optionally the targeting board as well */
void Board::print(bool opponent)
{
	cout << "   ";
	for (int i = 1; i <= 10; i++)
		cout << " " << i << " ";
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i + 1 << "  ";
		if (i + 1 == 10)
			cout << "\b";
		for (int j = 0; j < 10; j++)
			if (!((j - i) % 2))
			{
				if (cell[i][j])
					cout << (char)176 << "#" << (char)176;
				else
					cout << (char)176 << (char)176 << (char)176;
			}
			else if (cell[i][j])
				cout << (char)178 << "#" << (char)178;
			else
				cout << (char)178 << (char)178 << (char)178;
		cout << endl;
	}
	cout << endl;
	if (!opponent)
		return;
	cout << "   ";
	for (int i = 1; i <= 10; i++)
		cout << " " << i << " ";
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i + 1 << "  ";
		if (i + 1 == 10)
			cout << "\b";
		for (int j = 0; j < 10; j++)
			if (!((j - i) % 2))
			{
				if (opponent_predict[i][j] == 2)
					cout << (char)176 << "x" << (char)176;
				else if (opponent_predict[i][j] == 1)
					cout << (char)176 << "#" << (char)176;
				else
					cout << (char)176 << (char)176 << (char)176;
			}
			else if (opponent_predict[i][j] == 2)
				cout << (char)178 << "x" << (char)178;
			else if (opponent_predict[i][j] == 1)
				cout << (char)178 << "#" << (char)178;
			else
				cout << (char)178 << (char)178 << (char)178;
		cout << endl;
	}
	cout << endl;
}

/** Returns the value in the board at x, y coordinates */
int Board::get_cell(int x, int y)
{
	if (x < 0 || x > 9 || y < 0 || y > 9)
		return -1;
	return cell[x][y];
}

/** Adds a new prediction */
void Board::add_prediction(int x, int y, int prediction)
{
	if (x < 0 || x > 9 || y < 0 || y > 9)
		return ;
	opponent_predict[x][y] = prediction;
}

bool Board::operator!=(Board opponent)
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (opponent.cell[i][j] == 1 && opponent_predict[i][j] != opponent.cell[i][j])
				return true;
	return false;
}