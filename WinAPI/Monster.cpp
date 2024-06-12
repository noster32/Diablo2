#include "Stdafx.h"
#include "Monster.h"
#include "Player.h"

void Monster::LookAngleCal(Point2D destLocation)
{
	if ((PI_2 / 16.0f) <= monsterLocation.getAngle(destLocation) && monsterLocation.getAngle(destLocation) < (PI_2 / 16.0f) * 3)
	{
		lookAngle = RightUp;
	}
	else if ((PI_2 / 16.0f) * 3 <= monsterLocation.getAngle(destLocation) && monsterLocation.getAngle(destLocation) < (PI_2 / 16.0f) * 5)
	{
		lookAngle = Up;
	}
	else if ((PI_2 / 16.0f) * 5 <= monsterLocation.getAngle(destLocation) && monsterLocation.getAngle(destLocation) < (PI_2 / 16.0f) * 7)
	{
		lookAngle = LeftUp;
	}
	else if ((PI_2 / 16.0f) * 7 <= monsterLocation.getAngle(destLocation) && monsterLocation.getAngle(destLocation) < (PI_2 / 16.0f) * 9)
	{
		lookAngle = Left;
	}
	else if ((PI_2 / 16.0f) * 9 <= monsterLocation.getAngle(destLocation) && monsterLocation.getAngle(destLocation) < (PI_2 / 16.0f) * 11)
	{
		lookAngle = LeftDown;
	}
	else if ((PI_2 / 16.0f) * 11 <= monsterLocation.getAngle(destLocation) && monsterLocation.getAngle(destLocation) < (PI_2 / 16.0f) * 13)
	{
		lookAngle = Front;
	}
	else if ((PI_2 / 16.0f) * 13 <= monsterLocation.getAngle(destLocation) && monsterLocation.getAngle(destLocation) < (PI_2 / 16.0f) * 15)
	{
		lookAngle = RightDown;
	}
	else
		lookAngle = Right;
}

void Monster::setStatus(void)
{
	if (isDied)
	{
		astar->destinationClear();
		status = Died;
	}
	else if (isAttack && !isDied)
	{
		status = Attack;
	}
	else if (isMove && !isDied)
	{
		status = Move;
	}
	else
		status = Idle;
}

void Monster::MoveToPlayer(Point2D playerLocation)
{
	if (TILEMANAGER->getWall()[astar->CoordCheck(playerLocation).x + (astar->CoordCheck(playerLocation).y * TILEMANAGER->getWorldSize().x)] == 1)
	{
		LookAngleCal(playerLocation);
		isMove = true;
		astar->setMovePoint(playerLocation);
		astar->WayPoint(astar->CoordCheck(monsterLocation), astar->CoordCheck(playerLocation));
	}
}

void Monster::AttackPlayer(Player* player)
{
	player->hitDamage(atk);
}

void Monster::detectPlayer(RECT playerRect)
{
	RECT rc;
	if (IntersectRect(&rc, &attackRangeRect, &playerRect) && !isDied)
	{
		isDetectPlayer = false;
		isAttack = true;
	}
	else if (IntersectRect(&rc, &detectRect, &playerRect) && !isDied)
	{
		isDetectPlayer = true;
		isAttack = false;
	}
	else
	{
		isAttack = false;
		isDetectPlayer = false;
	}


}

HRESULT Monster::init(void)
{
	return S_OK;
}

void Monster::release(void)
{
}

void Monster::update(Point2D _camera, RECT playerRect, Point2D playerLocation)
{
}

void Monster::render(HDC hdc)
{
}
