#include "Stdafx.h"
#include "Boss.h"
#include "Player.h"

HRESULT Boss::init(void)
{
	SOUNDMANAGER->AddSound("RedHose", "Resources/Sounds/Boss/lightning.wav");
	SOUNDMANAGER->AddSound("BossDie", "Resources/Sounds/Boss/DiabloDead.wav")->SetVolume(100);
	SOUNDMANAGER->AddSound("BossInit", "Resources/Sounds/Boss/DiabloInit.wav");
	SOUNDMANAGER->AddSound("FireStorm", "Resources/Sounds/Boss/fireStorm.wav");
	SOUNDMANAGER->AddSound("FlameCircle", "Resources/Sounds/Boss/flameCircle.wav");
	SOUNDMANAGER->AddSound("Rush", "Resources/Sounds/Boss/attack.wav");
	SOUNDMANAGER->AddSound("FightBGM", "Resources/Sounds/Boss/fightbgm.wav")->SetVolume(70);
	SOUNDMANAGER->AddSound("AfterDie", "Resources/Sounds/Boss/afterDie.wav");

	_FlameCircle = new FlameCircle;
	_FlameCircle->init("flameCircle", 1000, 1000);
	_redLightningPJ = new RedHose;
	_redLightningPJ->init("LightningR", 500, 1000);
	_FireStorm = new FireStorm;
	_FireStorm->init("FireStormObj2", 400, 1300);

	_actionNum = IDLE;
	_direction = LD;
	_speed = 2.0f;
	_redHoseCount = 0;
	_x = 7840;
	_y = 3290;
	_fireStormDistance = 40;
	_actCount = 0;
	_hp = 10000;
	_maxHp = 10000;
	_isDead = false;

	temp = 0;

	return S_OK;
}

void Boss::release(void)
{
	_FlameCircle->release();
	SAFE_DELETE(_FlameCircle);
	_redLightningPJ->release();
	SAFE_DELETE(_redLightningPJ);
	_FireStorm->release();
	SAFE_DELETE(_FireStorm);
}

void Boss::update(Player* pl)
{
	if (_actionNum == IDLE && _count % 100 == 0 && !_fireStormOn)
	{
		_actionNum = RND->getFromIntTo(WALK, FIRESTORM);
		if (temp == _actionNum)
		{
			_actionNum = RND->getFromIntTo(WALK, FIRESTORM);
		}
		temp = _actionNum;
	}

	if (_isDead && _dieFrame == 150)
	{
		SOUNDMANAGER->FindSound("FightBGM")->Stop(0);
	}

	move(pl);

	_hpPercentage = _hp *100 / _maxHp;

	_FlameCircle->update();
	_redLightningPJ->update();
	_FireStorm->update();
}

