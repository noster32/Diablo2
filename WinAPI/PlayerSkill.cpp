#include "Stdafx.h"
#include "PlayerSkill.h"

#pragma region 아이템 이미지
HRESULT SKILLIMG::init()
{
	//히드라 본체
	IMAGEMANAGER->addFrameImage("히드라L0", "Resources/Images/Sorceress/hydra/hydraL0.bmp",
		0.0f, 0.0f, 168, 70, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("히드라L1", "Resources/Images/Sorceress/hydra/hydraL1.bmp",
		0.0f, 0.0f, 168, 70, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("히드라L2", "Resources/Images/Sorceress/hydra/hydraL2.bmp",
		0.0f, 0.0f, 168, 70, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("히드라R0", "Resources/Images/Sorceress/hydra/hydraR0.bmp",
		0.0f, 0.0f, 168, 70, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("히드라R1", "Resources/Images/Sorceress/hydra/hydraR1.bmp",
		0.0f, 0.0f, 168, 70, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("히드라R2", "Resources/Images/Sorceress/hydra/hydraR2.bmp",
		0.0f, 0.0f, 168, 70, 4, 1, true, RGB(255, 0, 255));

	//히드라 땅에서 불나오는거
	IMAGEMANAGER->addFrameImage("히드라땅불", "Resources/Images/Sorceress/hydra/hydrafire.bmp",
		0.0f, 0.0f, 350, 55, 5, 1, true, RGB(255, 0, 255));

	//파이어볼
	IMAGEMANAGER->addFrameImage("파이어볼0", "Resources/Images/Sorceress/fireball/fireball0.bmp",
		0.0f, 0.0f, 470, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파이어볼1", "Resources/Images/Sorceress/fireball/fireball1.bmp",
		0.0f, 0.0f, 470, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파이어볼2", "Resources/Images/Sorceress/fireball/fireball2.bmp",
		0.0f, 0.0f, 470, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파이어볼3", "Resources/Images/Sorceress/fireball/fireball3.bmp",
		0.0f, 0.0f, 470, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파이어볼4", "Resources/Images/Sorceress/fireball/fireball4.bmp",
		0.0f, 0.0f, 470, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파이어볼5", "Resources/Images/Sorceress/fireball/fireball5.bmp",
		0.0f, 0.0f, 470, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파이어볼6", "Resources/Images/Sorceress/fireball/fireball6.bmp",
		0.0f, 0.0f, 470, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파이어볼7", "Resources/Images/Sorceress/fireball/fireball7.bmp",
		0.0f, 0.0f, 470, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파이어볼8", "Resources/Images/Sorceress/fireball/fireball8.bmp",
		0.0f, 0.0f, 470, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파이어볼9", "Resources/Images/Sorceress/fireball/fireball9.bmp",
		0.0f, 0.0f, 470, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파이어볼10", "Resources/Images/Sorceress/fireball/fireball10.bmp",
		0.0f, 0.0f, 470, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파이어볼11", "Resources/Images/Sorceress/fireball/fireball11.bmp",
		0.0f, 0.0f, 470, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파이어볼12", "Resources/Images/Sorceress/fireball/fireball12.bmp",
		0.0f, 0.0f, 470, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파이어볼13", "Resources/Images/Sorceress/fireball/fireball13.bmp",
		0.0f, 0.0f, 470, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파이어볼14", "Resources/Images/Sorceress/fireball/fireball14.bmp",
		0.0f, 0.0f, 470, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파이어볼15", "Resources/Images/Sorceress/fireball/fireball15.bmp",
		0.0f, 0.0f, 470, 61, 5, 1, true, RGB(255, 0, 255));

	//프로즌 오브
	IMAGEMANAGER->addFrameImage("프로즌오브", "Resources/Images/Sorceress/icebolt/iceorb.bmp",
		0.0f, 0.0f, 64, 32, 2, 1, true, RGB(255, 0, 255));

	//아이스 볼트
	IMAGEMANAGER->addFrameImage("아이스볼트0", "Resources/Images/Sorceress/icebolt/icebolt_leftdown2.bmp",
		0.0f, 0.0f, 102, 38, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아이스볼트1", "Resources/Images/Sorceress/icebolt/icebolt_leftdown.bmp",
		0.0f, 0.0f, 174, 36, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아이스볼트2", "Resources/Images/Sorceress/icebolt/icebolt_leftdown0.bmp",
		0.0f, 0.0f, 228, 22, 6, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("아이스볼트3", "Resources/Images/Sorceress/icebolt/icebolt_left.bmp",
		0.0f, 0.0f, 420, 21, 6, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("아이스볼트4", "Resources/Images/Sorceress/icebolt/icebolt_leftup2.bmp",
		0.0f, 0.0f, 300, 11, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아이스볼트5", "Resources/Images/Sorceress/icebolt/icebolt_leftup.bmp",
		0.0f, 0.0f, 330, 28, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아이스볼트6", "Resources/Images/Sorceress/icebolt/icebolt_leftup0.bmp",
		0.0f, 0.0f, 222, 34, 6, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("아이스볼트7", "Resources/Images/Sorceress/icebolt/icebolt_up.bmp",
		0.0f, 0.0f, 108, 39, 6, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("아이스볼트8", "Resources/Images/Sorceress/icebolt/icebolt_rightup2.bmp",
		0.0f, 0.0f, 210, 34, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아이스볼트9", "Resources/Images/Sorceress/icebolt/icebolt_rightup.bmp",
		0.0f, 0.0f, 324, 34, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아이스볼트10", "Resources/Images/Sorceress/icebolt/icebolt_rightup0.bmp",
		0.0f, 0.0f, 288, 10, 6, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("아이스볼트11", "Resources/Images/Sorceress/icebolt/icebolt_right.bmp",
		0.0f, 0.0f, 420, 25, 6, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("아이스볼트12", "Resources/Images/Sorceress/icebolt/icebolt_rightdown2.bmp",
		0.0f, 0.0f, 306, 10, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아이스볼트13", "Resources/Images/Sorceress/icebolt/icebolt_rightdown.bmp",
		0.0f, 0.0f, 318, 29, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아이스볼트14", "Resources/Images/Sorceress/icebolt/icebolt_rightdown0.bmp",
		0.0f, 0.0f, 210, 39, 6, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("아이스볼트15", "Resources/Images/Sorceress/icebolt/icebolt_down.bmp",
		0.0f, 0.0f, 96, 37, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아이스볼트히트", "Resources/Images/Sorceress/icebolt/icebolthit.bmp",
		0.0f, 0.0f, 1020, 95, 17, 1, true, RGB(255, 0, 255));

	//메테오
	IMAGEMANAGER->addFrameImage("메테오", "Resources/Images/Sorceress/meteor/meteor.bmp",
		0.0f, 0.0f, 924, 125, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("메테오폭발", "Resources/Images/Sorceress/meteor/fireExplode.bmp",
		0.0f, 0.0f, 1300, 130, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("메테오타겟", "Resources/Images/Sorceress/meteor/meteorTarget.bmp",
		0.0f, 0.0f, 1904, 74, 17, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("메테오불", "Resources/Images/Sorceress/meteor/smallfire.bmp",
		0.0f, 0.0f, 1188, 89, 18, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("메테오불2", "Resources/Images/Sorceress/meteor/meteorfire.bmp",
		0.0f, 0.0f, 1080, 89, 18, 1, true, RGB(255, 0, 255));

	return S_OK;
}
#pragma endregion
//=================================================================
#pragma region 히드라
HRESULT HYDRA::init()
{
	_hydraTick = _hydraBulletTick = 7.0f;
	hydraIdx = 0;
	return S_OK;
}

void HYDRA::release(void)
{
}

void HYDRA::update(const char* imageName, int idx, Point2D camera)
{
	if (HYDRA_COUNT + _hydraTick <= GetTickCount64())
	{
		_hydraTick = GetTickCount64();
		IMAGEMANAGER->findImage(imageName)->setFrameX(IMAGEMANAGER->findImage(imageName)->getFrameX() + 1);
		if (IMAGEMANAGER->findImage(imageName)->getFrameX() >= IMAGEMANAGER->findImage(imageName)->getMaxFrameX())
		{
			//hydra[idx].hydrafirecnt--;
			IMAGEMANAGER->findImage(imageName)->setFrameX(0);
		}

		IMAGEMANAGER->findImage("히드라땅불")->setFrameX(IMAGEMANAGER->findImage("히드라땅불")->getFrameX() + 1);
		if (IMAGEMANAGER->findImage("히드라땅불")->getFrameX() >= IMAGEMANAGER->findImage("히드라땅불")->getMaxFrameX())
		{
			IMAGEMANAGER->findImage("히드라땅불")->setFrameX(0);
		}
	}
	move(idx, camera);

	if(hydra[idx].liveTime <= TIMEMANAGER->getWorldTime())
	{
		removeHydra(idx);
		hydraIdx--;
	}

}

void HYDRA::render(const char* imageName, int idx, Point2D camera)
{
	for (int i = 0; i < hydra.size(); i++)
	{
		IMAGEMANAGER->findImage(imageName)->frameRender(getMemDC(), hydra[idx]._hydrarc.left - camera.x, hydra[idx]._hydrarc.top - camera.y,
			IMAGEMANAGER->findImage(imageName)->getFrameX(),0);

		IMAGEMANAGER->findImage("히드라땅불")->frameRender(getMemDC(), hydra[idx]._hydrarc.left - 15 - camera.x, hydra[idx]._hydrarc.top + 30 - camera.y,
			IMAGEMANAGER->findImage("히드라땅불")->getFrameX(),0);

	}
	draw(idx, camera);
}

void HYDRA::setHydraPosition(int idx, float x, float y)
{

	hydra[idx]._x = x;
	hydra[idx]._y = y;
	hydra[idx].bulletNum = 0;

	hydra[idx]._hydrarc = RectMakeCenter(hydra[idx]._x, hydra[idx]._y, 28, 37);
	makebullet(idx);
}

void HYDRA::removeHydra(int arrNum)
{
	hydra.erase(hydra.begin() + arrNum);
}

void HYDRA::makebullet(int idx)
{
	for (int i = 0; i < 8; i++)
	{
		HydraBullet bullet;
		ZeroMemory(&bullet, sizeof(HydraBullet));

		bullet.speed = 4.0f;
		bullet.x = bullet.fireX = hydra[idx]._x;
		bullet.y = bullet.fireY = hydra[idx]._y;
		bullet.speedX = 3.0f;
		bullet.speedY = 3.0f;
		bullet.fire = false;
		bullet.hydrafirecnt = 1;
		bullet.bulletName = "파이어볼15";
		bullet.fireDirect = false;
		bullet.hit = false;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, 30, 20);

		hydra[idx].bullet.push_back(bullet);
	}
}

void HYDRA::fire(int idx, float x, float y)
{
	hydra[idx].bullet[hydra[idx].bulletNum].fire = true;
}

void HYDRA::draw(int idx, Point2D camera)
{
	IMAGEMANAGER->frameRender(hydra[idx].bullet[hydra[idx].bulletNum].bulletName,getMemDC(),
		hydra[idx].bullet[hydra[idx].bulletNum].x - 30 - camera.x, hydra[idx].bullet[hydra[idx].bulletNum].y - 30 - camera.y);
	
	if (FIREBALL_COUNT + _hydraBulletTick <= GetTickCount64() && hydra[idx].bullet[hydra[idx].bulletNum].fire)
	{
		_hydraBulletTick = GetTickCount64();
		IMAGEMANAGER->findImage(hydra[idx].bullet[hydra[idx].bulletNum].bulletName)->setFrameX(IMAGEMANAGER->findImage(hydra[idx].bullet[hydra[idx].bulletNum].bulletName)->getFrameX() + 1);
		if (IMAGEMANAGER->findImage(hydra[idx].bullet[hydra[idx].bulletNum].bulletName)->getFrameX() >= IMAGEMANAGER->findImage(hydra[idx].bullet[hydra[idx].bulletNum].bulletName)->getMaxFrameX())
		{
			IMAGEMANAGER->findImage(hydra[idx].bullet[hydra[idx].bulletNum].bulletName)->setFrameX(0);
		}
	}
}

void HYDRA::move(int idx, Point2D camera)
{
	hydra[idx].bullet[hydra[idx].bulletNum].x += cosf(hydra[idx].bullet[hydra[idx].bulletNum].angle * PI / 180.0f) * hydra[idx].bullet[hydra[idx].bulletNum].speedX;
	hydra[idx].bullet[hydra[idx].bulletNum].y += -sinf(hydra[idx].bullet[hydra[idx].bulletNum].angle * PI / 180.0f) * hydra[idx].bullet[hydra[idx].bulletNum].speedY;

	hydra[idx].bullet[hydra[idx].bulletNum].rc = RectMakeCenter(hydra[idx].bullet[hydra[idx].bulletNum].x + 10 - camera.x, hydra[idx].bullet[hydra[idx].bulletNum].y - camera.y, 30, 20);

	if (600 < getDistance(hydra[idx].bullet[hydra[idx].bulletNum].fireX - camera.x, hydra[idx].bullet[hydra[idx].bulletNum].fireY - camera.y, hydra[idx].bullet[hydra[idx].bulletNum].x - camera.x, hydra[idx].bullet[hydra[idx].bulletNum].y - camera.y) || hydra[idx].bullet[hydra[idx].bulletNum].hit)
	{
		hydra[idx].bullet[hydra[idx].bulletNum].fire = false;
		hydra[idx].bullet[hydra[idx].bulletNum].hydrafirecnt--;
		if (hydra[idx].bulletNum < 7) hydra[idx].bulletNum++;
	}
}
#pragma endregion
//=================================================================
#pragma region 프로즌오브
HRESULT FROZENORB::init()
{
	_iceBoltName[0] = "아이스볼트0";
	_iceBoltName[1] = "아이스볼트1";
	_iceBoltName[2] = "아이스볼트2";
	_iceBoltName[3] = "아이스볼트3";
	_iceBoltName[4] = "아이스볼트4";
	_iceBoltName[5] = "아이스볼트5";
	_iceBoltName[6] = "아이스볼트6";
	_iceBoltName[7] = "아이스볼트7";
	_iceBoltName[8] = "아이스볼트8";
	_iceBoltName[9] = "아이스볼트9";
	_iceBoltName[10] = "아이스볼트10";
	_iceBoltName[11] = "아이스볼트11";
	_iceBoltName[12] = "아이스볼트12";
	_iceBoltName[13] = "아이스볼트13";
	_iceBoltName[14] = "아이스볼트14";
	_iceBoltName[15] = "아이스볼트15";

	_iceboltAngle[0] = 247.5f;
	_iceboltAngle[1] = 225.0f;
	_iceboltAngle[2] = 202.5f;
	_iceboltAngle[3] = 180.0f;
	_iceboltAngle[4] = 157.5f;
	_iceboltAngle[5] = 135.0f;
	_iceboltAngle[6] = 112.5f;
	_iceboltAngle[7] = 90.0f;
	_iceboltAngle[8] = 67.5f;
	_iceboltAngle[9] = 45.0f;
	_iceboltAngle[10] = 22.5f;
	_iceboltAngle[11] = 0.0f;
	_iceboltAngle[12] = 337.5f;
	_iceboltAngle[13] = 315.0f;
	_iceboltAngle[14] = 292.5f;
	_iceboltAngle[15] = 270.0f;

	float r = 200.0f;
	_iceBoltRange[0] = r * 0.7;
	_iceBoltRange[1] = r * 0.8;
	_iceBoltRange[2] = r * 0.9;
	_iceBoltRange[3] = r;
	_iceBoltRange[4] = r * 0.9;
	_iceBoltRange[5] = r * 0.8;
	_iceBoltRange[6] = r * 0.7;
	_iceBoltRange[7] = r * 0.6;
	_iceBoltRange[8] = r * 0.7;
	_iceBoltRange[9] = r * 0.8;
	_iceBoltRange[10] = r * 0.9;
	_iceBoltRange[11] = r;
	_iceBoltRange[12] = r * 0.9;
	_iceBoltRange[13] = r * 0.8;
	_iceBoltRange[14] = r * 0.7;
	_iceBoltRange[15] = r * 0.6;

	_range = 470;
	_range = 564;
	_frozenOrbTick = _iceBoltTick = 0;

	return S_OK;
}

void FROZENORB::release(void)
{
}

void FROZENORB::update(Point2D camera)
{
	move(camera);
	icebolt(camera);
}

void FROZENORB::render(Point2D camera)
{
	draw(camera);
}

void FROZENORB::makeOrb(float x, float y, float angle)
{
	ORB orb;
	ZeroMemory(&orb, sizeof(ORB));

	orb.angle = angle;
	orb.x = orb.fireX = x;
	orb.y = orb.fireY = y;
	orb.iceboltFireIdx = 0; // 66;
	orb.iceboltIdx = 0;
	orb.orbIdx = 0;
	orb.rc = RectMakeCenter(x, y, 32, 32);

	_vfrozenOrb.push_back(orb);
}

void FROZENORB::draw(Point2D camera)
{
	for (_vifrozenOrb = _vfrozenOrb.begin(); _vifrozenOrb != _vfrozenOrb.end(); ++_vifrozenOrb)
	{
		IMAGEMANAGER->frameRender("프로즌오브", getMemDC(), _vifrozenOrb->x - camera.x, _vifrozenOrb->y - camera.y, _vifrozenOrb->orbIdx, 0);
		if (FROZENORB_COUNT + _frozenOrbTick <= GetTickCount64())
		{
			_frozenOrbTick = GetTickCount64();
			_vifrozenOrb->orbIdx++;
			if (_vifrozenOrb->orbIdx > 1) _vifrozenOrb->orbIdx = 0;
		}
	}
}

void FROZENORB::move(Point2D camera)
{
	for (_vifrozenOrb = _vfrozenOrb.begin(); _vifrozenOrb != _vfrozenOrb.end();)
	{
		_vifrozenOrb->x += cosf(_vifrozenOrb->angle) * 1.8;
		_vifrozenOrb->y += -sinf(_vifrozenOrb->angle) * 1.8;

		_vifrozenOrb->rc = RectMakeCenter(_vifrozenOrb->x - camera.x, _vifrozenOrb->y - camera.y, 16, 16);

		if (_vifrozenOrb->iceboltFireIdx % 10 == 1 && (1 <= _vifrozenOrb->iceboltFireIdx && _vifrozenOrb->iceboltFireIdx <= 71))
		{
			_iceBolt1.push_back({ RectMakeCenter(_vifrozenOrb->x - 5, _vifrozenOrb->y,10,10),
				_vifrozenOrb->x - 5, _vifrozenOrb->y,_vifrozenOrb->x - 5, _vifrozenOrb->y,
				_iceboltAngle[_vifrozenOrb->iceboltFireIdx - (8 * _vifrozenOrb->iceboltIdx)],
				3,_iceBoltRange[_vifrozenOrb->iceboltFireIdx - (8 * _vifrozenOrb->iceboltIdx)],false,_iceBoltName[_vifrozenOrb->iceboltFireIdx - (8 * _vifrozenOrb->iceboltIdx)],0,false });
			_vifrozenOrb->iceboltIdx++;
		}
		else if (_vifrozenOrb->iceboltFireIdx % 10 == 1 && (81 <= _vifrozenOrb->iceboltFireIdx && _vifrozenOrb->iceboltFireIdx <= 151))
		{
			_iceBolt1.push_back({ RectMakeCenter(_vifrozenOrb->x - 5, _vifrozenOrb->y,10,10),
				_vifrozenOrb->x - 5, _vifrozenOrb->y,_vifrozenOrb->x - 5, _vifrozenOrb->y,
				_iceboltAngle[_vifrozenOrb->iceboltFireIdx - (8 * _vifrozenOrb->iceboltIdx) - 16],
				3,_iceBoltRange[_vifrozenOrb->iceboltFireIdx - (8 * _vifrozenOrb->iceboltIdx) - 16],false,_iceBoltName[_vifrozenOrb->iceboltFireIdx - (8 * _vifrozenOrb->iceboltIdx) - 16],0, false });
			_vifrozenOrb->iceboltIdx++;

		}
		else if (_vifrozenOrb->iceboltFireIdx % 10 == 1 && (161 <= _vifrozenOrb->iceboltFireIdx && _vifrozenOrb->iceboltFireIdx <= 231))
		{
			_iceBolt1.push_back({ RectMakeCenter(_vifrozenOrb->x - 5, _vifrozenOrb->y,10,10),
				_vifrozenOrb->x - 5, _vifrozenOrb->y,_vifrozenOrb->x - 5, _vifrozenOrb->y,
				_iceboltAngle[_vifrozenOrb->iceboltFireIdx - (8 * _vifrozenOrb->iceboltIdx) - 32],
				3,_iceBoltRange[_vifrozenOrb->iceboltFireIdx - (8 * _vifrozenOrb->iceboltIdx) - 32],false,_iceBoltName[_vifrozenOrb->iceboltFireIdx - (8 * _vifrozenOrb->iceboltIdx) - 32],0, false });
			_vifrozenOrb->iceboltIdx++;
		}
		else if (_vifrozenOrb->iceboltFireIdx % 10 == 1 && (241 <= _vifrozenOrb->iceboltFireIdx && _vifrozenOrb->iceboltFireIdx <= 311))
		{
			_iceBolt1.push_back({ RectMakeCenter(_vifrozenOrb->x - 5, _vifrozenOrb->y,10,10),
				_vifrozenOrb->x - 5, _vifrozenOrb->y,_vifrozenOrb->x - 5, _vifrozenOrb->y,
				_iceboltAngle[_vifrozenOrb->iceboltFireIdx - (8 * _vifrozenOrb->iceboltIdx) - 48],
				3,_iceBoltRange[_vifrozenOrb->iceboltFireIdx - (8 * _vifrozenOrb->iceboltIdx) - 48],false,_iceBoltName[_vifrozenOrb->iceboltFireIdx - (8 * _vifrozenOrb->iceboltIdx) - 48],0, false });
			_vifrozenOrb->iceboltIdx++;
		}
		else if (312 == _vifrozenOrb->iceboltFireIdx)
		{
			for (int i = 0; i < 15; i++)
			{
				_iceBolt5.push_back({ RectMakeCenter(_vifrozenOrb->x - 5, _vifrozenOrb->y,10,10),
					_vifrozenOrb->x - 5, _vifrozenOrb->y,_vifrozenOrb->x - 5, _vifrozenOrb->y,
					_iceboltAngle[i],
					3,_iceBoltRange[i],false,_iceBoltName[i],0, false });
			}
		}

		_vifrozenOrb->iceboltFireIdx++;

		if (_range < getDistance(_vifrozenOrb->fireX, _vifrozenOrb->fireY, _vifrozenOrb->x, _vifrozenOrb->y))
		{
			SOUNDMANAGER->FindSound("FrozenOrbExplode")->Play(0);
			_vifrozenOrb = _vfrozenOrb.erase(_vifrozenOrb);
		}
		else _vifrozenOrb++;
	}
}

void FROZENORB::icebolt(Point2D camera)
{
	for (int i = 0; i < _iceBolt1.size();)
	{
		_iceBolt1[i].x += cosf(_iceBolt1[i].angle * PI / 180.0f) * 3;
		_iceBolt1[i].y += -sinf(_iceBolt1[i].angle * PI / 180.0f) * 1.5;

		_iceBolt1[i].rc = RectMakeCenter(_iceBolt1[i].x - camera.x , _iceBolt1[i].y - camera.y, 10, 10);
		if (_iceBolt1[i].range < getDistance(_iceBolt1[i].x - camera.x, _iceBolt1[i].y - camera.y, _iceBolt1[i].fireX - camera.x, _iceBolt1[i].fireY - camera.y) || _iceBolt1[i].hit)
		{
			_iceBolt1.erase(_iceBolt1.begin() + i);
		}
		else ++i;
	}

	for (int i = 0; i < _iceBolt5.size();)
	{
		_iceBolt5[i].x += cosf(_iceBolt5[i].angle * PI / 180.0f) * 3;
		_iceBolt5[i].y += -sinf(_iceBolt5[i].angle * PI / 180.0f) * 1.5;

		_iceBolt5[i].rc = RectMakeCenter(_iceBolt5[i].x - camera.x, _iceBolt5[i].y - camera.y, 10, 10);
		if (_iceBolt5[i].range < getDistance(_iceBolt5[i].x - camera.x, _iceBolt5[i].y - camera.y, _iceBolt5[i].fireX - camera.x, _iceBolt5[i].fireY - camera.y) || _iceBolt5[i].hit)
		{
			_iceBolt5.erase(_iceBolt5.begin() + i);
		}
		else ++i;
	}
}

void FROZENORB::iceboltrender(Point2D camera)
{
	for (int i = 0; i < _iceBolt1.size(); i++)
	{
		IMAGEMANAGER->frameRender(_iceBolt1[i].name, getMemDC(), _iceBolt1[i].x - camera.x, _iceBolt1[i].y - camera.y, _iceBolt1[i].index, 0);
		if (ICEBOLT_COUNT + _iceBoltTick <= GetTickCount64())
		{
			_iceBoltTick = GetTickCount64();
			_iceBolt1[i].index++;
			if (_iceBolt1[i].index > 5) _iceBolt1[i].index = 0;
		}
	}

	for (int i = 0; i < _iceBolt5.size(); i++)
	{
		IMAGEMANAGER->frameRender(_iceBolt5[i].name, getMemDC(), _iceBolt5[i].x - camera.x, _iceBolt5[i].y - camera.y, _iceBolt5[i].index, 0);
		if (ICEBOLT_COUNT + _iceBoltTick <= GetTickCount64())
		{
			_iceBoltTick = GetTickCount64();
			_iceBolt5[i].index++;
			if (_iceBolt5[i].index > 5) _iceBolt5[i].index = 0;
		}
	}
}

#pragma endregion
//=================================================================
#pragma region 메테오
HRESULT METEOR::init()
{
	return S_OK;
}

void METEOR::release(void)
{
}

void METEOR::update(Point2D camera)
{
	move(camera);
}

void METEOR::render(Point2D camera)
{
	draw(camera);
}

void METEOR::summonMeteor(float x, float y, Point2D camera)
{
	MeteorTarget target;
	ZeroMemory(&target, sizeof(MeteorTarget));

	target.MeteorTargetTick = 0;
	target.summonMeteorIdx = 0;
	target.idx = 0;
	target.x = x + camera.x;
	target.y = y + camera.y;
	target.onceSummon = false;

	_vMtarget.push_back(target);
}

void METEOR::draw(Point2D camera)
{
	for (_viMtarget = _vMtarget.begin(); _viMtarget != _vMtarget.end(); ++_viMtarget)
	{
		IMAGEMANAGER->frameRender("메테오타겟", getMemDC(), _viMtarget->x - 55 - camera.x, _viMtarget->y - 45 - camera.y, _viMtarget->idx, 0);
		if (MTARGET_COUNT + _viMtarget->MeteorTargetTick <= GetTickCount64())
		{
			_viMtarget->MeteorTargetTick = GetTickCount64();
			_viMtarget->idx++;
			if (_viMtarget->idx > 16)
			{
				_viMtarget->idx = 0;
				_viMtarget->summonMeteorIdx++;	
			}
		}
	}

	for (_viMeteor = _vMeteor.begin(); _viMeteor != _vMeteor.end(); ++_viMeteor)
	{
		if (!_viMeteor->explosion)
		{
			IMAGEMANAGER->frameRender("메테오", getMemDC(), _viMeteor->x - 25 - camera.x, _viMeteor->y - 110 - camera.y, _viMeteor->idx, 0);
			if (MTARGET_COUNT + _viMeteor->MeteorTick <= GetTickCount64())
			{
				_viMeteor->MeteorTick = GetTickCount64();
				_viMeteor->idx++;
				if (_viMeteor->idx > 11)
				{
					_viMeteor->idx = 0;
				}
			}
		}
	}

	for (_viExplosion = _vExplosion.begin(); _viExplosion != _vExplosion.end(); ++_viExplosion)
	{
		if (_viExplosion->isFire)
		{
			if (!_viExplosion->isFireEnd)
			{
				IMAGEMANAGER->frameRender("메테오불", getMemDC(), _viExplosion->x - 70 - camera.x, _viExplosion->y - 90 - camera.y, _viExplosion->fireidx, 0);
				IMAGEMANAGER->frameRender("메테오불", getMemDC(), _viExplosion->x - 70 - camera.x, _viExplosion->y - 50 - camera.y, _viExplosion->fireidx, 0);
				IMAGEMANAGER->frameRender("메테오불", getMemDC(), _viExplosion->x - 20 - camera.x, _viExplosion->y - 70 - camera.y, _viExplosion->fireidx, 0);
				IMAGEMANAGER->frameRender("메테오불", getMemDC(), _viExplosion->x + 30 - camera.x, _viExplosion->y - 90 - camera.y, _viExplosion->fireidx, 0);
				IMAGEMANAGER->frameRender("메테오불", getMemDC(), _viExplosion->x + 30 - camera.x, _viExplosion->y - 50 - camera.y, _viExplosion->fireidx, 0);
			}
			else
			{
				IMAGEMANAGER->frameRender("메테오불2", getMemDC(), _viExplosion->x - 70 - camera.x, _viExplosion->y - 90 - camera.y, _viExplosion->fireidx, 0);
				IMAGEMANAGER->frameRender("메테오불2", getMemDC(), _viExplosion->x - 70 - camera.x, _viExplosion->y - 50 - camera.y, _viExplosion->fireidx, 0);
				IMAGEMANAGER->frameRender("메테오불2", getMemDC(), _viExplosion->x - 20 - camera.x, _viExplosion->y - 70 - camera.y, _viExplosion->fireidx, 0);
				IMAGEMANAGER->frameRender("메테오불2", getMemDC(), _viExplosion->x + 30 - camera.x, _viExplosion->y - 90 - camera.y, _viExplosion->fireidx, 0);
				IMAGEMANAGER->frameRender("메테오불2", getMemDC(), _viExplosion->x + 30 - camera.x, _viExplosion->y - 50 - camera.y, _viExplosion->fireidx, 0);
			}
			if (MTFIRE_COUNT + _viExplosion->FireTick <= GetTickCount64())
			{
				_viExplosion->FireTick = GetTickCount64();
				_viExplosion->fireidx++;
				if (_viExplosion->fireidx > 17)
				{
					_viExplosion->fireidx = 0;
					_viExplosion->hitTime++;
				}
			}
		}
		if (_viExplosion->isExplosion)
		{
			IMAGEMANAGER->frameRender("메테오폭발", getMemDC(), _viExplosion->x - 100 - camera.x, _viExplosion->y - 90 - camera.y, _viExplosion->idx, 0);
			IMAGEMANAGER->frameRender("메테오폭발", getMemDC(), _viExplosion->x - 100 - camera.x, _viExplosion->y - 50 - camera.y, _viExplosion->idx, 0);
			IMAGEMANAGER->frameRender("메테오폭발", getMemDC(), _viExplosion->x - 50  - camera.x, _viExplosion->y - 70 - camera.y, _viExplosion->idx, 0);
			IMAGEMANAGER->frameRender("메테오폭발", getMemDC(), _viExplosion->x -  0  - camera.x, _viExplosion->y - 90 - camera.y, _viExplosion->idx, 0);
			IMAGEMANAGER->frameRender("메테오폭발", getMemDC(), _viExplosion->x -  0  - camera.x, _viExplosion->y - 50 - camera.y, _viExplosion->idx, 0);

			if (MTARGET_COUNT + _viExplosion->ExplosionTick <= GetTickCount64())
			{
				_viExplosion->ExplosionTick = GetTickCount64();
				_viExplosion->idx++;
				if (_viExplosion->idx > 11)
				{
					_viExplosion->idx = 0;
					_viExplosion->isExplosion = false;
				}
				if (_viExplosion->idx == 5) _viExplosion->isFire = true;
			}
		}
	}
}

void METEOR::move(Point2D camera)
{
	for (_viMtarget = _vMtarget.begin(); _viMtarget != _vMtarget.end();)
	{
		if (_viMtarget->summonMeteorIdx < 4)
		{
			if (_viMtarget->summonMeteorIdx == 3 && !_viMtarget->onceSummon)
			{
				_viMtarget->onceSummon = true;
				Meteor _meteor;
				ZeroMemory(&_meteor, sizeof(Meteor));

				_meteor.y = camera.y;
				_meteor.endY = _viMtarget->y;
				_meteor.x = _viMtarget->x - 60.0f;
				_meteor.speedY = 4.0f;
				_meteor.speedX = 60.0f / (_meteor.endY / 4.0f);
				_meteor.explosion = false;
				_meteor.idx = 0;
				_meteor.MeteorTick = 0;

				_vMeteor.push_back(_meteor);
			}
			++_viMtarget;
		}
		else
		{
			_viMtarget = _vMtarget.erase(_viMtarget);
		}
	}

	for (_viMeteor = _vMeteor.begin(); _viMeteor != _vMeteor.end();)
	{
		if (!_viMeteor->explosion)
		{
			_viMeteor->x += _viMeteor->speedX;
			_viMeteor->y += _viMeteor->speedY;

			if (_viMeteor->y >= _viMeteor->endY)
			{
				_viMeteor->explosion = true;
				SOUNDMANAGER->FindSound("MeteorImpact")->Play(0);
			}
			else ++_viMeteor;
		}
		else
		{
			MeteorExplosion _explosion;
			ZeroMemory(&_explosion, sizeof(MeteorExplosion));

			_explosion.x = _viMeteor->x;
			_explosion.y = _viMeteor->y;
			_explosion.hitTime = _explosion.idx = 0;
			_explosion.fireidx = _explosion.ExplosionTick = _explosion.FireTick = 0;
			_explosion.isExplosion = true;
			_explosion.isFire = _explosion.isFireEnd = false;
			_explosion.rc = RectMakeCenter(_viMeteor->x - camera.x + 20, _viMeteor->y - camera.y, 100, 50);

			_vExplosion.push_back(_explosion);

			_viMeteor = _vMeteor.erase(_viMeteor);
		}
	}

	for (_viExplosion = _vExplosion.begin(); _viExplosion != _vExplosion.end(); )
	{
		_viExplosion->rc = RectMakeCenter(_viExplosion->x - camera.x + 20, _viExplosion->y - camera.y, 100, 50);
		if (_viExplosion->hitTime == 9) _viExplosion->isFireEnd = true;
		if (_viExplosion->hitTime == 10) _viExplosion = _vExplosion.erase(_viExplosion);
		else ++_viExplosion;
	}
}
#pragma endregion
