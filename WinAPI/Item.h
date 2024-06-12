#pragma once
#include "GameNode.h"

struct tagItem2
{
	GImage* img;
	char* iName;
	char* iType;
	char* info;
	float x, y;
	RECT rc;
	int invenNum;
	int gold;
	bool click;
};

class Item : public GameNode
{
private:
	vector<tagItem2> _vItem;
	vector<tagItem2>::iterator _viItem;
	int _playerGold;
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	vector<tagItem2> getItem(void) { return _vItem; }
	int getPlayerGold() { return _playerGold; }
	void setPlayerGold(int playerGold) { _playerGold = playerGold; }

	Item() {}
	~Item() {}
};

