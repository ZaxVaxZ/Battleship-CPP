#include "Human_Board.hpp"

/** Checks the adjacent cell from the opponent's board and marks the targeting board */
bool Human_Board::mark(int x, int y, Board opponent)
{
	add_prediction(x, y, 2 - opponent.get_cell(x, y));
	return (bool)opponent.get_cell(x, y);
}

/** Responsible for filling up the tactical board of the human player */
void Human_Board::start_up()
{
	int x, y, d, cnt, k;
	bool problem = false, dir[4];
	for (int z = 0; z < 2; z++)
	{
		for (int i = 0; i < 4; i++)
			dir[i] = false;
		system("cls");
		print(false);
		cout << ">> Now place your ";
		switch (z)
		{
		case 0:
			cout << "first";
			break;
		case 1:
			cout << "second";
			break;
		}
		cout << " battleship, that looks like this in Down direction:\n\n";
		cout << "     X\n";
		cout << "     #\n     #\n     #\n\n";
		cout << ">> The \'X\' represents which cell you will be entering the coordinates for.\n";
		if (problem)
		{
			cout << ">> Your previous coordinates had no possible directions to place a battleship (Check rules for more).\n";
			cout << ">> Please enter valid coordinates: ";
		}
		else
			cout << ">> Please enter the battleship's coordinates: ";
		problem = false;
		cin >> x >> y;
		if (cin.eof())
			exit(1);
		while (cin.fail() || x < 1 || y < 1 || y > 10 || x > 10)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ">> Please enter Valid coordinates for the battleship: ";
			cin >> x >> y;
			if (cin.eof())
				exit(1);
		}
		x--;
		y--;
		for (int i = 1; i <= 4; i++)
			if (available_space(x, y, BATTLESHIP, i) < 1)
				dir[i - 1] = true;
		cnt = count(dir, dir + 4, true);
		if (cnt == 4)
		{
			problem = true;
			z--;
		}
		else if (cnt == 3)
		{
			cout << ">> Direction set to the only possible way a battleship could fit in (" << x << ", " << y << ").\n";
			d = find(dir, dir + 4, false) - dir + 1;
		}
		else
		{
			k = 0;
			cout << ">> Now enter a direction for the ship:\n";
			if (!dir[0])
				cout << ++k << "> Up\n";
			if (!dir[1])
				cout << ++k << "> Down\n";
			if (!dir[2])
				cout << ++k << "> Left\n";
			if (!dir[3])
				cout << ++k << "> Right\n";
			do
			{
				d = getch() - 48;
			} while (d > k || d < 1);
			cnt = 0;
			for (int i = 0; i < 4; i++)
			{
				if (!dir[i])
					cnt++;
				if (d == cnt)
				{
					d = i + 1;
					break;
				}
			}
		}
		if (!problem)
			place_battleship(x, y, d);
	}
	problem = false;
	for (int z = 0; z < 2; z++)
	{
		for (int i = 0; i < 4; i++)
			dir[i] = false;
		system("cls");
		print(false);
		cout << ">> Now place your ";
		switch (z)
		{
		case 0:
			cout << "first";
			break;
		case 1:
			cout << "second";
			break;
		}
		cout << " fighter jet, that looks like this in Down direction:\n\n";
		cout << "   # X #\n";
		cout << "     #\n     #\n\n";
		cout << ">> The \'X\' represents which cell you will be entering the coordinates for.\n";
		if (problem)
		{
			cout << ">> Your previous coordinates had no possible directions to place a fighter jet (Check rules for more).\n";
			cout << ">> Please enter valid coordinates: ";
		}
		else
			cout << ">> Please enter the fighter jet's coordinates: ";
		problem = false;
		cin >> x >> y;
		if (cin.eof())
			exit(1);
		while (cin.fail() || x < 1 || y < 1 || y > 10 || x > 10)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ">> Please enter Valid coordinates for the fighter jet: ";
			cin >> x >> y;
			if (cin.eof())
				exit(1);
		}
		x--;
		y--;
		for (int i = 1; i <= 4; i++)
			if (available_space(x, y, FIGHTERJET, i) < 1)
				dir[i - 1] = true;
		cnt = count(dir, dir + 4, true);
		if (cnt == 4)
		{
			problem = true;
			z--;
		}
		else if (cnt == 3)
		{
			cout << ">> Direction set to the only possible way a fighter jet could fit in (" << x << ", " << y << ").\n";
			d = find(dir, dir + 4, false) - dir + 1;
		}
		else
		{
			k = 0;
			cout << ">> Now enter a direction for the ship:\n";
			if (!dir[0])
				cout << ++k << "> Up\n";
			if (!dir[1])
				cout << ++k << "> Down\n";
			if (!dir[2])
				cout << ++k << "> Left\n";
			if (!dir[3])
				cout << ++k << "> Right\n";
			do
			{
				d = getch() - 48;
			} while (d > k || d < 1);
			cnt = 0;
			for (int i = 0; i < 4; i++)
			{
				if (!dir[i])
					cnt++;
				if (d == cnt)
				{
					d = i + 1;
					break;
				}
			}
		}
		if (!problem)
			place_fighterjet(x, y, d);
	}
	for (int z = 0; z < 4; z++)
	{
		system("cls");
		print(false);
		cout << ">> Now place your ";
		switch (z)
		{
		case 0:
			cout << "first";
			break;
		case 1:
			cout << "second";
			break;
		case 2:
			cout << "third";
			break;
		case 3:
			cout << "forth";
			break;
		}
		cout << " submarine, that is just a 1 cell ship:\n\n";
		cout << "     X\n\n";
		cout << ">> Please enter the submarine's coordinates: ";
		cin >> x >> y;
		if (cin.eof())
			exit(1);
		while (cin.fail() || x < 1 || y < 1 || y > 10 || x > 10 || available_space(x - 1, y - 1, SUBMARINE, 0) < 1)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ">> Please enter Valid coordinates for the submarine: ";
			cin >> x >> y;
			if (cin.eof())
				exit(1);
		}
		x--;
		y--;
		place_submarine(x, y);
	}
	system("cls");
}
