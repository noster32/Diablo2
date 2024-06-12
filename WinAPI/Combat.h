#pragma once

class Player;
class DiabloMap;

struct HITEFFECT
{
	int curidx;
	int count;
	float x, y;
	bool hitend;
};

class Combat
{
private:
	int _fireDelay = 0;

	vector<HITEFFECT> _vfireHitEffect;
	vector<HITEFFECT>::iterator _vifireHitEffect;
	vector<HITEFFECT> _viceHitEffect;
	vector<HITEFFECT>::iterator _viiceHitEffect;

public: 
	void update(Player* player, DiabloMap* diaMap);
	void render(HDC hdc, Player* player);
};