void Boss::render(void)
{
	_FlameCircle->render();
	_FireStorm->render();

#pragma region ¸ð¼Ç ·»´õ
	if (_actionNum == IDLE)
	{
		switch (_direction)
		{
		case D:
			IMAGEMANAGER->frameRender("IdleD", getMemDC(), _rc.left - 120 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 50- SCENEMANAGER->getPLAYER()->getCamera().y, _frame, 0);
			break;
		case LD:
			IMAGEMANAGER->frameRender("IdleLD", getMemDC(), _rc.left - 130 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 65- SCENEMANAGER->getPLAYER()->getCamera().y, _frame, 0);
			break;
		case L:
			IMAGEMANAGER->frameRender("IdleL", getMemDC(), _rc.left - 140 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 70 - SCENEMANAGER->getPLAYER()->getCamera().y, _frame, 0);
			break;
		case LU:
			IMAGEMANAGER->frameRender("IdleLU", getMemDC(), _rc.left - 140 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 50-SCENEMANAGER->getPLAYER()->getCamera().y, _frame, 0);
			break;
		case U:
			IMAGEMANAGER->frameRender("IdleU", getMemDC(), _rc.left - 127 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 40- SCENEMANAGER->getPLAYER()->getCamera().y, _frame, 0);
			break;
		case RU:
			IMAGEMANAGER->frameRender("IdleRU", getMemDC(), _rc.left - 120 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 35- SCENEMANAGER->getPLAYER()->getCamera().y, _frame, 0);
			break;
		case R:
			IMAGEMANAGER->frameRender("IdleR", getMemDC(), _rc.left - 120 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 55- SCENEMANAGER->getPLAYER()->getCamera().y, _frame, 0);
			break;
		case RD:
			IMAGEMANAGER->frameRender("IdleRD", getMemDC(), _rc.left - 110 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 60- SCENEMANAGER->getPLAYER()->getCamera().y, _frame, 0);
			break;
		}
	}
	else if (_actionNum == DEAD) IMAGEMANAGER->frameRender("Dead", getMemDC(), _rc.left - 100 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 170 - SCENEMANAGER->getPLAYER()->getCamera().y, _dieFrame, 0);
	else if (_actionNum == WALK)
	{
		switch (_direction)
		{
		case D:
			IMAGEMANAGER->frameRender("WalkD", getMemDC(), _rc.left - 30 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 50 - SCENEMANAGER->getPLAYER()->getCamera().y, _frame, 0);
			break;
		case LD:
			IMAGEMANAGER->frameRender("WalkLD", getMemDC(), _rc.left - 50 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 50 - SCENEMANAGER->getPLAYER()->getCamera().y, _frame, 0);
			break;
		case L:
			IMAGEMANAGER->frameRender("WalkL", getMemDC(), _rc.left - 55 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 60 - SCENEMANAGER->getPLAYER()->getCamera().y, _frame, 0);
			break;
		case LU:
			IMAGEMANAGER->frameRender("WalkLU", getMemDC(), _rc.left - 60 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 50 - SCENEMANAGER->getPLAYER()->getCamera().y, _frame, 0);
			break;
		case U:
			IMAGEMANAGER->frameRender("WalkU", getMemDC(), _rc.left - 35 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 60 - SCENEMANAGER->getPLAYER()->getCamera().y, _frame, 0);
			break;
		case RU:
			IMAGEMANAGER->frameRender("WalkRU", getMemDC(), _rc.left - 120 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 50 - SCENEMANAGER->getPLAYER()->getCamera().y, _frame, 0);
			break;
		case R:
			IMAGEMANAGER->frameRender("WalkR", getMemDC(), _rc.left - 130 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 50 - SCENEMANAGER->getPLAYER()->getCamera().y, _frame, 0);
			break;
		case RD:
			IMAGEMANAGER->frameRender("WalkRD", getMemDC(), _rc.left - 60 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 60 - SCENEMANAGER->getPLAYER()->getCamera().y, _frame, 0);
			break;
		}
	}
	else if (_actionNum == RUSH)
	{
		switch (_direction)
		{
		case D:
			IMAGEMANAGER->frameRender("RushD", getMemDC(), _rc.left - 160 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 50 - SCENEMANAGER->getPLAYER()->getCamera().y, _rushFrame, 0);
			break;
		case LD:
			IMAGEMANAGER->frameRender("RushLD", getMemDC(), _rc.left - 160 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 60 - SCENEMANAGER->getPLAYER()->getCamera().y, _rushFrame, 0);
			break;
		case L:
			IMAGEMANAGER->frameRender("RushL", getMemDC(), _rc.left - 160 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 70 - SCENEMANAGER->getPLAYER()->getCamera().y, _rushFrame, 0);
			break;
		case LU:
			IMAGEMANAGER->frameRender("RushLU", getMemDC(), _rc.left - 170 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 80 - SCENEMANAGER->getPLAYER()->getCamera().y, _rushFrame, 0);
			break;
		case U:
			IMAGEMANAGER->frameRender("RushU", getMemDC(), _rc.left - 160 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 80 - SCENEMANAGER->getPLAYER()->getCamera().y, _rushFrame, 0);
			break;
		case RU:
			IMAGEMANAGER->frameRender("RushRU", getMemDC(), _rc.left - 140 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 70 - SCENEMANAGER->getPLAYER()->getCamera().y, _rushFrame, 0);
			break;
		case R:
			IMAGEMANAGER->frameRender("RushR", getMemDC(), _rc.left - 140 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 60 - SCENEMANAGER->getPLAYER()->getCamera().y, _rushFrame, 0);
			break;
		case RD:
			IMAGEMANAGER->frameRender("RushRD", getMemDC(), _rc.left - 130 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 60 - SCENEMANAGER->getPLAYER()->getCamera().y, _rushFrame, 0);
			break;
		}
	}
	else if (_actionNum == REDHOSE)
	{
		switch (_direction)
		{
		case D:
			IMAGEMANAGER->frameRender("RedHoseD", getMemDC(), _rc.left - 80 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 110 - SCENEMANAGER->getPLAYER()->getCamera().y, _redhoseFrame, 0);
			break;
		case LD:
			IMAGEMANAGER->frameRender("RedHoseLD", getMemDC(), _rc.left - 100 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 110 - SCENEMANAGER->getPLAYER()->getCamera().y, _redhoseFrame, 0);
			break;
		case L:
			IMAGEMANAGER->frameRender("RedHoseL", getMemDC(), _rc.left - 100 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 120 - SCENEMANAGER->getPLAYER()->getCamera().y, _redhoseFrame, 0);
			break;
		case LU:
			IMAGEMANAGER->frameRender("RedHoseLU", getMemDC(), _rc.left - 100 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 110 - SCENEMANAGER->getPLAYER()->getCamera().y, _redhoseFrame, 0);
			break;
		case U:
			IMAGEMANAGER->frameRender("RedHoseU", getMemDC(), _rc.left - 90 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 90 - SCENEMANAGER->getPLAYER()->getCamera().y, _redhoseFrame, 0);
			break;
		case RU:
			IMAGEMANAGER->frameRender("RedHoseRU", getMemDC(), _rc.left - 100 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 80 - SCENEMANAGER->getPLAYER()->getCamera().y, _redhoseFrame, 0);
			break;
		case R:
			IMAGEMANAGER->frameRender("RedHoseR", getMemDC(), _rc.left - 120 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 100 - SCENEMANAGER->getPLAYER()->getCamera().y, _redhoseFrame, 0);
			break;
		case RD:
			IMAGEMANAGER->frameRender("RedHoseRD", getMemDC(), _rc.left - 70 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 100 - SCENEMANAGER->getPLAYER()->getCamera().y, _redhoseFrame, 0);
			break;
		}
	}
	else if (_actionNum == FLAMECIRCLE)
	{
		switch (_direction)
		{
		case D:
			IMAGEMANAGER->frameRender("flameCircleD", getMemDC(), _rc.left - 127 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 66 - SCENEMANAGER->getPLAYER()->getCamera().y, _circleFrame, 0);
			break;
		case LD:
			IMAGEMANAGER->frameRender("flameCircleLD", getMemDC(), _rc.left - 137 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 60 - SCENEMANAGER->getPLAYER()->getCamera().y, _circleFrame, 0);
			break;
		case L:
			IMAGEMANAGER->frameRender("flameCircleL", getMemDC(), _rc.left - 146 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 74 - SCENEMANAGER->getPLAYER()->getCamera().y, _circleFrame, 0);
			break;
		case LU:
			IMAGEMANAGER->frameRender("flameCircleLU", getMemDC(), _rc.left - 147 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 58 - SCENEMANAGER->getPLAYER()->getCamera().y, _circleFrame, 0);
			break;
		case U:
			IMAGEMANAGER->frameRender("flameCircleU", getMemDC(), _rc.left - 134 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 60 - SCENEMANAGER->getPLAYER()->getCamera().y, _circleFrame, 0);
			break;
		case RU:
			IMAGEMANAGER->frameRender("flameCircleRU", getMemDC(), _rc.left - 125 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 57 - SCENEMANAGER->getPLAYER()->getCamera().y, _circleFrame, 0);
			break;
		case R:
			IMAGEMANAGER->frameRender("flameCircleR", getMemDC(), _rc.left - 125 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 65 - SCENEMANAGER->getPLAYER()->getCamera().y, _circleFrame, 0);
			break;
		case RD:
			IMAGEMANAGER->frameRender("flameCircleRD", getMemDC(), _rc.left - 116 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 70 - SCENEMANAGER->getPLAYER()->getCamera().y, _circleFrame, 0);
			break;
		}
	}
	else if (_actionNum == FIRESTORM)
	{
		switch (_direction)
		{
		case D:
			IMAGEMANAGER->frameRender("FireStormD", getMemDC(), _rc.left - 65 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 172 - SCENEMANAGER->getPLAYER()->getCamera().y, _fireStormFrame, 0);
			break;
		case LD:
			IMAGEMANAGER->frameRender("FireStormLD", getMemDC(), _rc.left - 82 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 167 - SCENEMANAGER->getPLAYER()->getCamera().y, _fireStormFrame, 0);
			break;
		case L:
			IMAGEMANAGER->frameRender("FireStormL", getMemDC(), _rc.left - 74 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 195 - SCENEMANAGER->getPLAYER()->getCamera().y, _fireStormFrame, 0);
			break;
		case LU:
			IMAGEMANAGER->frameRender("FireStormLU", getMemDC(), _rc.left - 90 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 168 - SCENEMANAGER->getPLAYER()->getCamera().y, _fireStormFrame, 0);
			break;
		case U:
			IMAGEMANAGER->frameRender("FireStormU", getMemDC(), _rc.left - 111 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 143 - SCENEMANAGER->getPLAYER()->getCamera().y, _fireStormFrame, 0);
			break;
		case RU:
			IMAGEMANAGER->frameRender("FireStormRU", getMemDC(), _rc.left - 86 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 180 - SCENEMANAGER->getPLAYER()->getCamera().y, _fireStormFrame, 0);
			break;
		case R:
			IMAGEMANAGER->frameRender("FireStormR", getMemDC(), _rc.left - 164 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 183 - SCENEMANAGER->getPLAYER()->getCamera().y, _fireStormFrame, 0);
			break;
		case RD:
			IMAGEMANAGER->frameRender("FireStormRD", getMemDC(), _rc.left - 89 - SCENEMANAGER->getPLAYER()->getCamera().x, _rc.top - 210 - SCENEMANAGER->getPLAYER()->getCamera().y, _fireStormFrame, 0);
			break;
		}
	}
#pragma endregion

	_redLightningPJ->render();

	IMAGEMANAGER->alphaRender("HpBarBG", getMemDC(), 345, 10, 0, 0, 128, 32, 200);
	IMAGEMANAGER->alphaRender("HpBar", getMemDC(), 345, 10, 0, 0, 128 * (_hpPercentage * 0.01), 32, 245);
	FONTMANAGER->drawText(getMemDC(), 364, 12, "kodia", 27, 10, "Diablo", 6, RGB(255, 255, 255));
}

