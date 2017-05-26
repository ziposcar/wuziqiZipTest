
#include "../heads/weight.h"
#include <cstdio>
#include <cstring>
#include <iostream>

weight::weight()
{
	memset(wei, 0, sizeof(wei));
}
bool weight::update(const int &who, const int &x, const int &y, const int &w, const int &level)
{
	if (level == 3 && wei[who][x][y].v[3])
	{
		wei[who][x][y].v[3] += 20;
		//return true;
	}
	else if (level == 3 && wei[who][x][y].v[2])
	{
		wei[who][x][y].v[3] += 1;
	}
	else if (level == 2 && wei[who][x][y].v[2])
	{
		wei[who][x][y].v[2] += 5;
	}
	else if (level == 1 && wei[who][x][y].v[2])
	{
		wei[who][x][y].v[2] += 1;
	}
	else if (level == 1 && wei[who][x][y].v[1])
	{
		wei[who][x][y].v[2] += 1;
	}
	wei[who][x][y].v[level] += w;
	if (wei[who][x][y].v[level] < 0)
	{
		std::cout << "intager overflow!\n" << std::endl;
		return false;
	}
	return true;
}
bool weight::update(const int &who, const Position &p, const int &w, const int &level)
{
	return update(who, p.x, p.y, w, level);
}