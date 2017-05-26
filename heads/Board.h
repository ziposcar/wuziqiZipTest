
#pragma once

#include "BasicClasses.h"
#include "weight.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <functional>
#include <algorithm>
#include <vector>

//Node Decide(std::priority_queue<Node> q);

//从正右顺时针得到8个方向
const int dir[8][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

class Board : public weight
{
private:
	int boardData[20][20];
	int sizeOfBoard;
	int whosePart;
	int numOfPieces;

	int maxBit;
private:
	//move将返回，点p向d方向移动后的Position对象
	bool legal(const Position &p) const;
public:
	int size() const;
	int who() const;
	int at(const int &x, const int &y) const;

	bool tmp(const Node &a, const Node &b, const int &fri) const;

	int friendly(const Position &p) const;
	//棋盘基本数据读入
	bool DataInput(std::ifstream &fin);

	//最优先的决策
	bool find_win(const Position &p) const;
	bool find_line(const Position &p, const int &fri) const;
	//决策
	void GetWeight(const Position &p, const int &fri);
	void GetWeightAll();
	void DEBUG_SeeWeight() const;
	//挽救
	void resistForDeath();

	//博弈树
	bool GameTree();
	int WhoWin();

	Position Put();

	friend Node Decide(const Board &board);
	friend int dfs(const int &depth, out possible, Board& baseBoard);
};

Position move(const Position &p, const int &d);

#define EMPTY_SPACE(p_) (legal(p_) && (friendly(p_) == 0))
#define WHOSE_SPACE(p_, f) (legal(p_) && (friendly(p_) == f))