void Boss::move(Player* pl)
{
	if (_hp <= 0) _actionNum = DEAD;

	_count++;
	_rc = RectMakeCenter(_x, _y, 100, 150);
	_hitBox = RectMakeCenter(_x - SCENEMANAGER->getPLAYER()->getCamera().x, _y - SCENEMANAGER->getPLAYER()->getCamera().y, 100, 150);
	
	if (_actionNum == IDLE)
	{
		if (_count % 6 == 0)
		{
			_actCount = 0;
			_frame++;
			if (_frame > 11) _frame = 0;
		}
	}
	else if (_actionNum == WALK)
	{
		if (_count % 6 == 0 && !_finishAction)
		{
			_frame++;
			if (_frame > 11)
			{
				_actCount++;
				_frame = 0;

				if (_actCount == 2) _actionNum = IDLE;
			}
		}

		_angle = getAngle(_x, _y, pl->getPlayerStat().x, pl->getPlayerStat().y);
		_x += cosf(_angle) * _speed * 0.8;
		_y += -sinf(_angle) * _speed * 0.8;

		if ((_angle > 337.5 * (PI / 180) && _angle < 360 * (PI / 180)) || (_angle < 22.5 * (PI / 180) && _angle > 0 * (PI / 180)))
		{
			_direction = R;
		}
		else if (_angle > 22.5 * (PI / 180) && _angle < 57.5 * (PI / 180))
		{
			_direction = RU;
		}
		else if (_angle > 57.5 * (PI / 180) && _angle < 122.5 * (PI / 180))
		{
			_direction = U;
		}
		else if (_angle > 122.5 * (PI / 180) && _angle < 157.5 * (PI / 180))
		{
			_direction = LU;
		}
		else if (_angle > 157.5 * (PI / 180) && _angle < 202.5 * (PI / 180))
		{
			_direction = L;
		}
		else if (_angle > 202.5 * (PI / 180) && _angle < 237.5 * (PI / 180))
		{
			_direction = LD;
		}
		else if (_angle > 237.5 * (PI / 180) && _angle < 302.5 * (PI / 180))
		{
			_direction = D;
		}
		else if (_angle > 302.5 * (PI / 180) && _angle < 337.5 * (PI / 180))
		{
			_direction = RD;
		}
	}
	else if (_actionNum == FLAMECIRCLE)
	{
		if (_count % 7 == 0)
		{
			_circleFrame++;
			if (_circleFrame == 4)	SOUNDMANAGER->FindSound("FlameCircle")->Play(0);
			if (_circleFrame == 9)
			{
				flameCircle(pl);
			}
			if (_circleFrame > 17)
			{
				_circleFrame = 0;
				_actionNum = IDLE;
			}
		}
	}
	else if (_actionNum == RUSH)
	{
		if (_count % 6 == 0)
		{
			_rushFrame++;
			if (_rushFrame == 14)	SOUNDMANAGER->FindSound("Rush")->Play(0);
			if (_rushFrame > 21)
			{
				_rushFrame = 0;
				_actionNum = IDLE;
			}
		}

		_angle = getAngle(_x, _y, pl->getPlayerStat().x, pl->getPlayerStat().y);
		_x += cosf(_angle) * _speed * 1.5;
		_y += -sinf(_angle) * _speed * 1.5;

		if ((_angle > 337.5 * (PI / 180) && _angle < 360 * (PI / 180)) || (_angle < 22.5 * (PI / 180) && _angle > 0 * (PI / 180)))
		{
			_direction = R;
		}
		else if (_angle > 22.5 * (PI / 180) && _angle < 57.5 * (PI / 180))
		{
			_direction = RU;
		}
		else if (_angle > 57.5 * (PI / 180) && _angle < 122.5 * (PI / 180))
		{
			_direction = U;
		}
		else if (_angle > 122.5 * (PI / 180) && _angle < 157.5 * (PI / 180))
		{
			_direction = LU;
		}
		else if (_angle > 157.5 * (PI / 180) && _angle < 202.5 * (PI / 180))
		{
			_direction = L;
		}
		else if (_angle > 202.5 * (PI / 180) && _angle < 237.5 * (PI / 180))
		{
			_direction = LD;
		}
		else if (_angle > 237.5 * (PI / 180) && _angle < 302.5 * (PI / 180))
		{
			_direction = D;
		}
		else if (_angle > 302.5 * (PI / 180) && _angle < 337.5 * (PI / 180))
		{
			_direction = RD;
		}
	}
	else if (_actionNum == REDHOSE)
	{
		if (_count % 6 == 0 && !_redHoseOn)
		{
			_redhoseFrame++;

			if (_redhoseFrame == 6)  SOUNDMANAGER->FindSound("RedHose")->Play(0);
			if (_redhoseFrame == 9 && !_redHoseOn)
			{
				_redHoseOn = true;
			}

			if (_redhoseFrame > 16) _actionNum = IDLE;
		}
		if (_redHoseOn)
		{
			_redhoseFrame = 9;

			if (_count % 12 == 0)
			{
				redHoseLightning(pl);
				_redHoseCount++;
				if (_redHoseCount > 17)
				{
					_redHoseOn = false;
					_redhoseFrame = 0;
					_redHoseCount = 0;
					_actionNum = IDLE;
				}
			}
		}

		_angle = getAngle(_x, _y, pl->getPlayerStat().x, pl->getPlayerStat().y);

		if ((_angle > 337.5 * (PI / 180) && _angle < 360 * (PI / 180)) || (_angle < 22.5 * (PI / 180) && _angle > 0 * (PI / 180)))
		{
			_direction = R;
		}
		else if (_angle > 22.5 * (PI / 180) && _angle < 57.5 * (PI / 180))
		{
			_direction = RU;
		}
		else if (_angle > 57.5 * (PI / 180) && _angle < 122.5 * (PI / 180))
		{
			_direction = U;
		}
		else if (_angle > 122.5 * (PI / 180) && _angle < 157.5 * (PI / 180))
		{
			_direction = LU;
		}
		else if (_angle > 157.5 * (PI / 180) && _angle < 202.5 * (PI / 180))
		{
			_direction = L;
		}
		else if (_angle > 202.5 * (PI / 180) && _angle < 237.5 * (PI / 180))
		{
			_direction = LD;
		}
		else if (_angle > 237.5 * (PI / 180) && _angle < 302.5 * (PI / 180))
		{
			_direction = D;
		}
		else if (_angle > 302.5 * (PI / 180) && _angle < 337.5 * (PI / 180))
		{
			_direction = RD;
		}
	}
	else if (_actionNum == DEAD)
	{
		if (!_isDead)
		{
			if (_dieFrame == 11)
			{
				SOUNDMANAGER->FindSound("BossDie")->Play(0);
				SOUNDMANAGER->FindSound("RedHose")->Stop(0);
				SOUNDMANAGER->FindSound("FireStorm")->Stop(0);
				SOUNDMANAGER->FindSound("FlameCircle")->Stop(0);
			}
			if (_count % 7 == 0)
			{
				_dieFrame++;
				if (_dieFrame > 150)
				{
					_dieFrame = 150;
					SOUNDMANAGER->FindSound("AfterDie")->Play(0);
					_isDead = true;
				}
			}
		}
	}
	else if (_actionNum == FIRESTORM)
	{
		if (_count % 6 == 0)
		{
			_fireStormFrame++;
			if (_fireStormFrame == 7)	SOUNDMANAGER->FindSound("FireStorm")->Play(0);
			if (_fireStormFrame == 9)
			{
				fireStorm(pl);
				_fireStormOn = true;
			}
			if (_fireStormFrame > 15)
			{
				_actionNum = IDLE;
			}
		}
	}

	if (_fireStormOn)
	{
		if (_fireStormCount >= 25)
		{
			_fireStormOn = false;
			_fireStormCount = 0;
			_fireStormDistance = 0;
			_fireStormFrame = 0;
		}

		if (_fireStormCount % 2 == 0)
		{
			_FireStorm->_angle += RND->getFromFloatTo(-4.0f, 4.0f) * (PI / 180.00f);
			_FireStorm->_angle2 += RND->getFromFloatTo(-2.0f, 2.0f) * (PI / 180.00f);
			_FireStorm->_angle3 += RND->getFromFloatTo(-4.0f, 4.0f) * (PI / 180.00f);
			_FireStorm->_angle4 += RND->getFromFloatTo(-2.0f, 2.0f) * (PI / 180.00f);
		}

		if (_count % 7 == 0 && _fireStormCount < 25)
		{
			_fireStormCount += 1;

			_FireStorm->fire(_FireStorm->_x + 20 + (cosf(_FireStorm->_angle) * _fireStormDistance), _FireStorm->_y + 110 + (-sinf(_FireStorm->_angle) * _fireStormDistance), 10, 4);
			_FireStorm->fire(_FireStorm->_x + 20 + (cosf(_FireStorm->_angle2) * _fireStormDistance), _FireStorm->_y + 110 + (-sinf(_FireStorm->_angle2) * _fireStormDistance), 10, 4);
			_FireStorm->fire(_FireStorm->_x + 20 + (cosf(_FireStorm->_angle3) * _fireStormDistance), _FireStorm->_y + 110 + (-sinf(_FireStorm->_angle3) * _fireStormDistance), 10, 4);
			_FireStorm->fire(_FireStorm->_x + 20 + (cosf(_FireStorm->_angle4) * _fireStormDistance), _FireStorm->_y + 110 + (-sinf(_FireStorm->_angle4) * _fireStormDistance), 10, 4);

			_fireStormDistance += 35;
		}
	}
}

