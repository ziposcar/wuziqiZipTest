
#pragma once

#ifndef DEF_OF_DEBUG
#define DEF_OF_DEBUG
extern bool DEBUG;
#endif

typedef double& out;
struct Position
{
	int x;
	int y;
	Position();
	Position(const int &xx, const int &yy);
};

class Vec4
{
public:
	int v[4];
	int highestBit;
	Vec4();
	void UpdateHighestBit();
	bool operator < (const Vec4 &e) const;
	bool operator == (const Vec4 &e) const;
	bool operator > (const Vec4 &e) const;
};