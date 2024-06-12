#pragma once
#include "GameNode.h"
#include "Inventory.h"
#include "PlayerStatUI.h"
#include "Shop.h"

class Player;

class UI2:public GameNode
{
private:
	Inventory* _inventory;
	PlayerStatUI* _pStatUI;
	Shop* _shop;

	int _count;
	int _cursorFrame;
	int _skillFrame;

	bool _isStatButtonPush;
	bool _isItemButtonPush;

	RECT _skillR[4];
	bool _skillClick;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(Player* p);

	int& getSkillFrame(void) { return _skillFrame; }

	UI2(){}
	~UI2() {}
};