void Boss::flameCircle(Player* pl)
{
	_FlameCircle->initFrame();

	_angle = getAngle(_x, _y, pl->getPlayerStat().x, pl->getPlayerStat().y);

	if ((_angle > 337.5 * (PI / 180) && _angle < 360 * (PI / 180)) || (_angle < 22.5 * (PI / 180) && _angle > 0 * (PI / 180)))
	{
		_direction = R;
	}
	else if (_angle > 22.5 * (PI / 180) && _angle < 57.5 * (PI / 180))
	{
		_direction = RU;
	}
	else if (_angle > 57.5 * (PI / 180) && _angle < 122.5 * (PI / 180))
	{
		_direction = U;
	}
	else if (_angle > 122.5 * (PI / 180) && _angle < 157.5 * (PI / 180))
	{
		_direction = LU;
	}
	else if (_angle > 157.5 * (PI / 180) && _angle < 202.5 * (PI / 180))
	{
		_direction = L;
	}
	else if (_angle > 202.5 * (PI / 180) && _angle < 237.5 * (PI / 180))
	{
		_direction = LD;
	}
	else if (_angle > 237.5 * (PI / 180) && _angle < 302.5 * (PI / 180))
	{
		_direction = D;
	}
	else if (_angle > 302.5 * (PI / 180) && _angle < 337.5 * (PI / 180))
	{
		_direction = RD;
	}

	RECT rc = _rc;

	for (int i = 0; i < 36; i++)
	{
		_FlameCircle->fire(rc.left + (rc.right - rc.left) / 2, rc.top + (rc.bottom - rc.top) / 2,
			(i * 10) * (PI / 180), 4);
	}
}

