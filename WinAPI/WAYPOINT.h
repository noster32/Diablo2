#pragma once
#include "GameNode.h"

class Player;

struct WayPOINT
{
	GImage* img;
	RECT movePoint;
	RECT cancelRC;
};

class WAYPOINT : public GameNode
{
private:
	RECT _wayPoint;
	RECT newPlayerRC;
	bool _isWayPoint;
	bool _isWayPointClick;
	bool _dungeonMove;

	vector<WayPOINT> _vway;
	vector<WayPOINT>::iterator _viway;

public:
	HRESULT init(void);
	void release(void);
	void update(Player* p);
	void render(void);

	bool getIsWayPoint() { return _isWayPoint; }


	WAYPOINT() {}
	~WAYPOINT() {}
};

