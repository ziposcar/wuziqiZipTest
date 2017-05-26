
#pragma once

class Vec4
{
public:
	int v[4];
	bool operator < (const Vec4 &e) const;
	bool operator == (const Vec4 &e) const;
	bool operator > (const Vec4 &e) const;
};