#include "Stdafx.h"
#include "Balog.h"

HRESULT Balog::init()
{
	monsterImg = new MonsterImage;
	monsterImg->balogInit();
	astar = new RouteFind;
	astar->init();
	astar->setPlayerCoord(monsterLocation);
	lookAngle = Front;
	astar->setSpeed(2);
	hp = 100;
	isDied = false;

	return S_OK ;
}

void Balog::release(void)
{
	SAFE_DELETE(astar);
	monsterImg->balogRelease();
	SAFE_DELETE(monsterImg);
}

void Balog::update(Point2D _camera, RECT playerRect, Point2D playerLocation)
{
	
	camera = _camera;
	
	if (hp <= 0 && !isDied)
	{
		SOUNDMANAGER->FindSound("BalocDie")->Play(0);
		isDied = true;
		isDetectPlayer = false;
		isAttack = false;
		isMove = false;
	}
	
	astar->update(_camera);
	monsterLocation = astar->getPlayerLocation();
	setStatus();
	detectPlayer(playerRect);
	monsterImg->balogUpdate(lookAngle, status);
	if (isAttack)
	{
		astar->setMovePoint(monsterLocation);
	}
	else if (isDetectPlayer)
	{
		MoveToPlayer(playerLocation);
	}
	if (astar->getDestinnation().size() == 0)
		isMove = false;

	enemyRect = RectMakeCenter(monsterLocation.x - camera.x, monsterLocation.y - camera.y, 302, 202);
	detectRect = RectMakeCenter(monsterLocation.x - camera.x, monsterLocation.y - camera.y, 800, 800);
	attackRangeRect = RectMakeCenter(monsterLocation.x - camera.x, monsterLocation.y - camera.y, 100, 100);
	enemyHitBox = RectMakeCenter(monsterLocation.x - camera.x, monsterLocation.y - camera.y + 20, 60, 80);
}


void Balog::render(HDC hdc)
{
	monsterImg->balogAnim(hdc, enemyRect.left, enemyRect.top, status);
}
