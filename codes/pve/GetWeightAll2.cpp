
#include "../../heads/pve/Board.h"


bool Board::find_line(const Position &p, const int &fri) const
{
	//遍历方向
	const Position &p_0 = p;
	for (int round = 0; round < 8; ++round)
	{
		int len;
		Position tmp = p_0;

		Position p__1 = move(p_0, (round + 4)%8);
		Position p__2 = move(p__1, (round + 4)%8);
		Position p__3 = move(p__2, (round + 4)%8);
		Position p_1 = move(p_0, round);
		Position p_2 = move(p_1, round);
		Position p_3 = move(p_2, round);
		Position p_4 = move(p_3, round);
		Position p_5 = move(p_4, round);

		if ((WHOSE_SPACE(p_1, fri) && WHOSE_SPACE(p_2, fri) && WHOSE_SPACE(p_3, fri) && WHOSE_SPACE(p__1, fri)) || (WHOSE_SPACE(p_1, fri) && WHOSE_SPACE(p_2, fri) && WHOSE_SPACE(p__1, fri) && WHOSE_SPACE(p__2, fri)) || ((WHOSE_SPACE(p_1, fri) && WHOSE_SPACE(p_2, fri) && WHOSE_SPACE(p_3, fri) && WHOSE_SPACE(p_4, fri))))
		{
			return true;
		}
	}
	return false;
}
void Board::GetWeight(const Position &p, const int &fri)
{
	const Position &p_0 = p;
	for (int round = 0; round < 8; ++round)
	{
		int len;
		Position tmp = p_0;

		Position p__1 = move(p_0, (round + 4)%8);
		Position p__2 = move(p__1, (round + 4)%8);
		Position p__3 = move(p__2, (round + 4)%8);
		Position p_1 = move(p_0, round);
		Position p_2 = move(p_1, round);
		Position p_3 = move(p_2, round);
		Position p_4 = move(p_3, round);
		Position p_5 = move(p_4, round);

		if ((WHOSE_SPACE(p_1, fri) && WHOSE_SPACE(p_2, fri) && WHOSE_SPACE(p_3, fri) && WHOSE_SPACE(p__1, fri)) || (WHOSE_SPACE(p_1, fri) && WHOSE_SPACE(p_2, fri) && WHOSE_SPACE(p__1, fri) && WHOSE_SPACE(p__2, fri)) || ((WHOSE_SPACE(p_1, fri) && WHOSE_SPACE(p_2, fri) && WHOSE_SPACE(p_3, fri) && WHOSE_SPACE(p_4, fri))))
		{
			update(fri, p, 10000, 3);
			break;
		}

		//3连
		if (EMPTY_SPACE(p_1) && WHOSE_SPACE(p_2, fri) && WHOSE_SPACE(p_3, fri) && WHOSE_SPACE(p_4, fri) && EMPTY_SPACE(p_5))
		{
			update(fri, p, 1, 2);
			update(fri, p_1, 4, 3);
		}
		else if ((!EMPTY_SPACE(p__1)) && WHOSE_SPACE(p_1, fri) && WHOSE_SPACE(p_2, fri) && WHOSE_SPACE(p_3, fri) && EMPTY_SPACE(p_4)  && (!EMPTY_SPACE(p_5)))
		{
			if (WHOSE_SPACE(p_1, whosePart))
			{
				update(fri, p, 1, 3);
				update(fri, p, 4, 2);
			}
			else
			{
				update(fri, p, 3, 2);
			}
		}
		//3断
		else if (EMPTY_SPACE(p__2) && WHOSE_SPACE(p__1, fri) && WHOSE_SPACE(p_1, fri) && WHOSE_SPACE(p_2, fri) && EMPTY_SPACE(p_3))
		{
			if (WHOSE_SPACE(p__1, whosePart))
			{
				update(fri, p, 5, 3);
				update(fri, p__2, 5, 2);
				update(fri, p_3, 5, 2);
			}
			else
			{
				update(fri, p, 4, 3);
				update(fri, p__2, 3, 3);
				update(fri, p_3, 3, 3);
			}
		}
		//3散
		else if (EMPTY_SPACE(p_2) && WHOSE_SPACE(p__1, fri) && WHOSE_SPACE(p_1, fri) && WHOSE_SPACE(p_3, fri) && (!WHOSE_SPACE(p__2, fri)))
		{
			update(fri, p, 4, 2);
		}
		//3死
		else if (WHOSE_SPACE(p_4, fri) && (!WHOSE_SPACE(p_5, fri)) && (!EMPTY_SPACE(p_5)) && (EMPTY_SPACE(p_1) && WHOSE_SPACE(p_2, fri) && WHOSE_SPACE(p_3, fri)))
		{
			if (WHOSE_SPACE(p_4, whosePart))
			{
				update(fri, p, 1, 3);
				update(fri, p, 1, 2);
				update(fri, p_1, 1, 3);
				update(fri, p_1, 3, 2);
			}
			else
			{
				update(fri, p, 1, 2);
				update(fri, p_1, 3, 2);
			}
		}
		else if (WHOSE_SPACE(p_4, fri) && (!WHOSE_SPACE(p_5, fri)) && (!EMPTY_SPACE(p_5)) && (EMPTY_SPACE(p_2) && WHOSE_SPACE(p_1, fri) && WHOSE_SPACE(p_3, fri)))
		{
			if (WHOSE_SPACE(p_4, whosePart))
			{
				update(fri, p, 1, 3);
				update(fri, p, 1, 2);
				update(fri, p_2, 1, 3);
				update(fri, p_2, 3, 2);
			}
			else
			{
				update(fri, p, 1, 2);
				update(fri, p_2, 3, 2);
			}
		}
		else if (WHOSE_SPACE(p_4, fri) && (!WHOSE_SPACE(p_5, fri)) && (!EMPTY_SPACE(p_5)) && (EMPTY_SPACE(p_3) && WHOSE_SPACE(p_1, fri) && WHOSE_SPACE(p_2, fri)))
		{
			if (WHOSE_SPACE(p_4, whosePart))
			{
				update(fri, p, 1, 3);
				update(fri, p, 1, 2);
				update(fri, p_3, 1, 3);
				update(fri, p_3, 3, 2);
			}
			else
			{
				update(fri, p, 1, 2);
				update(fri, p_3, 3, 2);
			}
		}

		//2连
		else if (EMPTY_SPACE(p_1) && WHOSE_SPACE(p_2, fri) && WHOSE_SPACE(p_3, fri))
		{
			//活
			if (EMPTY_SPACE(p_4))
			{
				update(fri, p, 3, 2);
				update(fri, p_1, 4, 2);
			}
			//半死
			else if (!WHOSE_SPACE(p_4, fri) && EMPTY_SPACE(p__1))
			{
				update(fri, p, 2, 1);
				update(fri, p_1, 2, 1);
			}
		}
		//2断
		else if (WHOSE_SPACE(p_1, fri) && WHOSE_SPACE(p__1, fri) && EMPTY_SPACE(p_2) && EMPTY_SPACE(p__2))
		{
			if (round < 4)
			{
				int tmp = 0;
				tmp += EMPTY_SPACE(p_3);
				tmp += EMPTY_SPACE(p__3);
				update(fri, p, 2 + tmp, 2);
			}
		}
		//1
		else if (WHOSE_SPACE(p_1, fri) && EMPTY_SPACE(p_2) && EMPTY_SPACE(p__1))
		{
			int tmp = 1;
			Position temp = p_2;
			while (EMPTY_SPACE(temp))
			{
				++tmp;
				temp = move(temp, round);
			}
			temp = p_0;
			while (EMPTY_SPACE(temp))
			{
				++tmp;
				temp = move(temp, (round + 4) % 8);
			}
			if (tmp >= 4)
			{
				update(fri, p, tmp - 4, 1);
			}
		}
		else
		{
			Position tmp = p;
			int tmpTimes = -1;
			while (EMPTY_SPACE(tmp))
			{
				++tmpTimes;
				tmp = move(tmp, round);
			}
			update(fri, p, tmpTimes, 0);
		}
	}
	wei[fri][p.x][p.y].UpdateHighestBit();
}
void Board::GetWeightAll()
{
	for (int i = 0; i < size(); ++i)
	{
		for (int j = 0; j < size(); ++j)
		{
			if (boardData[i][j] == 0)
			{
				GetWeight(Position(i, j), 1);
				(maxBit < wei[1][i][j].highestBit)?(maxBit = wei[1][i][j].highestBit):(1);
				GetWeight(Position(i, j), 2);
				(maxBit < wei[2][i][j].highestBit)?(maxBit = wei[2][i][j].highestBit):(1);
			}
		}
	}
}