#include "Stdafx.h"
#include "Player.h"
#include "Boss.h"
#include "Inventory.h"
#include "WAYPOINT.h"

HRESULT Player::init(void)
{
	skillImg = new SKILLIMG;
	skillImg->init();
	hydraskill = new HYDRA;
	hydraskill->init();
	frozenorbskill = new FROZENORB;
	frozenorbskill->init();
	meteorskill = new METEOR;
	meteorskill->init();
	playerImg = new PlayerImg;
	playerImg->init();
	astar = new RouteFind;
	astar->init();

	SOUNDMANAGER->AddSound("Teleport", "Resources/Sounds/player/Teleport.wav");
	SOUNDMANAGER->AddSound("ColdCast", "Resources/Sounds/player/coldcast.wav");
	SOUNDMANAGER->AddSound("FireCast", "Resources/Sounds/player/firecast.wav");
	SOUNDMANAGER->AddSound("FrozenOrb", "Resources/Sounds/player/FrozenOrb.wav")->SetVolume(20);
	SOUNDMANAGER->AddSound("FrozenOrbExplode", "Resources/Sounds/player/FrozenOrbExplode.wav")->SetVolume(20);
	SOUNDMANAGER->AddSound("HydraFireSound", "Resources/Sounds/player/hydraFireSound.wav");
	SOUNDMANAGER->AddSound("MeteorImpact", "Resources/Sounds/player/meteorImpact.wav");

	for (int i = 0; i < 3; i++)
	{
		if (i == 2) hydraSortX[i] = 15;
		else hydraSortX[i] = 0;
		if (i == 0) hydraSortY[i] = 0;
		else hydraSortY[i] = 15;
	}

	PlayerStat _ps;
	ZeroMemory(&_ps, sizeof(PlayerStat));

	_ps.hp = _ps.mp = 1000;
	_ps.maxHp = _ps.maxMp = 1000;
	_ps.atk = 300;
	_ps.def = 300;
	_ps.str = _ps.dex = _ps.life = _ps.energe = 150;
	_ps.speed = 1.5f;
	_ps.hpCnt = _ps.mpCnt = 20;
	_ps.isDie = _ps.ismove = _ps.isskill = _ps.iscasting = false;
	_ps.direction = 0;
	_ps.moveIdx = _ps.skillIdx = _ps.castingIdx = 0;
	_ps.castingName = "파이어캐스트";
	_ps.maxcastIdx = 13;

	_player = _ps;

	_playerMoveTick = _playerSkillTick = _playerCastingTick = _playerShadTick = 0;

	_pmoveName = PLAYERIDLE;
	_pskillName = NAMEMETEOR;

	resetCamera();
	resetRect();

	_cameraShake = _shakeTime = _currentShakeTime = 0;
	_isShake = _isDiaSummon = false;

	astar->setSpeed(3);

	_invenOpen = _statOpen = _WayOpen = _isClickMove = false;
	_cameraMoveD = _cameraMoveY = _isAllStop = _playerSkillAng = 0;
	lastX = lastY = 0;

	return S_OK;
}

void Player::resetCamera()
{
	_camera.x = _player.x - WINSIZE_X / 2;
	_camera.y = _player.y - WINSIZE_Y / 2;
}

void Player::resetRect()
{
	_player.rc = RectMakeCenter(_player.x - _camera.x, _player.y - _camera.y, 60, 90);
	_player.hitRC = RectMakeCenter(_player.x - _camera.x, _player.y - _camera.y, 20, 55);
}

void Player::release(void)
{
	skillImg->release();
	SAFE_DELETE(skillImg);
	hydraskill->release();
	SAFE_DELETE(hydraskill);
	frozenorbskill->release();
	SAFE_DELETE(frozenorbskill);
	meteorskill->release();
	SAFE_DELETE(meteorskill);
	playerImg->release();
	SAFE_DELETE(playerImg);
}

