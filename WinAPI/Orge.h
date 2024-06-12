#pragma once
#include "Monster.h"

class Orge : public Monster
{
private:
	int hp;

public:
	HRESULT init();
	void release();
	void update(Point2D _camera, RECT playerRect, Point2D playerLocation) override;
	void render(HDC hdc);


	int getHp(void) { return hp; }
	void hitEnemy(int dmg) { hp -= dmg; }

	Orge() {}
	Orge(Point2D mLocation) : Monster(mLocation) {}
};

