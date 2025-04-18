#include "NPC_Board.hpp"

NPC_Board::NPC_Board()
{
	//    x_core=y_core=last_x=last_y=-1;
	//    srand(time(0));
	tanks = planes = ships = 0;
	nextx = nexty = -1;
	for (int i = 0; i < 4; i++)
		direction[i] = false;
	for (int i = 0; i < 10; i++)
		available[i] = true;
	for (int i = 0; i < 10; i++)
		predict[i] = "..........";
	int c = 0, x, y, d;
	do
	{
		x = rand() % 10;
		y = rand() % 10;
		d = rand() % 4 + 1;
		if (available_space(x, y, BATTLESHIP, d) == 1)
			place_battleship(x, y, d), c++;
	} while (c < 2);
	c = 0;
	do
	{
		x = rand() % 10;
		y = rand() % 10;
		d = rand() % 4 + 1;
		if (available_space(x, y, FIGHTERJET, d) == 1)
			place_fighterjet(x, y, d), c++;
	} while (c < 2);
	c = 0;
	do
	{
		x = rand() % 10;
		y = rand() % 10;
		if (available_space(x, y, SUBMARINE, 0) == 1)
			place_submarine(x, y), c++;
	} while (c < 4);
}

pair<int, int> NPC_Board::getCoords()
{
	if (xy.empty())
	{
		int x1 = -2, x = -1, y, y1;
		bool f;
		do
		{
			if (x == 10)
				x = 0;
			if (x == x1)
				break;
			if (x == -1)
				x = rand() % 10, x1 = x;
			if (!available[x])
			{
				x++;
				continue;
			}
			y = rand() % 10;
			y1 = y;
			if (predict[x].at(y) != '.')
			{
				f = false;
				y++;
				if (y == 10)
					y = 0;
				while (y != y1)
				{
					if (predict[x].at(y) == '.')
						break;
					else
						y++;
					if (y == 10)
						y = 0;
				}
				if (y == y1)
				{
					available[x] = false;
					x++;
					continue;
				}
				else
					f = true;
			}
			else
				f = true;
		} while (!f);
		if (y == y1 && !f)
			return make_pair(-1, -1);
		return make_pair(x, y);
	}
	else
	{
		int n;
		fill(direction, direction + 4, false);
		if (predict[max(xy.top().first - 1, 0)].at(xy.top().second) != '.')
			direction[0] = true;
		if (predict[max(xy.top().first - 1, 0)].at(min(xy.top().second + 1, 9)) == '#')
			direction[0] = true;
		if (predict[max(xy.top().first - 1, 0)].at(max(xy.top().second - 1, 0)) == '#')
			direction[0] = true;
		if (predict[xy.top().first].at(min(xy.top().second + 1, 9)) != '.')
			direction[1] = true;
		if (predict[min(xy.top().first + 1, 9)].at(min(xy.top().second + 1, 9)) == '#')
			direction[1] = true;
		if (predict[max(xy.top().first - 1, 0)].at(min(xy.top().second + 1, 9)) == '#')
			direction[1] = true;
		if (predict[min(xy.top().first + 1, 9)].at(xy.top().second) != '.')
			direction[2] = true;
		if (predict[min(xy.top().first + 1, 9)].at(min(xy.top().second + 1, 9)) == '#')
			direction[2] = true;
		if (predict[min(xy.top().first + 1, 9)].at(max(xy.top().second - 1, 0)) == '#')
			direction[2] = true;
		if (predict[xy.top().first].at(max(xy.top().second - 1, 0)) != '.')
			direction[3] = true;
		if (predict[min(xy.top().first + 1, 9)].at(max(xy.top().second - 1, 0)) == '#')
			direction[3] = true;
		if (predict[max(xy.top().first - 1, 0)].at(max(xy.top().second - 1, 0)) == '#')
			direction[3] = true;
		n = count(direction, direction + 4, false);
		// cout<<endl;
		// cout<<n<<endl;
		// char can=gc();
		if (!n)
		{
			return make_pair(-2, -2);
		}
		else if (n == 1)
		{
			for (int i = 0; i < 4; i++)
			{
				if (direction[i] == false)
				{
					switch (i)
					{
					case 0:
						return make_pair(xy.top().first - 1, xy.top().second);
					case 1:
						return make_pair(xy.top().first, xy.top().second + 1);
					case 2:
						return make_pair(xy.top().first + 1, xy.top().second);
					case 3:
						return make_pair(xy.top().first, xy.top().second - 1);
					}
				}
			}
		}
		else
		{
			int x, y = 0;
			x = rand() % n;
			for (int i = 0; i < 4; i++)
			{
				if (y == x && !direction[i])
				{
					switch (i)
					{
					case 0:
						return make_pair(xy.top().first - 1, xy.top().second);
					case 1:
						return make_pair(xy.top().first, xy.top().second + 1);
					case 2:
						return make_pair(xy.top().first + 1, xy.top().second);
					case 3:
						return make_pair(xy.top().first, xy.top().second - 1);
					}
				}
				if (direction[i] == false)
					y++;
			}
		}
	}
	return make_pair(-1, -1);
}