void Player::update(void)
{
	if (!_isAllStop)
	{
		CameraMoveUpdate(true);

		if (!SCENEMANAGER->getWAYP()->getIsWayPoint())
		{
			astar->update(_camera);
			_player.x = astar->getPlayerLocation().x;
			_player.y = astar->getPlayerLocation().y;
			cameraUpdate();
		}
		if (_player.ismove && !SCENEMANAGER->getWAYP()->getIsWayPoint())
		{
			_player.angle = astar->getDestAngle();
			PlayerAngleSet(_player.angle * 180.0f / PI);
			PlayerShadowAngSet(_player.angle * 180.0f / PI);

			_player.rc = RectMakeCenter(_player.x - _camera.x, _player.y - _camera.y, 60, 90);
			_player.hitRC = RectMakeCenter(_player.x - _camera.x, _player.y - _camera.y, 20, 55);
		}

		if (KEYMANAGER->isStayKeyDown(MK_LBUTTON) && _isClickMove)
		{
			Point2D playerLocation(_player.x, _player.y);
			_player.coord = astar->CoordCheck(playerLocation);
			Point2D movePoint = TILEMANAGER->getRealMousePt();
			Point2D moveTile = astar->CoordCheck(movePoint);

			if (moveTile.x >= 0 && moveTile.y >= 0 && moveTile.x <= TILEMANAGER->getWorldSize().x && moveTile.y <= TILEMANAGER->getWorldSize().y)
			{
				if (TILEMANAGER->getWall()[moveTile.x + (moveTile.y * TILEMANAGER->getWorldSize().x)] == 1)
				{
					astar->setMovePoint(movePoint);

					astar->FindPath(_player.coord, moveTile);
					if (!_player.ismove) _player.ismove = true;
				}
			}
		}

		if (astar->getDestinnation().size() == 0)
		{
			_player.ismove = false;
		}
	}
}

