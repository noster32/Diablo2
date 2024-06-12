#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Boss.h"
#include "UI2.h"

class MasterScene : public GameNode
{
private:
	Player* _player;
	UI2* _ui;
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MasterScene() {}
	~MasterScene() {}
};

