#pragma once
#include "GameNode.h"
#include "Boss.h"
#include "Player.h"
#include "DiabloMap.h"
#include "Combat.h"

struct Tyrael
{
	int x, y, imgFrameX, imgFrameY;
	RECT tyRc;
	bool click;
};



class DungeonScene : public GameNode
{
private:
	Player* _player;
	Boss* _boss;
	DiabloMap* _diaMap;
	Combat* _combat;

	bool _isLoadingSceneImg;
	int _loadingDcnt;
	GImage* _loadingPlusImg;
	
	RECT _alterRc;
	RECT _temp;

	bool _alterActive;

	vector<HITEFFECT> _vDiafireHitEffect;
	vector<HITEFFECT>::iterator _viDiafireHitEffect;
	vector<HITEFFECT> _vDiaiceHitEffect;
	vector<HITEFFECT>::iterator _viDiaiceHitEffect;

	int _count, _fireDelay, _comingCount;
	
	int _text;

	Tyrael _tyrael;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	void collision(void);
	void effectrender(void);

	Player* getPlayer(void) { return _player; }

	DungeonScene() {}
	~DungeonScene() {}
};

