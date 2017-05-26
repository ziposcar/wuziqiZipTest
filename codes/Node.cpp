
#include "../heads/Node.h"

Node::Node()
{
	p.x = p.y = -1;
}
Node::Node(const Position &pp, const Vec4 &vec4)
{
	for (int i = 0; i < 4; ++i)
	{
		this->v[i] = vec4.v[i];
	}
	p = pp;
}

bool Node::operator < (const Node &e) const
{
	if (v[3] != e.v[3])
	{
		return v[3] < e.v[3];
	}
	else if (v[2] != e.v[2])
	{
		return v[2] < e.v[2];
	}
	else if (v[1] != e.v[1])
	{
		return v[1] < e.v[1];
	}
	else
	{
		return v[0] < e.v[0];
	}
}
bool Node::operator == (const Node &e) const
{
	for (int i = 0; i < 4; ++i)
	{
		if (v[i] != e.v[i])
		{
			return false;
		}
	}
	return true;
}
bool Node::operator = (const Node &e)
{
	p.x = e.p.x;
	p.y = e.p.y;
	for (int i = 0; i < 4; ++i)
	{
		v[i] = e.v[i];
	}
}
bool Node::operator > (const Node &e) const
{
	if (v[3] != e.v[3])
	{
		return v[3] > e.v[3];
	}
	else if (v[2] != e.v[2])
	{
		return v[2] > e.v[2];
	}
	else if (v[1] != e.v[1])
	{
		return v[1] > e.v[1];
	}
	else
	{
		return v[0] > e.v[0];
	}
}