void Player::update(Boss* dia)
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_pskillName = NAMEHYDRA;
		_player.castingName = "파이어캐스트";
		_player.maxcastIdx = 13;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_pskillName = NAMEFROZENORB;
		_player.castingName = "아이스캐스트";
		_player.maxcastIdx = 14;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		_pskillName = NAMEMETEOR;
		_player.castingName = "파이어캐스트";
		_player.maxcastIdx = 13;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		_pskillName = NAMETELEPORT;
		_player.castingName = "텔레포트캐스트";
		_player.maxcastIdx = 17;
	}

	CameraMoveUpdate(false);

	astar->update(_camera);

	_player.angle = astar->getDestAngle();
	if (lastX != astar->getPlayerLocation().x || lastY != astar->getPlayerLocation().y)
	{
		_player.x = astar->getPlayerLocation().x;
		_player.y = astar->getPlayerLocation().y;

		lastX = _player.x;
		lastY = _player.y;
	}

	_player.rc = RectMakeCenter(_player.x - _camera.x, _player.y - _camera.y, 60, 90);
	_player.hitRC = RectMakeCenter(_player.x - _camera.x, _player.y - _camera.y, 20, 55);

	cameraUpdate();

	Point2D playerLocation(_player.x, _player.y);
	_player.coord = astar->CoordCheck(playerLocation);

	if (KEYMANAGER->isStayKeyDown(MK_LBUTTON) && _isClickMove)
	{
		PlayerAngleSet(_player.angle * 180.0f / PI);
		PlayerShadowAngSet(_player.angle * 180.0f / PI);
		Point2D movePoint = TILEMANAGER->getRealMousePt();
		Point2D moveTile = astar->CoordCheck(movePoint);

		if (moveTile.x >= 0 && moveTile.y >= 0 && moveTile.x <= TILEMANAGER->getWorldSize().x && moveTile.y <= TILEMANAGER->getWorldSize().y)
		{
			if (TILEMANAGER->getWall()[moveTile.x + (moveTile.y * TILEMANAGER->getWorldSize().x)] == 1)
			{
				astar->setMovePoint(movePoint);

				astar->WayPoint(_player.coord, moveTile);
				if (!_player.ismove) _player.ismove = true;
			}
		}
	}

	if (astar->getDestinnation().size() == 0)
	{
		_player.ismove = false;
	}

	if (KEYMANAGER->isOnceKeyDown(MK_RBUTTON))
	{
		astar->destinationClear();
		PlayerAngleSet(getAngle(_player.x - _camera.x, _player.y - _camera.y, _ptMouse.x, _ptMouse.y) * 180.0f / PI);
		PlayerShadowAngSet(getAngle(_player.x - _camera.x, _player.y - _camera.y, _ptMouse.x, _ptMouse.y) * 180.0f / PI);
		
		_player.endX = _player.x;
		_player.endY = _player.y;
		_player.ismove = false;
		switch (_pskillName)
		{
		case NAMEHYDRA:
			if (!_player.isskill)
			{
				hydraX = _ptMouse.x;
				hydraY = _ptMouse.y;
				_player.mp -= 5;
				SOUNDMANAGER->FindSound("FireCast")->Play(0);
				for (int i = 0; i < 3; i++)
				{
					hydraskill->setHydraInfo();
					hydraskill->setHydraPosition(hydraskill->getHydraIdx(), hydraX + hydraSortX[i] + _camera.x, hydraY + hydraSortY[i] + _camera.y);
					hydraskill->setSummon(hydraskill->getHydraIdx(), true);
					hydraskill->setLiveTime(hydraskill->getHydraIdx(), TIMEMANAGER->getWorldTime() + 10);
					hydraskill->setHydraIdx(hydraskill->getHydraIdx() + 1);

					hydraskill->setHydraAngle(i, getAngle(
						hydraskill->getHydraInfo()[i]._hydrarc.left + (hydraskill->getHydraInfo()[i]._hydrarc.right - hydraskill->getHydraInfo()[i]._hydrarc.left) / 2 - _camera.x,
						hydraskill->getHydraInfo()[i]._hydrarc.top + (hydraskill->getHydraInfo()[i]._hydrarc.bottom - hydraskill->getHydraInfo()[i]._hydrarc.top) / 2 - _camera.y,
						dia->getX() - _camera.x, dia->getY() - _camera.y
					));
					
					AngleSet6(i, hydraskill->getHydraInfo()[i].hydraAngle * 180.0f / PI);
					AngleSet16(i, hydraskill->getHydraInfo()[i].hydraAngle * 180.0f / PI);
				}
			}
			break;

		case NAMEFROZENORB:
			if (!_player.isskill)
			{
				_player.mp -= 5;
				frozenorbskill->makeOrb(_player.x, _player.y,
					getAngle(_player.x - _camera.x + 10, _player.y - _camera.y + 20, _ptMouse.x, _ptMouse.y));
				SOUNDMANAGER->FindSound("ColdCast")->Play(0);
			}
			break;

		case NAMEMETEOR:
			if (!_player.isskill)
			{
				_player.mp -= 5;
				meteorskill->summonMeteor(_ptMouse.x, _ptMouse.y, _camera);
				SOUNDMANAGER->FindSound("FireCast")->Play(0);
			}
			break;

		case NAMETELEPORT:
			_player.mp -= 5;
			_player.endX = _ptMouse.x + _camera.x;
			_player.endY = _ptMouse.y + _camera.y;
			_player.x = _player.endX;
			_player.y = _player.endY;
			astar->setPlayerCoord(Point2D(_player.x, _player.y));
			
			SOUNDMANAGER->FindSound("Teleport")->Play(0);

			cameraUpdate();
			break;
		}
		_player.isskill = true;
		_player.iscasting = true;
	}

	for (int i = 0; i < hydraskill->getHydraInfo().size(); i++)
	{
		hydraskill->setHydraAngle(i, getAngle(
			hydraskill->getHydraInfo()[i]._hydrarc.left + (hydraskill->getHydraInfo()[i]._hydrarc.right - hydraskill->getHydraInfo()[i]._hydrarc.left) / 2 - _camera.x,
			hydraskill->getHydraInfo()[i]._hydrarc.top + (hydraskill->getHydraInfo()[i]._hydrarc.bottom - hydraskill->getHydraInfo()[i]._hydrarc.top) / 2 - _camera.y,
			dia->getX() - _camera.x, dia->getY() - _camera.y
		));
		AngleSet6(i, hydraskill->getHydraInfo()[i].hydraAngle * 180.0f / PI);
		AngleSet16(i, hydraskill->getHydraInfo()[i].hydraAngle * 180.0f / PI);
		if (hydraskill->getHydraInfo()[i].hydraSummon)
		{
			hydraskill->update(hydraskill->getHydraInfo()[i].hydraPos, i, _camera);
		}
	}

	frozenorbskill->update(_camera);
	meteorskill->update(_camera);

	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		_isShake = true;
	}
	if (_isShake)
	{
		CShake();
	}

	_player.hpCnt = _player.hp / (_player.maxHp / 20);
	_player.mpCnt = _player.mp / (_player.maxMp / 20);
}

