#pragma once
#include "MonsterImage.h"
#include "RouteFind.h"

class Player;

enum LookAngle
{
	Front, LeftDown, Left, LeftUp, Up, RightUp, Right, RightDown
};

enum Status
{
	Idle, Move, Attack, Died, GetHit
};
class Monster
{
protected:
	MonsterImage* monsterImg;
	RouteFind* astar;

	LookAngle lookAngle;
	Status status;

	RECT detectRect;
	RECT attackRangeRect;
	RECT enemyHitBox;
	RECT enemyRect;

	bool isDetectPlayer;
	bool isAttack;
	bool isMove;
	bool isDied;

	Point2D monsterLocation;
	Point2D camera;

	int atk;

	void LookAngleCal(Point2D playerLocation);
	void setStatus(void); 
	void MoveToPlayer(Point2D playerLocation);
	void AttackPlayer(Player* player);
	void detectPlayer(RECT playerRect);
	
public:
	virtual HRESULT init(void);
	void release(void);
	virtual void update(Point2D camera, RECT playerRect, Point2D playerLocation);
	virtual void render(HDC hdc);

	bool getIsAttack(void) { return isAttack; }
	RECT getAttackRange(void) { return attackRangeRect; }
	RECT getHitBox(void) { return enemyHitBox; }
	float getMonsterX() { return monsterLocation.x; }
	float getMonsterY() { return monsterLocation.y; }

	void setLocation(Point2D pt) { monsterLocation = pt; }

	Monster() : isDied(false) {}
	Monster(Point2D mLocation): monsterLocation(mLocation) {}
};