int NPC_Board::play(Board opponent)
{
	pair<int, int> ab;
	if (nextx != -1)
	{
		ab = make_pair(nextx, nexty);
		cout << nextx << " " << nexty << endl;
		nextx = nexty = -1;
	}
	else
		ab = getCoords();
	if (ab.first != -2 && ab.first != -1)
	{
		if (opponent.get_cell(ab.first, ab.second) == 1)
		{
			cout << "\n>> Oh no! The enemy launched a successful strike at (" << ab.first + 1 << ", " << ab.second + 1 << ").\n";
			xy.push(ab);
			finished.push_back(ab);
			predict[ab.first].at(ab.second) = '#';
			for (int i = 0; i < 10; i++)
				cout << predict[i] << endl;
			char c = getch();
			(void) c;
			if ((int)finished.size() == 5)
			{
				for (int i = 0; i < (int)finished.size(); i++)
				{
					for (int j = max(0, finished[i].first - 1); j <= min(9, finished[i].first + 1); j++)
						for (int k = max(0, finished[i].second - 1); k <= min(9, finished[i].second + 1); k++)
							if (predict[j].at(k) == '.')
								predict[j].at(k) = 'x';
				}
				while (!finished.empty())
					finished.pop_back();
				while (!xy.empty())
					xy.pop();
				planes++;
			}
			else if (finished.size() == 4)
			{
				// cout<<"C";
				int xfreq[10] = {}, yfreq[10] = {};
				for (int i = 0; i < 4; i++)
				{
					xfreq[finished[i].first]++;
					yfreq[finished[i].second]++;
				}
				int *xm = max_element(xfreq, xfreq + 10);
				int *ym = max_element(yfreq, yfreq + 10);
				if (xm[0] == 4 || ym[0] == 4)
				{
					for (int i = 0; i < (int)finished.size(); i++)
					{
						for (int j = max(0, finished[i].first - 1); j <= min(9, finished[i].first + 1); j++)
							for (int k = max(0, finished[i].second - 1); k <= min(9, finished[i].second + 1); k++)
								if (predict[j].at(k) == '.')
									predict[j].at(k) = 'x';
					}
					while (!finished.empty())
						finished.pop_back();
					while (!xy.empty())
						xy.pop();
					ships++;
				}
				else if (xm[0] == 3)
				{
					int k = -1;
					pair<int, int> p;
					for (int i = 0; i < (int)finished.size(); i++)
					{
						if (finished[i].first != xm - xfreq)
							p = finished[i];
					}
					for (int i = 0; i < 10; i++)
					{
						if (yfreq[i] != 0)
						{
							if (k == 0)
							{
								k = i;
								break;
							}
							else
								k++;
						}
					}
					if (k == p.second)
					{
						if (p.first < xm - xfreq)
							k = p.first - 1;
						else
							k = p.first + 1;
					}
					else
					{
						if (p.first < xm - xfreq)
							k = p.first + 2;
						else
							k = p.first - 2;
					}
					nextx = k;
					nexty = p.second;
				}
				else
				{
					int k = -1;
					pair<int, int> p;
					for (int i = 0; i < (int)finished.size(); i++)
						if (finished[i].second != ym - yfreq)
							p = finished[i];
					for (int i = 0; i < 10; i++)
					{
						if (xfreq[i] != 0)
						{
							if (k == 0)
							{
								k = i;
								break;
							}
							else
								k++;
						}
					}
					if (k == p.first)
					{
						if (p.second < ym - yfreq)
							k = p.second - 1;
						else
							k = p.second + 1;
					}
					else
					{
						if (p.second < ym - yfreq)
							k = p.second + 2;
						else
							k = p.second - 2;
					}
					nextx = p.first;
					nexty = k;
				}
			}
		}
		else
		{
			cout << "\n>> Ha ha! The enemy launched a failed strike at (" << ab.first + 1 << ", " << ab.second + 1 << ").\n";
			predict[ab.first].at(ab.second) = 'x';
			for (int i = 0; i < 10; i++)
				cout << predict[i] << endl;
			char c = getch();
			(void) c;
			if (xy.empty() && ships != 2 && planes == 2 && tanks == 4)
			{
				// cout<<"STARTING SHIP SWIPE\n";
				int x, y, maxi = 0, mvx = -1, mvy = -1;
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						y = x = 0;
						if (predict[i].at(j) == '.')
						{
							if (i > 2)
								goxn(3, 0) if (x == 4)
								{
									y++;
									fillxn(3, 0)
								}
							x = 0;
							if (j > 2)
								goyn(3, 0) if (x == 4)
								{
									y++;
									fillyn(3, 0)
								}
							x = 0;
							if (i < 7)
								goxp(3, 0) if (x == 4)
								{
									y++;
									fillxp(3, 0)
								}
							x = 0;
							if (j < 7)
								goyp(3, 0) if (x == 4)
								{
									y++;
									fillyp(3, 0)
								}
							x = 0;
						}
						if (y > maxi)
							maxi = y, mvx = i, mvy = j;
					}
				}
				if (mvx != -1)
					nextx = mvx, nexty = mvy;
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (predict[i].at(j) == '.')
							predict[i].at(j) = 'x';
					}
				}
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (predict[i].at(j) == '1')
							predict[i].at(j) = '.';
					}
				}
			}
			if (xy.empty() && planes != 2 && ships == 2 && tanks == 4)
			{
				// cout<<"STARTING PLANE SWIPE\n";
				int x, y, maxi = 0, mvx = -1, mvy = -1;
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						x = y = 0;
						if (predict[i].at(j) == '.')
						{
							if (i > 1)
							{
								goxn(2, 0) if (x == 3)
								{
									if (j > 0 && j < 9)
									{
										iff(i - 2, j - 1, i - 2, j + 1)
										{
											predict[i - 2].at(j - 1) = predict[i - 2].at(j + 1) = '1';
											fillxn(2, 0) y++;
										}
										iff(i, j - 1, i, j + 1)
										{
											predict[i].at(j - 1) = predict[i].at(j + 1) = '1';
											fillxn(2, 0) y++;
										}
									}
									if (j > 1)
										iff(i - 1, j - 2, i - 1, j - 1)
										{
											predict[i - 1].at(j - 2) = predict[i - 1].at(j - 1) = '1';
											fillxn(2, 0) y++;
										}
									if (j < 8)
										iff(i - 1, j + 2, i - 1, j + 1)
										{
											predict[i - 1].at(j + 2) = predict[i - 1].at(j + 1) = '1';
											fillxn(2, 0) y++;
										}
								}
								x = 0;
							}
							if (j > 1)
							{
								goyn(2, 0) if (x == 3)
								{
									if (i > 0 && i < 9)
									{
										iff(i - 1, j - 2, i + 1, j - 2)
										{
											predict[i - 1].at(j - 2) = predict[i + 1].at(j - 2) = '1';
											fillyn(2, 0) y++;
										}
										iff(i - 1, j, i + 1, j)
										{
											predict[i - 1].at(j) = predict[i + 1].at(j) = '1';
											fillyn(2, 0) y++;
										}
									}
									if (i < 8)
										iff(i + 2, j - 1, i + 1, j - 1)
										{
											predict[i + 2].at(j - 1) = predict[i + 1].at(j - 1) = '1';
											fillyn(2, 0) y++;
										}
									if (i > 1)
										iff(i - 2, j - 1, i - 1, j - 1)
										{
											predict[i - 2].at(j - 1) = predict[i - 1].at(j - 1) = '1';
											fillyn(2, 0) y++;
										}
								}
								x = 0;
							}
							if (i < 8)
							{
								goxp(2, 0) if (x == 3)
								{
									if (j > 0 && j < 9)
									{
										iff(i + 2, j - 1, i + 2, j + 1)
										{
											predict[i + 2].at(j - 1) = predict[i + 2].at(j + 1) = '1';
											fillxp(2, 0) y++;
										}
										iff(i, j - 1, i, j + 1)
										{
											predict[i].at(j - 1) = predict[i].at(j + 1) = '1';
											fillxp(2, 0) y++;
										}
									}
									if (j > 1)
										iff(i + 1, j - 2, i + 1, j - 1)
										{
											predict[i + 1].at(j - 2) = predict[i + 1].at(j - 1) = '1';
											fillxp(2, 0) y++;
										}
									if (j < 8)
										iff(i + 1, j + 2, i + 1, j + 1)
										{
											predict[i + 1].at(j + 2) = predict[i + 1].at(j + 1) = '1';
											fillxp(2, 0) y++;
										}
								}
								x = 0;
							}
							if (j < 8)
							{
								goyp(2, 0) if (x == 3)
								{
									if (i > 0 && i < 9)
									{
										iff(i - 1, j + 2, i + 1, j + 2)
										{
											predict[i - 1].at(j + 2) = predict[i + 1].at(j + 2) = '1';
											fillyp(2, 0) y++;
										}
										iff(i - 1, j, i + 1, j)
										{
											predict[i - 1].at(j) = predict[i + 1].at(j) = '1';
											fillyp(2, 0) y++;
										}
									}
									if (i < 8)
										iff(i + 2, j + 1, i + 1, j + 1)
										{
											predict[i + 2].at(j + 1) = predict[i + 1].at(j + 1) = '1';
											fillyp(2, 0) y++;
										}
									if (i > 1)
										iff(i - 2, j + 1, i - 1, j + 1)
										{
											predict[i - 2].at(j + 1) = predict[i - 1].at(j + 1) = '1';
											fillyp(2, 0) y++;
										}
								}
								x = 0;
							}
						}
						if (y > maxi)
							maxi = y, mvx = i, mvy = j;
					}
				}
				// cout<<endl;
				// for(int i=0;i<10;i++) cout<<predict[i]<<endl;
				if (mvx != -1)
					nextx = mvx, nexty = mvy;
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (predict[i].at(j) == '.')
							predict[i].at(j) = 'x';
					}
				}
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (predict[i].at(j) == '1')
							predict[i].at(j) = '.';
					}
				}
			}
		}
	}
	else if (ab.first == -1)
	{
		return 0;
	}
	else
	{
		if (finished.size() == 1)
		{
			for (int j = max(0, finished[0].first - 1); j <= min(9, finished[0].first + 1); j++)
				for (int k = max(0, finished[0].second - 1); k <= min(9, finished[0].second + 1); k++)
					if (predict[j].at(k) == '.')
						predict[j].at(k) = 'x';
			while (!finished.empty())
				finished.pop_back();
			while (!xy.empty())
				xy.pop();
			tanks++;
			play(opponent);
		}
		else
		{
			xy.pop();
			play(opponent);
		}
	}
	if (ships == 2 && tanks == 4 && planes == 2)
	{
		return 0;
	}
	return 1;
}
