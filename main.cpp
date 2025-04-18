#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <ctime>
#include "Human_Board.hpp"
#include "NPC_Board.hpp"

using namespace std;

/** The main function of the program containing all the required code to run the game with the help of the 2 board classes */
int main()
{
	srand(time(NULL));
	Human_Board Player_board;
	NPC_Board PC_board;
	char choice;
	do
	{
		system("cls");
		Top();
		cout << ">> Choose what you'd like to do:\n\n";
		cout << "1> Start a new game.\n\n";
		cout << "2> Learn the rules of the game.\n\n";
		cout << "3> Exit.\n\n";
		do
		{
			choice = getch() - 48;
		} while (choice < 1 || choice > 3);
		if (choice == 3)
		{
			system("cls");
			Top();
			cout << ">> Thanks for using this program ^__^ | Made by ZaX\n";
			getch();
			return 0;
		}
		if (choice == 2)
		{
			system("cls");
			Top();
			cout << ">> This is a board game, that relies on expectation, observation, and guessing.\n\n";
			cout << ">> You start out with a 10x10 table that will be your \"map\", and you will fill\n   it with 3 types of ships:\n\n";
			cout << "1> Battleships, you get 2 of them, and they are formed of 4 consecutive squares.\n";
			cout << "2> Fighter jets, they look like the letter T, and you get two of them as well.\n";
			cout << "3> Submarines, you get four of these one-squared ships.\n\n";
			cout << ">> You cannot place two shapes so that they are touching (even from corners).\n";
			cout << ">> You cannot place two shapes crossing each other.\n\n";
			cout << ">> After you've finished planning your map, you get another blank map on which\n";
			cout << "   you'll be making your prediction for opponent's map.\n";
			cout << ">> The players take turn, in each turn, the player must choose some coordinates\n";
			cout << "   to check that cell on the opponent's map, if it is filled (colored/used) the\n";
			cout << "   second empty map of that player will color as well, else it would put an X.\n";
			cout << ">> The winner is the first player to have discovered the other's complete map!\n";
			cout << ">> Remember once you completely discover a ship from the opponent's map, don't\n";
			cout << "   hit the cells surrounding that ship because no two ships can be touching.\n";
			cout << ">> Press any key to go back to main menu.\n";
			getch();
		}
	} while (choice != 1);
	Player_board.start_up();
	int stillgoing, x, y;
	do
	{
		do
		{
			system("cls");
			Player_board.print(true);
			cout << ">> Enter the coordinates of the cell to hit on opponent map: ";
			cin >> x >> y;
			if (cin.eof())
				break;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			x--;
			y--;
			Player_board.check(x, y);
		} while (x < 0 || y < 0 || x > 9 || y > 9);
		system("cls");
		Player_board.print(true);
		if (Player_board.mark(x, y, PC_board))
			cout << ">> Congrats! you hit an opponent's ship! ";
		else
			cout << ">> Too bad! You hit water! ";
		getch();
		stillgoing = PC_board.play(Player_board);
	} while (Player_board != PC_board && stillgoing);
	return 0;
}