void Boss::redHoseLightning(Player* pl)
{

	RECT rc = _rc;

	_redLightningPJ->_angle = getAngle(_x, _y, pl->getPlayerStat().x, pl->getPlayerStat().y);

	if ((_redLightningPJ->_angle > 337.5 * (PI / 180) && _redLightningPJ->_angle < 360 * (PI / 180)) || (_redLightningPJ->_angle < 22.5 * (PI / 180) && _redLightningPJ->_angle > 0 * (PI / 180)))
	{
		_redLightningPJ->setImageName("LightningR");
		_redLightningPJ->fire(rc.left + (rc.right - rc.left) + 160 / 2, rc.top + (rc.bottom - rc.top) / 2 - 30,
			_redLightningPJ->_angle, 4);
	}
	else if (_redLightningPJ->_angle > 22.5 * (PI / 180) && _redLightningPJ->_angle < 57.5 * (PI / 180))
	{
		_redLightningPJ->setImageName("LightningRU");
		_redLightningPJ->fire(rc.left + (rc.right - rc.left) + 60 / 2, rc.top + (rc.bottom - rc.top) / 2 - 50,
			_redLightningPJ->_angle, 4);
	}
	else if (_redLightningPJ->_angle > 57.5 * (PI / 180) && _redLightningPJ->_angle < 122.5 * (PI / 180))
	{
		_redLightningPJ->setImageName("LightningU");
		_redLightningPJ->fire(rc.left + (rc.right - rc.left) / 2, rc.top + (rc.bottom - rc.top) / 2 - 110,
			_redLightningPJ->_angle, 4);
	}
	else if (_redLightningPJ->_angle > 122.5 * (PI / 180) && _redLightningPJ->_angle < 157.5 * (PI / 180))
	{
		_redLightningPJ->setImageName("LightningLU");
		_redLightningPJ->fire(rc.left + (rc.right - rc.left) / 2 - 110, rc.top + (rc.bottom - rc.top) / 2 - 100,
			_redLightningPJ->_angle, 4);
	}
	else if (_redLightningPJ->_angle > 157.5 * (PI / 180) && _redLightningPJ->_angle < 202.5 * (PI / 180))
	{
		_redLightningPJ->setImageName("LightningL");
		_redLightningPJ->fire(rc.left + (rc.right - rc.left) / 2 - 170, rc.top + (rc.bottom - rc.top) / 2 - 50,
			_redLightningPJ->_angle, 4);
	}
	else if (_redLightningPJ->_angle > 202.5 * (PI / 180) && _redLightningPJ->_angle < 237.5 * (PI / 180))
	{
		_redLightningPJ->setImageName("LightningLD");
		_redLightningPJ->fire(rc.left + (rc.right - rc.left) / 2 - 110, rc.top + (rc.bottom - rc.top) / 2 + 40,
			_redLightningPJ->_angle, 4);
	}
	else if (_redLightningPJ->_angle > 237.5 * (PI / 180) && _redLightningPJ->_angle < 302.5 * (PI / 180))
	{
		_redLightningPJ->setImageName("LightningD");
		_redLightningPJ->fire(rc.left + (rc.right - rc.left) / 2 - 10, rc.top + (rc.bottom - rc.top) / 2 + 40,
			_redLightningPJ->_angle, 4);
	}
	else if (_redLightningPJ->_angle > 302.5 * (PI / 180) && _redLightningPJ->_angle < 337.5 * (PI / 180))
	{
		_redLightningPJ->setImageName("LightningRD");
		_redLightningPJ->fire(rc.left + (rc.right - rc.left) / 2 + 100, rc.top + (rc.bottom - rc.top) / 2,
			_redLightningPJ->_angle, 4);
	}
}

