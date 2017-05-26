
#include "../heads/BasicClasses.h"

bool DEBUG;

Position::Position()
{
	x = -1;
	y = -1;
}
Position::Position(const int &xx, const int &yy)
{
	x = xx;
	y = yy;
}

bool Vec4::operator < (const Vec4 &e) const
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
bool Vec4::operator == (const Vec4 &e) const
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
bool Vec4::operator > (const Vec4 &e) const
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

Vec4::Vec4()
{
	highestBit = 0;
}

void Vec4::UpdateHighestBit()
{
	int i;
	for (i = 3; i > 0; --i)
	{
		if ((v[i] > 1 && i == 3) || (i < 3 && v[i] > 0))
		{
			break;
		}
	}
	(highestBit < i)?(highestBit = i):(1);
}