void Player::render(bool isVillage)
{
	if (SHADOW_COUNT + _playerShadTick <= GetTickCount64())
	{
		_playerShadTick = GetTickCount64();
		_player.shadowIdx++;
		if (_player.shadowIdx > 16)
		{
			_player.shadowIdx = 0;
		}
	}
	if (!isVillage)
	{
		if (_player.ismove)
		{
			IMAGEMANAGER->frameRender("CombatWalkShadow", getMemDC(), _player.x - 60 - _camera.x, _player.y - 50 - _camera.y, _player.moveIdx, _player.direction);
			IMAGEMANAGER->frameRender("던전걷기", getMemDC(), _player.x - 30 - _camera.x, _player.y - 50 - _camera.y, _player.moveIdx, _player.direction);
			if (MOVE_COUNT + _playerMoveTick <= GetTickCount64())
			{
				_playerMoveTick = GetTickCount64();
				_player.moveIdx++;
				if (_player.moveIdx > 7) _player.moveIdx = 0;
			}
		}
		else
		{
			if (!_player.isskill)
			{
				IMAGEMANAGER->frameRender("CombatIdleShadow", getMemDC(), _player.x - 50 - _camera.x, _player.y - 50 - _camera.y, _player.moveIdx, _player.direction);
				IMAGEMANAGER->frameRender("던전대기", getMemDC(), _player.x - 30 - _camera.x, _player.y - 50 - _camera.y, _player.moveIdx, _player.direction);
				if (MOVE_COUNT + _playerMoveTick <= GetTickCount64())
				{
					_playerMoveTick = GetTickCount64();
					_player.moveIdx++;
					if (_player.moveIdx > 7) _player.moveIdx = 0;
				}
			}
			else
			{
				IMAGEMANAGER->frameRender("PlCastingShadow", getMemDC(), _player.x - 55 - _camera.x, _player.y - 50 - _camera.y, _player.skillIdx, _player.direction);
				IMAGEMANAGER->frameRender("캐스팅모션", getMemDC(), _player.x - 40 - _camera.x, _player.y - 50 - _camera.y, _player.skillIdx, _player.direction);
				if (CAST_COUNT + _playerMoveTick <= GetTickCount64())
				{
					_playerMoveTick = GetTickCount64();
					_player.skillIdx++;
					if (_player.skillIdx > 13)
					{
						_player.skillIdx = 0;
						_player.isskill = false;
					}
				}
			}
		}

		if (_player.iscasting)
		{
			IMAGEMANAGER->frameRender(_player.castingName, getMemDC(), _player.x - 50 - _camera.x, _player.y - 80 - _camera.y, _player.castingIdx, 0);
			if (CASTING_COUNT + _playerCastingTick <= GetTickCount64())
			{
				_playerCastingTick = GetTickCount64();
				_player.castingIdx++;
				if (_player.castingIdx > _player.maxcastIdx)
				{
					_player.castingIdx = 0;
					_player.iscasting = false;
				}
			}
		}

		for (int i = 0; i < hydraskill->getHydraInfo().size(); i++)
		{
			if (hydraskill->getHydraInfo()[i].hydraSummon)
			{
				hydraskill->render(hydraskill->getHydraInfo()[i].hydraPos, i, _camera);
			}
		}

		meteorskill->render(_camera);

		frozenorbskill->render(_camera);
		frozenorbskill->iceboltrender(_camera);
	}
	else
	{
		if (_player.ismove)
		{
			IMAGEMANAGER->frameRender("TownWalkShadow", getMemDC(), _player.x - 45 - _camera.x, _player.y - 40 - _camera.y, _player.moveIdx, _player.direction);
			IMAGEMANAGER->frameRender("마을걷기", getMemDC(), _player.x - 15 - _camera.x, _player.y - 40 - _camera.y, _player.moveIdx, _player.direction);
			if (MOVE_COUNT + _playerMoveTick <= GetTickCount64())
			{
				_playerMoveTick = GetTickCount64();
				_player.moveIdx++;
				if (_player.moveIdx > 7) _player.moveIdx = 0;
			}
		}
		else
		{
			IMAGEMANAGER->frameRender("PlIdleShadow", getMemDC(), _player.x - 45 - _camera.x, _player.y - 40 - _camera.y, _player.moveIdx, _player.direction);
			IMAGEMANAGER->frameRender("마을대기", getMemDC(), _player.x - 15 - _camera.x, _player.y - 40 - _camera.y, _player.moveIdx, _player.direction);
			if (MOVE_COUNT + _playerMoveTick <= GetTickCount64())
			{
				_playerMoveTick = GetTickCount64();
				_player.moveIdx++;
				if (_player.moveIdx > 15) _player.moveIdx = 0;
			}
		}
	}

}

