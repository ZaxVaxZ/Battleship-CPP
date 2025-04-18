#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>

using namespace std;

#define Top() cout << "*~-+-+-+-=[{ Battleship game }]=-+-+-+-~*\n\n"

#define SUBMARINE 1
#define FIGHTERJET 2
#define BATTLESHIP 3

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define goxp(n, z)                                                      \
	for (int k = i; k <= i + n; k++)                                    \
	{                                                                   \
		if (predict[k].at(j + z) == '.' || predict[k].at(j + z) == '1') \
			x++;                                                        \
		else                                                            \
			break;                                                      \
	}
#define goyp(n, z)                                                      \
	for (int k = j; k <= j + n; k++)                                    \
	{                                                                   \
		if (predict[i + z].at(k) == '.' || predict[i + z].at(k) == '1') \
			x++;                                                        \
		else                                                            \
			break;                                                      \
	}
#define goxn(n, z)                                                      \
	for (int k = i - n; k <= i; k++)                                    \
	{                                                                   \
		if (predict[k].at(j + z) == '.' || predict[k].at(j + z) == '1') \
			x++;                                                        \
		else                                                            \
			break;                                                      \
	}
#define goyn(n, z)                                                      \
	for (int k = j - n; k <= j; k++)                                    \
	{                                                                   \
		if (predict[i + z].at(k) == '.' || predict[i + z].at(k) == '1') \
			x++;                                                        \
		else                                                            \
			break;                                                      \
	}
#define fillxp(n, z)                 \
	for (int k = i; k <= i + n; k++) \
		predict[k].at(j + z) = '1';
#define fillyp(n, z)                 \
	for (int k = j; k <= j + n; k++) \
		predict[i + z].at(k) = '1';
#define fillxn(n, z)                 \
	for (int k = i - n; k <= i; k++) \
		predict[k].at(j + z) = '1';
#define fillyn(n, z)                 \
	for (int k = j - n; k <= j; k++) \
		predict[i + z].at(k) = '1';
#define iff(a, b, c, d) if ((predict[a].at(b) == '.' || predict[a].at(b) == '1') && (predict[c].at(d) == '.' || predict[c].at(d) == '1'))


/** The general Base class for the two main Board classes containing common methods and data */
class Board
{
	private:
		int opponent_predict[10][10], cell[10][10];

	public:
		Board();

		void check(int &x, int &y);
		void print(bool opponent);
		bool operator!=(Board opponent);
		int available_space(int x, int y, int ship, int direction);
		void place_submarine(int x, int y);
		void place_fighterjet(int x, int y, int direction);
		void place_battleship(int x, int y, int direction);
		int	get_cell(int x, int y);
		void add_prediction(int x, int y, int prediction);
};

#endif