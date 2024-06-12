#pragma once
#include "GameNode.h"
#include "Player.h"
#include "World.h"
#include "WAYPOINT.h"

class VillageScene : public GameNode
{
private:
	Player* _player;
	World* _world;
	WAYPOINT* _WP;
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	VillageScene() {}
	~VillageScene() {}
};

