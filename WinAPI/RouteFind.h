#pragma once

#define TILE_WIDTH 160
#define TILE_HEIGHT 80

class RouteFind
{
private:
	vector<int> _vCollisionNode;
	vector<Point2D> _vNeighborTile;
	vector<Point2D> _vRoute;

	Point2D _selected;
	Point2D _mapSize;
	Point2D _tileLocation;
	Point2D _moveTile;
	Point2D _movePoint;
	Point2D _beforePlayerCoord;
	Point2D routeTile;
	
	bool _isMove;

	RECT _player;
	Point2D _objectLocation;
	Point2D _playerLocation;
	Point2D _playerCoord;

	float destAngle;

	int _speed;
	//Start Point
	Point2D current;

public:
	HRESULT init();
	void release(void);
	void update(Point2D camera);
	void render(HDC hdc);

	void WayPoint(Point2D objectCoord, Point2D targetTile);
	void FindPath(Point2D objectCoord, Point2D targetTile);
	void RetracePath(Node start, Node end);
	Point2D distanceBetweenTile(Point2D targetTile);

	void MoveToTile(Point2D tile);
	void MoveToPoint(Point2D point);


	Point2D TileCenterLocation(Point2D Location);
	Point2D CoordCheck(Point2D Location);


	void setPlayerCoord(Point2D player) { _objectLocation = player; }
	Point2D getPlayerCoord(void) { return _playerCoord; }
	Point2D getPlayerLocation(void) { return _objectLocation; }
	void setMovePoint(Point2D pt) { _movePoint = pt; }
	vector<Point2D> getDestinnation(void) { return _vRoute; }
	void destinationClear(void) { if (_vRoute.size() > 0) { _vRoute.clear(); } }
	float getDestAngle(void) { return destAngle; }
	void setSpeed(int speed) { _speed = speed; }
};

