#include "Stdafx.h"
#include "Orge.h"

HRESULT Orge::init()
{
	monsterImg = new MonsterImage;
	monsterImg->orgeInit();
	astar = new RouteFind;
	astar->init();
	astar->setPlayerCoord(monsterLocation);
	lookAngle = Front;
	astar->setSpeed(2);
	hp = 100;
	isDied = false;

	return S_OK;
}

void Orge::release(void)
{
	SAFE_DELETE(astar);
	monsterImg->ogreRelease();
	SAFE_DELETE(monsterImg);
}

void Orge::update(Point2D _camera, RECT playerRect, Point2D playerLocation)
{
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		hp -= 100;
	}
	camera = _camera;
	if (hp <= 0 && !isDied)
	{
		SOUNDMANAGER->FindSound("OgreDie")->Play(0);
		isDied = true;
		isDetectPlayer = false;
		isAttack = false;
		isMove = false;
	}
	astar->update(_camera);
	monsterLocation = astar->getPlayerLocation();
	setStatus();
	detectPlayer(playerRect);
	monsterImg->orgeUpdate(lookAngle, status);
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

	enemyRect = RectMakeCenter(monsterLocation.x - camera.x, monsterLocation.y - camera.y, 157, 141);
	detectRect = RectMakeCenter(monsterLocation.x - camera.x, monsterLocation.y - camera.y, 800, 800);
	attackRangeRect = RectMakeCenter(monsterLocation.x - camera.x, monsterLocation.y - camera.y, 100, 100);
	enemyHitBox = RectMakeCenter(monsterLocation.x - camera.x, monsterLocation.y - camera.y, 60, 100);
}


void Orge::render(HDC hdc)
{
	monsterImg->orgeAnim(hdc, enemyRect.left, enemyRect.top, status);
}

