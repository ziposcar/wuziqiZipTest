
#include "../heads/libAI.h"

void qs(std::vector<Node> &vec, const int &fri, const Board &board)
{
	//std::sort(vec.begin(), vec.end(), board.tmp);
	for (int i = 0; i < vec.size(); ++i)
	{
		int k = i;
		for (int j = i; j < vec.size(); j++)
		{
			if (!board.tmp(vec[k], vec[j], fri))
			{
				k = j;
			}
		}
		Node t = vec[i];
		vec[i] = vec[k];
		vec[k] = t;
	}

	for (int i = vec.size() - 1; i > 0; --i)
	{
		if (!(board.wei[fri % 2 + 1][vec[0].p.x][vec[0].p.y] == board.wei[fri % 2 + 1][vec[i].p.x][vec[i].p.y]))
		{
			vec.pop_back();
		}
	}
}
Node Decide(const Board &board)
{
	Board b = board;
	std::priority_queue<Node> q[3];

	for (int way = 1; way <= 2; ++way)
	{
		for (int i = 0; i < b.sizeOfBoard; ++i)
		{
			for (int j = 0; j < b.sizeOfBoard; ++j)
			{
				if (b.boardData[i][j] == 0)
				{
					q[way].push(Node(Position(i, j), b.wei[way][i][j]));
					/*
					int k;
					for (k = 3; k > 0; --k)
					{
						if (b.wei[way][i][j].v[k])
						{
							break;
						}
					}
					*/
				}
			}
		}
	}

	srand(unsigned(time(0)));

	std::vector<Node> vec[3];
	int maxLev[3];
	for (int i = 1; i <= 2; ++i)
	{
		maxLev[i] = 0;
		int j;
		for (j = 3; j >= 0; --j)
		{
			if (q[i].top().v[j])
			{
				break;
			}
		}
		maxLev[i] = j;
	}
	for (int i = 1; i <= 2; ++i)
	{
		vec[i].push_back(q[i].top());
		q[i].pop();
		while (!q[i].empty() && vec[i][vec[i].size() - 1].v[maxLev[i]] == q[i].top().v[maxLev[i]])
		{
			vec[i].push_back(q[i].top());
			q[i].pop();
		}
	}
	qs(vec[1], 1, b);
	qs(vec[2], 2, b);
	if (vec[b.whosePart][0].v[3])
	{
		return vec[b.whosePart][rand() % vec[b.whosePart].size()];
	}
	if (vec[b.whosePart][0] < vec[b.whosePart % 2 + 1][0])
	{
		return vec[b.whosePart % 2 + 1][rand() % vec[b.whosePart % 2 + 1].size()];
	}
	else
	{
		return vec[b.whosePart][rand() % vec[b.whosePart].size()];
	}
}
