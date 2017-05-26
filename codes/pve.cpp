/*
* @Author: oscar
* @Date:   2016-12-14 23:57:12
* @Last Modified by:   oscar
* @Last Modified time: 2017-01-06 22:49:42
*/
#include <bits/stdc++.h>
#include <windows.h>
#include "../heads/pve/Board.h"
using namespace std;

Board boardNow;

int (&boardData)[20][20] = boardNow.boardData;
int &sizeOfBoard = boardNow.sizeOfBoard;
int &whosePart = boardNow.whosePart;
int sumOfPiece;

string pathOfTemp;
string inputFile[2];

char outputQuick[10000];
char integer[8];

inline void input(ifstream &fin)
{
	fin.open(pathOfTemp.c_str());
	fin >> sizeOfBoard >> whosePart;
	for (int i = 0; i < sizeOfBoard; ++i)
	{
		for (int j = 0; j < sizeOfBoard; ++j)
		{
			fin >> boardData[i][j];
		}
	}
	fin.close();
}
inline void outputNS(ofstream &fout)
{
	fout.open(pathOfTemp.c_str());
	fout << sizeOfBoard << ' ' << whosePart << endl;
	strcat(outputQuick, "    ");
	// cout << "    ";
	for (int i = 0; i < sizeOfBoard; ++i)
	{
		strcat(outputQuick, (i>=10)?("  "):("   "));
		itoa(i, integer, 10);
		strcat(outputQuick, integer);
		// printf("%4d", i);
	}
	strcat(outputQuick, "\n");
	// cout << endl;
	for (int i = 0; i < sizeOfBoard; ++i)
	{
		strcat(outputQuick, (i>=10)?("  "):("   "));
		itoa(i, integer, 10);
		strcat(outputQuick, integer);
		// printf("%4d", i);
		for (int j = 0; j < sizeOfBoard; ++j)
		{
			if (boardData[i][j] == 0)
			{
				strcat(outputQuick, "   -");
				// cout << "   " << '-';
			}
			else if (boardData[i][j] == 1)
			{
				strcat(outputQuick, "   X");
				// cout << "   " << 'X';
			}
			else if (boardData[i][j] == 2)
			{
				strcat(outputQuick, "   O");
				// cout << "   " << 'O';
			}
			//cout << boardData[i][j] << ' ';
			fout << boardData[i][j] << ' ';
		}
		strcat(outputQuick, "\n\n");
		// cout << endl << endl;
		fout << endl;
	}
	system("cls");
	printf("%s", outputQuick);
	fout.close();
}
inline void output(ofstream &fout, const int &x, const int &y)
{
	outputQuick[0] = 0;
	strcat(outputQuick, "\n");
	// cout << x << ' ' << y;
	outputNS(fout);
}
void init(ifstream &fin, ofstream &fout)
{
	sumOfPiece = 0;
	memset(boardData, 0, sizeof(boardData));
	fout.open(pathOfTemp.c_str());
	fout << (sizeOfBoard = 15) << ' ' << 1 << endl;
	for (int i = 0; i < sizeOfBoard; ++i)
	{
		for (int j = 0; j < sizeOfBoard; ++j)
		{
			fout << 0 << ' ';
		}
		fout << endl;
	}
	fout.close();
}
void p_go(const int &x, const int &y)
{
	if (boardData[x][y] != 0)
	{
		cout << "please put in the empty place!\n";
		int i, j;
		cin >> i >> j;
		p_go(i, j);
		return;
	}
	boardData[x][y] = whosePart;
	whosePart = whosePart % 2 + 1;
}
void end(const int &endNum)
{
	if(endNum == 0)
	{
		cout << "tie\n";
		getchar();getchar();
		exit(0);
	}
	else
	{
		cout << inputFile[endNum - 1] << " wins!\n";
		getchar();getchar();
		exit(0);
	}
}
int main()
{
	ifstream fin;
	ofstream fout;
	pathOfTemp += (getenv("temp"));
	pathOfTemp += "/board.dat";


	init(fin, fout);
	system("mode con cols=70 lines=35");
	//output(fout);



	//机先
	int timeInterval = 100;
	cout << "please input the repeat interval(ms):";
	cin >> timeInterval;
	cout << "please input first ai exe file:";
	cin >> inputFile[0];
	inputFile[0] += ".exe";
	cout << "please input second ai exe file:";
	cin >> inputFile[1];
	inputFile[1] += ".exe";
	int pick = 0;
	while (sumOfPiece < sizeOfBoard * sizeOfBoard)
	{
		
		int px, py;
		input(fin);

		if (timeInterval)
		{
			Sleep(timeInterval);
		}
		int pos = system(inputFile[pick].c_str());
		// system("cls");
		if (pos == -1)
		{
			cout << !pick << " win!\n";
			return 0;
		}
		px = pos / sizeOfBoard;
		py = pos % sizeOfBoard;
		if (boardData[px][py] != 0)
		{
			cout << "ai error!(put in somewhere have been put)\n";
			return 1;
		}
		boardData[px][py] = whosePart;
		++sumOfPiece;
		// system("cls");
		whosePart = whosePart % 2 + 1;
		output(fout, px, py);

		for (int k = 0; k < 2; ++k)
		{
			for (int i = 0; i < sizeOfBoard; ++i)
			{
				for (int j = 0; j < sizeOfBoard; ++j)
				{
					if (boardData[i][j] == whosePart)
					{
						if(boardNow.find_line(Position(i, j), whosePart))
						{
							end(whosePart);
						}
					}
				}
			}
			whosePart = whosePart % 2 + 1;
		}
		printf("%d %d %s\n", px, py, inputFile[pick].c_str());
		pick = (!pick);
	}
	end(0);
	return 0;

	// pve
	/*while (true)
	{
		int px, py;
		input(fin);

		cin >> px >> py;
		p_go(px, py);

		system("cls");
		output(fout);

		Sleep(1000);
		int pos = system("zipai.exe");
		system("cls");
		if (pos == -1)
		{
			cout << "you win!\n";
			return 0;
		}
		px = pos / sizeOfBoard;
		py = pos % sizeOfBoard;
		//cout << px << ' ' << py << endl;
		if (boardData[px][py] != 0)
		{
			cout << "ai error!(put in somewhere have been put)\n";
			return 1;
		}
		boardData[px][py] = whosePart;
		whosePart = whosePart % 2 + 1;
		output(fout, px, py);

	}*/
}