//카메라
//=================================================================================
void Player::cameraUpdate(void)
{
	_camera.x = _player.x - WINSIZE_X / 2 + _cameraMoveD;
	_camera.y = _player.y - WINSIZE_Y / 2 + _cameraMoveY;

	if (_camera.x < 0)
		_camera.x = 0;
	else if (_camera.x >= 15000 - WINSIZE_X)
		_camera.x = 15000 - WINSIZE_X;

	if (_camera.y < 0)
		_camera.y = 0;
	else if (_camera.y >= 15000 - WINSIZE_Y)
		_camera.y = 15000 - WINSIZE_Y;
}

void Player::CShake(void)
{
	_currentShakeTime++;
	if (_currentShakeTime % 3 == 0)
	{
		_shakeTime++;
		switch (_shakeTime % 8)
		{
		case 1: case 4:
			_camera.x -= 16;
			_camera.y -= 16;

			break;
		case 2: case 3:
			_camera.x += 16;
			_camera.y += 16;

			break;

		case 0: case 5:
			_camera.x -= 16;
			_camera.y += 16;

			break;

		case 6: case 7:
			_camera.x += 16;
			_camera.y -= 16;

			break;
		}
	}

	if (_shakeTime == 96)
	{
		_shakeTime = 0;
		_isShake = false;
		_isDiaSummon = true;
		SOUNDMANAGER->FindSound("BossInit")->Play(0);
	}
}


void Player::CameraMoveUpdate(bool waypoint)
{
	if (waypoint)
	{
		if (SCENEMANAGER->getWAYP()->getIsWayPoint() && !_WayOpen)
		{
			_cameraMoveD -= 200.0f;
			_WayOpen = true;
		}
		else if (!SCENEMANAGER->getWAYP()->getIsWayPoint() && _WayOpen)
		{
			_cameraMoveD += 200.0f;
			_WayOpen = false;
		}
	}
	if (SCENEMANAGER->getInven()->getInvenActive() && !_invenOpen)
	{
		_cameraMoveD += 200.0f;
		_invenOpen = true;
	}
	else if (!SCENEMANAGER->getInven()->getInvenActive() && _invenOpen)
	{
		_cameraMoveD -= 200.0f;
		_invenOpen = false;
	}
	cameraUpdate();
	_player.rc = RectMakeCenter(_player.x - _camera.x, _player.y - _camera.y, 60, 90);
	_player.hitRC = RectMakeCenter(_player.x - _camera.x, _player.y - _camera.y, 20, 55);

	if (_invenOpen)
	{
		if ((0 < _ptMouse.x && _ptMouse.x < 400) && (0 < _ptMouse.y && _ptMouse.y < 800)) _isClickMove = true;
		else _isClickMove = false;
	}
	else _isClickMove = true;
}

//=================================================================================
void Player::AngleSet6(int idx, float angle)
{
	if (30 <= angle && angle < 90)  hydraskill->setHydraPos(idx, "히드라R2");
	else if (90 <= angle && angle < 150) hydraskill->setHydraPos(idx, "히드라L0");
	else if (150 <= angle && angle < 210) hydraskill->setHydraPos(idx, "히드라L1");
	else if (210 <= angle && angle < 270) hydraskill->setHydraPos(idx, "히드라L2");
	else if (270 <= angle && angle < 330) hydraskill->setHydraPos(idx, "히드라R0");
	else                                  hydraskill->setHydraPos(idx, "히드라R1");
}

