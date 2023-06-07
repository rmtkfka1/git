#pragma once

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;


struct Pos {
	float x{};
	float y{};

	RECT operator+(const RECT& r) {
		RECT ret{};
		ret.left	= x + r.left;
		ret.top		= y + r.top;
		ret.right	= x + r.right;
		ret.bottom	= y +r.bottom;
		return ret;
	}

	RECT operator-(const RECT& r) {
		RECT ret{};
		ret.left	= r.left - x;
		ret.top		= r.top - y;
		ret.right	= r.right - x;
		ret.bottom	= r.bottom - y;
		return ret;
	}

	Pos operator*(const float f) {
		Pos ret;
		ret.x = x * f;
		ret.y = y * f;
		return ret;
	}

	Pos operator-(const Pos& p) {
		Pos ret;
		ret.x = x - p.x;
		ret.y = y - p.y;
		return ret;
	}
	Pos operator+(const Pos& p) {
		Pos ret;
		ret.x = x + p.x;
		ret.y = y + p.y;
		return ret;
	}

	void operator-=(const Pos& p) {
		x -= p.x;
		y -= p.y;
	}
	void operator+=(const Pos& p) {
		x += p.x;
		y += p.y;
	}

	bool operator!=(const Pos& p) {
		return (x != p.x || y != p.y);
	}
};

struct Stat
{
	int32 hp = 0;
	int32 maxhp = 0;
	float speed = 0;
};