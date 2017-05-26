/*
* @Author: oscar
* @Date:   2016-12-07 21:05:34
* @Last Modified by:   oscar
* @Last Modified time: 2017-01-21 19:29:36
*/
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#include <bits/stdc++.h>
#include "../heads/libAI.h"
using namespace std;
int main(int argc, char const *argv[])
{
	// if (strcmp(argv[1], "DEBUG") == 0)
	// {
	// 	DEBUG = true;
	// 	printf("DEBUG BEGIN\n");
	// }
	// else
	// {
		DEBUG = false;
	// }

	

	string pathOfTemp(getenv("temp"));
	pathOfTemp += "\\";
	ifstream fin((pathOfTemp + "board.dat").c_str());

	Board theBoard;
	if (!theBoard.DataInput(fin))
	{
		return -1;
	}

	Position theChoose = theBoard.Put();

	return (theBoard.size() * theChoose.x + theChoose.y);
}