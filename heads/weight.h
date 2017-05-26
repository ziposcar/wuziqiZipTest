
#pragma once
#include "BasicClasses.h"

class weight
{
public:
	Vec4 wei[3][20][20];
public:
	weight();
	bool update(const int &who, const int &x, const int &y, const int &w, const int &level);
	bool update(const int &who, const Position &p, const int &w, const int &level);
};
