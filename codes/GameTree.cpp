
#include "../heads/Board.h"

#include <windows.h>

const int maxDepth = 6;
const int maxBreadth = 4;
const double minBelievePossible = 0.6; 	//0 < x < 0.5
static int numOfDfs = 0;

	LARGE_INTEGER  num;
	long long start,end,freq;

int dfs(const int &depth, out possible, Board& baseBoard);
int CodePosition(const int &code, const int &x, const int &y);
void AddPositionInCode(int code, const Position &p);

bool cmp(const Node &a, const Node &b);
bool Board::GameTree()
{
	double possible;
	Board b = *this;
	int ans;
	int x, y;

	QueryPerformanceFrequency(&num);
	freq = num.QuadPart;
	QueryPerformanceCounter(&num);
	start = num.QuadPart;

	ans = dfs(0, possible, b);

	QueryPerformanceCounter(&num);
	end= num.QuadPart;
	if (DEBUG)
	{
		printf("time=%f\n",((end-start)*1000.0/freq)/numOfDfs);
		getchar();
	}

	if (ans == 0)
	{
		return false;		//对权值系统无改动，即在属性搜索后未找到必输手
	}
	else
	{
		if (ans > pow(sizeOfBoard * sizeOfBoard, maxBreadth - 1))
		{
			return false;	//由于没可能赢所以放弃更新权值
		}
		while (ans)
		{
			y = ans % 15;
			ans /= 15;
			x = ans % 15;
			ans /= 15;

			memset(&wei[1][x][y], 0, sizeof(wei[1][x][y]));
			memset(&wei[2][x][y], 0, sizeof(wei[2][x][y]));
		}
		return true;
	}
}

