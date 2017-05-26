
#include "../heads/Board.h"

//自检输出流

int Board::size() const
{
	return sizeOfBoard;
}
int Board::who() const
{
	return whosePart;
}
int Board::at(const int &x, const int &y) const
{
	return boardData[x][y];
}

bool Board::tmp(const Node &a, const Node &b, const int &fri) const
{
	for (int i = 3; i >= 0; --i)
	{
		if (a.v[i] > b.v[i])
		{
			return true;
		}
		else if (a.v[i] < b.v[i])
		{
			return false;
		}
		else if (this->wei[fri % 2 + 1][a.p.x][a.p.y].v[i] > this->wei[fri % 2 + 1][b.p.x][b.p.y].v[i])
		{
			return true;
		}
		else if (this->wei[fri % 2 + 1][a.p.x][a.p.y].v[i] < this->wei[fri % 2 + 1][b.p.x][b.p.y].v[i])
		{
			return false;
		}
	}
	return false;
}

bool Board::DataInput(std::ifstream &fin)
{
	fin >> sizeOfBoard;		//棋盘大小
	fin >> whosePart;		//黑白手
	numOfPieces = 0;
	for (int i = 0; i < size(); ++i)
	{
		for (int j = 0; j < size(); ++j)
		{
			fin >> boardData[i][j];
			if (boardData[i][j])
			{
				++numOfPieces;
			}
			if (fin.eof())
			{
				return false;
			}
		}
	}
	maxBit = 0;
	return true;
}

Position Board::Put()
{
	//**检测必封必长的连

	for (int k = 0; k < 2; ++k)
	{
		for (int i = 0; i < size(); ++i)
		{
			for (int j = 0; j < size(); ++j)
			{
				if (boardData[i][j] == 0)
				{
					if(find_line(Position(i, j), whosePart))
					{
						exit(i * 15 + j);
					}
				}
			}
		}
		whosePart = whosePart % 2 + 1;
	}

	//*权值覆盖
	GetWeightAll();

	if (DEBUG)
	{
		//输出中间权值，需注释eleGo中的
		//myProcess.StartInfo.UseShellExecute = false;
		//myProcess.StartInfo.CreateNoWindow = true;
		DEBUG_SeeWeight();
	}

	//*gameTree
	int beginOfGameTree = 4;
	if (numOfPieces > 4)
	{
		if (GameTree())
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
		if (DEBUG)
		{
			getchar();
		}
	}

	//**必输拯救
	//resistForDeath();

	//*权值分析

	return Decide(*this).p;

	//从中心寻找可放置点
	exit(-1);
}

struct Tmp
{
	Position p;
	int lastSuper;
	int valSelf;
	bool operator < (const Tmp &e) const
	{
		return (lastSuper==e.lastSuper)?(valSelf>e.valSelf):((lastSuper==0||e.lastSuper==0)?(lastSuper==0):(valSelf>e.valSelf));
	}
	void operator () (const int &x, const int &y, const int &l, const int &val)
	{
		p.x = x;
		p.y = y;
		lastSuper = l;
		valSelf = val;
	}
};
void Board::resistForDeath()
{
	int numOfSuperNum = 0, maxWei = 0;
	Board dtmp = *this;
	int tmpwei[15][15];
	for (int i = 0; i < size(); ++i)
	{
		for (int j = 0; j < size(); ++j)
		{
			if (boardData[i][j] == 0 && wei[whosePart % 2 + 1][i][j].v[3])
			{
				++numOfSuperNum;
				maxWei = (maxWei<wei[whosePart % 2 + 1][i][j].v[3])?wei[whosePart % 2 + 1][i][j].v[3]:maxWei;
			}
		}
	}
	if (numOfSuperNum > 3 || (numOfSuperNum == 3 && maxWei > 20))
	{
		std::vector<Tmp> v;
		Tmp tmp;
		for (int i = 0; i < size(); ++i)
		{
			for (int j = 0; j < size(); ++j)
			{
				if (boardData[i][j] == 0 && (wei[whosePart % 2 + 1][i][j].v[3]) || (wei[whosePart][i][j].v[3]))
				{
					dtmp.boardData[i][j] = whosePart;
					memset(dtmp.wei, 0, sizeof(dtmp.wei));
					int superPoint = 0;
					for (int k = 0; k < size(); ++k)
					{
						for (int l = 0; l < size(); ++l)
						{
							if (dtmp.boardData[k][l] == 0)
							{
								dtmp.GetWeight(Position(k, l), whosePart % 2 + 1);
								if (dtmp.wei[whosePart % 2 + 1][k][l].v[3] > 1)
								{
									++superPoint;
									break;
								}
							}
						}
					}
					tmp(i, j, superPoint, wei[whosePart][i][j].v[3] * 1000000 + wei[whosePart % 2 + 1][i][j].v[3] * 10000 + wei[whosePart % 2 + 1][i][j].v[2] * 100 + wei[whosePart % 2 + 1][i][j].v[1]);
					v.push_back(tmp);
					dtmp.boardData[i][j] = 0;
				}
			}
		}
		std::sort(v.begin(), v.end());
		//if (v[0].lastSuper == 0 || v[0].valSelf >= 10000)
		{
			exit(v[0].p.x * 15 + v[0].p.y);
		}
	}
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			if (wei[whosePart][i][j].v[3] == 1)
			{
				wei[whosePart][i][j].v[3] = 0;
			}
		}
	}
}

int Board::friendly(const Position &p) const
{
	return boardData[p.x][p.y];
}

Position move(const Position &p, const int &d)
{
	return Position(p.x + dir[d][0], p.y + dir[d][1]);
}

bool Board::legal(const Position &p) const
{
	return p.x >= 0 && p.y >= 0 && p.x < size() && p.y < size();
}

void Board::DEBUG_SeeWeight() const
{
	for (int w = 1; w < 3; ++w)
	{
		for (int k = 0; k < 4; ++k)
		{
			for (int i = 0; i < 15; ++i)
			{
				for (int j = 0; j < 15; ++j)
				{
					printf("%3d", wei[w][i][j].v[k]);
				}
				printf("\n");
			}
			printf("\n");
		}
		system("pause");
	}
}