void Boss::fireStorm(Player* pl)
{
	RECT rc = _rc;

	_FireStorm->_x = rc.left + (rc.right - rc.left) / 2;
	_FireStorm->_y = rc.top + (rc.bottom - rc.top) / 2;
	_FireStorm->_angle = getAngle(_FireStorm->_x, _FireStorm->_y, pl->getPlayerStat().x, pl->getPlayerStat().y);
	_FireStorm->_angle2 = _FireStorm->_angle + 10 * (PI / 180);
	_FireStorm->_angle3 = _FireStorm->_angle - 10 * (PI / 180);
	_FireStorm->_angle4 = _FireStorm->_angle - 15 * (PI / 180);

	if ((_FireStorm->_angle > 337.5 * (PI / 180) && _FireStorm->_angle < 360 * (PI / 180)) || (_FireStorm->_angle < 22.5 * (PI / 180) && _FireStorm->_angle > 0 * (PI / 180)))
	{
		_direction = R;
	}
	else if (_FireStorm->_angle > 22.5 * (PI / 180) && _FireStorm->_angle < 57.5 * (PI / 180))
	{
		_direction = RU;
	}
	else if (_FireStorm->_angle > 57.5 * (PI / 180) && _FireStorm->_angle < 122.5 * (PI / 180))
	{
		_direction = U;
	}
	else if (_FireStorm->_angle > 122.5 * (PI / 180) && _FireStorm->_angle < 157.5 * (PI / 180))
	{
		_direction = LU;
	}
	else if (_FireStorm->_angle > 157.5 * (PI / 180) && _FireStorm->_angle < 202.5 * (PI / 180))
	{
		_direction = L;
	}
	else if (_FireStorm->_angle > 202.5 * (PI / 180) && _FireStorm->_angle < 237.5 * (PI / 180))
	{
		_direction = LD;
	}
	else if (_FireStorm->_angle > 237.5 * (PI / 180) && _FireStorm->_angle < 302.5 * (PI / 180))
	{
		_direction = D;
	}
	else if (_FireStorm->_angle > 302.5 * (PI / 180) && _FireStorm->_angle < 337.5 * (PI / 180))
	{
		_direction = RD;
	}
}



