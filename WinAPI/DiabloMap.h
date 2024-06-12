#pragma once
#include "Orge.h"
#include "Balog.h"

class DiabloMap
{
private:
	Orge* _orge;
	Balog* _balog;
	//
	vector<Orge*> _vOrgeSpawnLocation;
	vector<Balog*> _vBalogSpawnLocation;
	int width;
	int height;

	Point2D _camera;

	int temp;
public:
	HRESULT init();
	void release(void);
	void update(Point2D camera, RECT playerRect, Point2D playerCoord);
	void render(HDC hdc);


	void setMobSpawn();

	vector<Orge*> getOrge() { return _vOrgeSpawnLocation; }
	vector<Balog*> getBalog() { return _vBalogSpawnLocation; }
};

