
#pragma once

#include "BasicClasses.h"

class Node : public Vec4
{
public:
	Position p;
	Node(const Position &pp, const Vec4 &vec4);
	Node();
	bool operator < (const Node &e) const;
	bool operator == (const Node &e) const;
	bool operator = (const Node &e);
	bool operator > (const Node &e) const;
};