int dfs(const int &depth, out possible, Board& baseBoard)
{
	using namespace std;

	if (baseBoard.WhoWin())
	{
		possible = 0;
		return -1;
	}
	if (depth > maxDepth)
	{
		possible = 0.5;
		return 0;
	}
	if (DEBUG)
	{
		++numOfDfs;
	}
	//vector<double> vectorOfPossible;
	vector<Node> vectorOfPut;

	//*权值覆盖
	baseBoard.GetWeightAll();

	//权值铺开后，没有足够的可置信点
	if (baseBoard.maxBit < 1)
	{
		memset(baseBoard.wei, 0, sizeof(baseBoard.wei));
		if (depth == 0)
		{
			return 0;
		}
		possible = 0.5;
		return 0;
	}

	//收集可置信点
	int numOfMaxPossiblePoints = 0;
	for (int i = 0; i < baseBoard.sizeOfBoard; ++i)
	{
		for (int j = 0; j < baseBoard.sizeOfBoard; ++j)
		{
			if (baseBoard.boardData[i][j] == 0)
			{
				if (baseBoard.wei[1][i][j].highestBit >= 1 && (!(baseBoard.wei[1][i][j] < baseBoard.wei[2][i][j])))
				{
					vectorOfPut.push_back(Node(Position(i, j), baseBoard.wei[1][i][j]));
					if (baseBoard.wei[1][i][j].v[3] >= 10000)
					{
						++numOfMaxPossiblePoints;
					}
				}
				else if (baseBoard.wei[2][i][j].highestBit >= 1 && (!(baseBoard.wei[2][i][j] < baseBoard.wei[1][i][j])))
				{
					vectorOfPut.push_back(Node(Position(i, j), baseBoard.wei[2][i][j]));
					if (baseBoard.wei[2][i][j].v[3] >= 10000)
					{
						++numOfMaxPossiblePoints;
					}
				}
			}
		}
	}
	sort(vectorOfPut.begin(), vectorOfPut.end(), cmp);
	memset(baseBoard.wei, 0, sizeof(baseBoard.wei));

	int numOfPut = vectorOfPut.size();
	double tempPossible, sumOfPossible = 0;
	int tempState;

	//double minPossible = 1;
	//Position minPossiblePosition;

	bool win = false;
	int impossiblePoints = 0;
	for (int i = 0; i < numOfPut && i < ((numOfMaxPossiblePoints)?(numOfMaxPossiblePoints):(maxBreadth)); ++i)
	{
		baseBoard.boardData[vectorOfPut[i].p.x][vectorOfPut[i].p.y] = baseBoard.whosePart;
		baseBoard.whosePart = baseBoard.whosePart % 2 + 1;
		tempState = dfs(depth + 1, tempPossible, baseBoard);
		baseBoard.whosePart = baseBoard.whosePart % 2 + 1;
		baseBoard.boardData[vectorOfPut[i].p.x][vectorOfPut[i].p.y] = 0;

		//(minPossible > tempPossible)?((minPossible = tempPossible), (minPossiblePosition = vectorOfPut[i])p.):(minPossiblePosition);

		//存在赢手
		if (tempState == -1)
		{
			if (depth == 0)
			{
				QueryPerformanceCounter(&num);
				end= num.QuadPart;
				if (DEBUG)
				{
					printf("time=%f\n",((end-start)*1000.0/freq)/numOfDfs);
					getchar();
					printf("decide by tree, AI must win\n");
					getchar();
				}
				exit(vectorOfPut[i].p.x * baseBoard.sizeOfBoard + vectorOfPut[i].p.y);
			}
			possible = 1;
			return 1;
		}
		else if (tempState == 0)
		{
			win = true;
			//vectorOfPossible.push_back(tempPossible);
			//sumOfPossible += tempPossible;
		}
		else
		{
			//vectorOfPossible.push_back(tempPossible);
			//sumOfPossible += tempPossible;
			AddPositionInCode(impossiblePoints, vectorOfPut[i].p);
		}
	}
	//若无胜利可能
	if (win == false)
	{
		if (depth == 0)
		{
			return 0;
		}
		else
		{
			possible = 0;
			return -1;		//这个-1表示本层失败
		}
	}
	else
	{
		if (depth == 0)
		{
			//if (minPossible > minBelievePossible)
			{
				if (DEBUG)
				{
					printf("decide by tree, but don't know who will win\n");
				}

				//exit(minPossiblePosition.x * baseBoard.sizeOfBoard + minPossiblePosition.y);
			}
			//else
			{
				return impossiblePoints;
			}
		}
		else
		{
			//possible = 1.0 - sumOfPossible / numOfPut;
			return 0;
		}
	}
}

int Board::WhoWin()
{
	for (int i = 0; i < size(); ++i)
	{
		for (int j = 0; j < size(); ++j)
		{
			if (boardData[i][j] != 0)
			{
				if (find_win(Position(i, j)))
				{
					return boardData[i][j];
				}
			}
		}
	}
	return 0;
}

bool Board::find_win(const Position &p) const
{
	const Position &p_0 = p;
	const int fri = boardData[p.x][p.y];
	for (int round = 0; round < 8; ++round)
	{
		int len;
		Position p_1 = move(p_0, round);
		Position p_2 = move(p_1, round);
		Position p_3 = move(p_2, round);
		Position p_4 = move(p_3, round);

		if (WHOSE_SPACE(p_0, fri) && WHOSE_SPACE(p_1, fri) && WHOSE_SPACE(p_2, fri) && WHOSE_SPACE(p_3, fri) && WHOSE_SPACE(p_4, fri))
		{
			return true;
		}
	}
	return false;
}

bool cmp(const Node &a, const Node &b)
{
	return a > b;
}

void AddPositionInCode(int code, const int &x, const int &y)
{
	long long tmp = code * 225;
	if (tmp <= 0x7fffffff)
		code = (code * 15 + x) * 15 + y;
}
void AddPositionInCode(int code, const Position &p)
{
	long long tmp = code * 225;
	if (tmp <= 0x7fffffff)
		code = (code * 15 + p.x) * 15 + p.y;
}