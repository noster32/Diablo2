#pragma once
//========================================================
// # Utils (간소화 하고 싶거나 or 수학적 기능을 모아둔다.)
//========================================================

#define DEG_TO_RAD		0.017453f
#define PI				3.141592654f
#define PI_2			6.283185308f
#define FLOAT_EPSILON	0.0001f
#define FLOAT_TO_INT(f1)		static_cast<int>(f1 + FLOAT_EPSILON)
#define FLOAT_EQUAL(f1, f2)	(fabs(f1 - f2) <= FLOAT_EPSILON)
#define IN_RANGE( value, min, max ) ( ((value) >= (min) && (value) <= (max)) ? 1 : 0 )
#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define TO_BOOL( a )  ( (a != 0) ? true : false )
#define CLAMP(x, upper, lower) (MIN(upper, MAX(x, lower)))

namespace MY_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY);
	float getAngle(float startX, float startY, float endX, float endY);
}

struct Point2D {
	int x, y;

	Point2D() : x(0.0f), y(0.0f) {}
	Point2D(int x, int y) : x(x), y(y) {}

	Point2D& create(const int& p2x, const int& p2y)
	{
		x = p2x;
		y = p2y;
		return Point2D(x, y);
	}

	Point2D operator + (const Point2D& p2) const { return Point2D(x + p2.x, y + p2.y); }
	Point2D operator - (const Point2D& p2) const { return Point2D(x - p2.x, y - p2.y); }
	Point2D operator * (const float f) const { return Point2D(x * f, y * f); }
	Point2D operator / (const float f) const { return Point2D(x / f, y / f); }

	void operator += (const Point2D& p2) { x += p2.x; y += p2.y; }
	//void operator += (const Vector2D & v2) { x += v2.x; y += v2.y; }

	//void operator = (const Vector2D& v2) { x = v2.x; y = v2.y; }

	bool operator >= (const Point2D& p2) const
	{
		if (x >= p2.x && y >= p2.y)
			return true;
		else
			return false;
	}

	bool operator >= (const int& p2) const
	{
		if (x >= p2 && y >= p2)
			return true;
		else
			return false;
	}

	bool operator <= (const int& p2) const
	{
		if (x <= p2 && y <= p2)
			return true;
		else
			return false;
	}

	bool operator == (const Point2D& p2) const
	{
		if (x == p2.x && y == p2.y)
			return true;
		else
			return false;
	}

	bool operator != (const Point2D& p2) const
	{
		if (x == p2.x && y == p2.y)
			return false;
		else
			return true;
	}

	bool operator == (const vector<Point2D>::iterator& iter) const {
		if (x == iter->x && y == iter->y)
			return true;
		else
			return false;
	}

	bool approximate(const Point2D& p2, const int& range) const
	{
		if (x >= (p2.x - range) && x <= (p2.x + range) && y >= (p2.y - range) && y <= (p2.y + range))
			return true;
		else
			return false;
	}

	float distance(const Point2D& p2) const
	{
		return sqrtf(powf(p2.x - x, 2.0f) + powf(p2.y - y, 2.0f));
	}

	float magnitude() const
	{
		return sqrtf(x * x + y * y);
	}

	float getAngle(const Point2D& p2) const
	{
		float tempX = p2.x - x;
		float tempY = p2.y - y;
		float d = sqrt(tempX * tempX + tempY * tempY);
		float angle = acos(tempX / d);

		if (tempY > 0) angle = PI_2 - angle;

		return angle;
	}

	Point2D screenLoca(const Point2D& _origin, int x, int y) const
	{
		return Point2D
		((_origin.x * 160) + (x - y) * (160 / 2),
			(_origin.y * 80) + (x + y) * (80 / 2));
	};

	Point2D screenLocaIso(const Point2D& _origin, int x, int y) const
	{
		return Point2D
		((_origin.x * 160) + (x - y) * (160 / 2),
			(_origin.y * 80) + (x + y) * (80 / 2));
	};
};

struct Vector2D {
	float x, y;


	Vector2D() : x(0.0f), y(0.0f) { }
	Vector2D(float x, float y) : x(x), y(y) { }

	Vector2D operator + (const Vector2D& v2) const { return Vector2D(x + v2.x, y + v2.y); }
	Vector2D operator - (const Vector2D& v2) const { return Vector2D(x - v2.x, y - v2.y); }
	Vector2D operator * (const float f) const { return Vector2D(x * f, y * f); }

	void operator += (const Vector2D& v2) { x += v2.x; y += v2.y; }
	void operator += (const Point2D& p2) { x += p2.x; y += p2.y; }
	void operator = (const Point2D& p2) { x = p2.x; y = p2.y; }

	float Magnitude() const { return sqrt(powf(x, 2.0f) + powf(y, 2.0f)); }
	float DotProduct(const Vector2D& v2) const { return x * v2.x + y * v2.y; }
};

struct Rect2D {
	int left, right, top, bottom;

	Rect2D(int left, int right, int top, int bottom) : left(left), right(right), top(top), bottom(bottom) { }

	bool IntersectRect(const Rect2D& t) const {
		return (left >= t.left && left <= t.right && top >= t.bottom && top <= t.top) ||
			(right >= t.left && right <= t.right && top >= t.bottom && top <= t.top) ||
			(left >= t.left && left <= t.right && bottom >= t.bottom && bottom <= t.top) ||
			(right >= t.left && right <= t.right && bottom >= t.bottom && bottom <= t.top);
	}
	bool IntersectRect(const RECT t) const {
		return (left >= t.left && left <= t.right && top >= t.bottom && top <= t.top) ||
			(right >= t.left && right <= t.right && top >= t.bottom && top <= t.top) ||
			(left >= t.left && left <= t.right && bottom >= t.bottom && bottom <= t.top) ||
			(right >= t.left && right <= t.right && bottom >= t.bottom && bottom <= t.top);
	}
};

struct Node 
{
	int gCost, hCost, num;
	int parentNum;

	int operator == (const Node& rhs) const
	{
		return num == rhs.num;
	}

	Node(int g, int h, int num) : gCost(g), hCost(h), num(num), parentNum(0) { }
	int fCost() const { return gCost + hCost; }
};


namespace std {
	template<>
	struct hash<Node> {
		std::size_t operator() (const Node& node) const 
		{
			return hash<int>()(node.num);
		}
	};
}
