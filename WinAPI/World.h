#pragma once

class Inventory;
class WAYPOINT;

class World
{
private:
	int width;
	int height;

	int temp;
public:
	HRESULT init();
	void release(void);
	void update(Point2D camera);
	void render(HDC hdc, int playerX);
};