void Player::AngleSet16(int idx, float angle)
{
	if (!hydraskill->getHydraInfo()[idx].bullet[hydraskill->getHydraInfo()[idx].bulletNum].fireDirect)
	{
		hydraskill->setHydraFireDirect(idx, hydraskill->getHydraInfo()[idx].bulletNum, true);

		if (12 <= angle && angle < 34)  hydraskill->setHydraFireName(idx, hydraskill->getHydraInfo()[idx].bulletNum, "파이어볼0");
		else if (34 <= angle && angle < 56)  hydraskill->setHydraFireName(idx, hydraskill->getHydraInfo()[idx].bulletNum, "파이어볼1");
		else if (56 <= angle && angle < 78)  hydraskill->setHydraFireName(idx, hydraskill->getHydraInfo()[idx].bulletNum, "파이어볼2");
		else if (78 <= angle && angle < 102) hydraskill->setHydraFireName(idx, hydraskill->getHydraInfo()[idx].bulletNum, "파이어볼3");
		else if (102 <= angle && angle < 124) hydraskill->setHydraFireName(idx, hydraskill->getHydraInfo()[idx].bulletNum, "파이어볼4");
		else if (124 <= angle && angle < 146) hydraskill->setHydraFireName(idx, hydraskill->getHydraInfo()[idx].bulletNum, "파이어볼5");
		else if (146 <= angle && angle < 168) hydraskill->setHydraFireName(idx, hydraskill->getHydraInfo()[idx].bulletNum, "파이어볼6");
		else if (168 <= angle && angle < 192) hydraskill->setHydraFireName(idx, hydraskill->getHydraInfo()[idx].bulletNum, "파이어볼7");
		else if (192 <= angle && angle < 214) hydraskill->setHydraFireName(idx, hydraskill->getHydraInfo()[idx].bulletNum, "파이어볼8");
		else if (214 <= angle && angle < 236) hydraskill->setHydraFireName(idx, hydraskill->getHydraInfo()[idx].bulletNum, "파이어볼9");
		else if (236 <= angle && angle < 258) hydraskill->setHydraFireName(idx, hydraskill->getHydraInfo()[idx].bulletNum, "파이어볼10");
		else if (258 <= angle && angle < 282) hydraskill->setHydraFireName(idx, hydraskill->getHydraInfo()[idx].bulletNum, "파이어볼11");
		else if (282 <= angle && angle < 304) hydraskill->setHydraFireName(idx, hydraskill->getHydraInfo()[idx].bulletNum, "파이어볼12");
		else if (304 <= angle && angle < 326) hydraskill->setHydraFireName(idx, hydraskill->getHydraInfo()[idx].bulletNum, "파이어볼13");
		else if (326 <= angle && angle < 348) hydraskill->setHydraFireName(idx, hydraskill->getHydraInfo()[idx].bulletNum, "파이어볼14");
		else                                  hydraskill->setHydraFireName(idx, hydraskill->getHydraInfo()[idx].bulletNum, "파이어볼15");

		hydraskill->setHydraFireAngle(idx, hydraskill->getHydraInfo()[idx].bulletNum, angle);
	}
}

void Player::PlayerAngleSet(float angle)
{
	if (12 <= angle && angle < 34)    _player.direction = 11;
	else if (34 <= angle && angle < 56)    _player.direction = 10;
	else if (56 <= angle && angle < 78)    _player.direction = 9;
	else if (78 <= angle && angle < 102)   _player.direction = 8;
	else if (102 <= angle && angle < 124)   _player.direction = 7;
	else if (124 <= angle && angle < 146)   _player.direction = 6;
	else if (146 <= angle && angle < 168)   _player.direction = 5;
	else if (168 <= angle && angle < 192)   _player.direction = 4;
	else if (192 <= angle && angle < 214)   _player.direction = 3;
	else if (214 <= angle && angle < 236)   _player.direction = 2;
	else if (236 <= angle && angle < 258)   _player.direction = 1;
	else if (258 <= angle && angle < 282)   _player.direction = 0;
	else if (282 <= angle && angle < 304)   _player.direction = 15;
	else if (304 <= angle && angle < 326)   _player.direction = 14;
	else if (326 <= angle && angle < 348)   _player.direction = 13;
	else                                    _player.direction = 12;
}

void Player::PlayerShadowAngSet(float angle)
{
	if (236 <= angle && angle < 282) _player.shaDirection = 5;
	else if (192 <= angle && angle < 236) _player.shaDirection = 6;
	else if (146 <= angle && angle < 192) _player.shaDirection = 7;
	else if (102 <= angle && angle < 146) _player.shaDirection = 8;
	else if (56 <= angle && angle < 102) _player.shaDirection = 0;
	else if (12 <= angle && angle < 56) _player.shaDirection = 1;
	else if (304 <= angle && angle < 348) _player.shaDirection = 3;
	else if (282 <= angle && angle < 304) _player.shaDirection = 4;
	else  _player.shaDirection = 2;
}