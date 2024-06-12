#include "Stdafx.h"
#include "MonsterImage.h"

HRESULT MonsterImage::balogInit()
{
	_balogIdle = IMAGEMANAGER->addImage("balog", "Resources/Images/Monster/balog/Balog_Idle.BMP", 2416, 1616, true, RGB(255, 0, 255));
	_balogIdleShadow = IMAGEMANAGER->addImage("balogS", "Resources/Images/Monster/balog/Balog_Idle_shadow.BMP", 2912, 2720, true, RGB(255, 0, 255));
	_balogMove = IMAGEMANAGER->addImage("balogM", "Resources/Images/Monster/balog/Balog_Walk.BMP", 2416, 1616, true, RGB(255, 0, 255));
	_balogMoveShadow = IMAGEMANAGER->addImage("balogMS", "Resources/Images/Monster/balog/Balog_Walk_shadow.BMP", 2912, 2720, true, RGB(255, 0, 255));
	_balogAttack = IMAGEMANAGER->addImage("balogA", "Resources/Images/Monster/balog/Balog_Attack.BMP", 4836, 1616, true, RGB(255, 0, 255));
	_balogAttackShadow = IMAGEMANAGER->addImage("balogAS", "Resources/Images/Monster/balog/Balog_Attack_shadow.BMP", 5824, 2720, true, RGB(255, 0, 255));
	_balogDied = IMAGEMANAGER->addImage("balogD", "Resources/Images/Monster/balog/Balog_Dying.BMP", 6040, 1616, true, RGB(255, 0, 255));
	_balogDiedShadow = IMAGEMANAGER->addImage("balogDS", "Resources/Images/Monster/balog/Balog_Dying_shadow.BMP", 7280, 2720, true, RGB(255, 0, 255));
	_balogGetHit = IMAGEMANAGER->addImage("balogGH", "Resources/Images/Monster/balog/Balog_Idle.BMP", 2416, 1616, true, RGB(255, 0, 255));
	_balogGetHitShadow = IMAGEMANAGER->addImage("balogGHS", "Resources/Images/Monster/balog/Balog_Idle.BMP", 2416, 1616, true, RGB(255, 0, 255));

	_balogIdleAnim = new Animation;
	_balogIdleAnim->init(_balogIdle->getWidth(), _balogIdle->getHeight(), 302, 202);
	_balogIdleAnim->setDefPlayFrame(false, true);
	_balogIdleAnim->setFPS(8);

	_balogIdleAnimShadow = new Animation;
	_balogIdleAnimShadow->init(_balogIdleShadow->getWidth(), _balogIdleShadow->getHeight(), 364, 340);
	_balogIdleAnimShadow->setDefPlayFrame(false, true);
	_balogIdleAnimShadow->setFPS(8);

	_balogMoveAnim = new Animation;
	_balogMoveAnim->init(_balogMove->getWidth(), _balogMove->getHeight(), 302, 202);
	_balogMoveAnim->setDefPlayFrame(false, true);
	_balogMoveAnim->setFPS(8);

	_balogMoveAnimShadow = new Animation;
	_balogMoveAnimShadow->init(_balogMoveShadow->getWidth(), _balogMoveShadow->getHeight(), 364, 340);
	_balogMoveAnimShadow->setDefPlayFrame(false, true);
	_balogMoveAnimShadow->setFPS(8);

	_balogAttackAnim = new Animation;
	_balogAttackAnim->init(_balogAttack->getWidth(), _balogAttack->getHeight(), 302, 202);
	_balogAttackAnim->setDefPlayFrame(false, true);
	_balogAttackAnim->setFPS(8);

	_balogAttackAnimShadow = new Animation;
	_balogAttackAnimShadow->init(_balogAttackShadow->getWidth(), _balogAttackShadow->getHeight(), 364, 340);
	_balogAttackAnimShadow->setDefPlayFrame(false, true);
	_balogAttackAnimShadow->setFPS(8);

	_balogDiedAnim = new Animation;
	_balogDiedAnim->init(_balogDied->getWidth(), _balogDied->getHeight(), 302, 202);
	_balogDiedAnim->setDefPlayFrame(false, false);
	_balogDiedAnim->setFPS(8);

	_balogDiedAnimShadow = new Animation;
	_balogDiedAnimShadow->init(_balogDiedShadow->getWidth(), _balogDiedShadow->getHeight(), 364, 340);
	_balogDiedAnimShadow->setDefPlayFrame(false, false);
	_balogDiedAnimShadow->setFPS(8);
	_balogIdleAnim->aniStart();
	_balogIdleAnimShadow->aniStart();
	_balogMoveAnim->aniStart();
	_balogMoveAnimShadow->aniStart();
	_balogAttackAnim->aniStart();
	_balogAttackAnimShadow->aniStart();
	_balogDiedAnim->aniStart();
	_balogDiedAnimShadow->aniStart();

	return S_OK;
}

void MonsterImage::balogRelease(void)
{
	_balogIdleAnim->release();
	SAFE_DELETE(_balogIdleAnim);
	_balogIdleAnimShadow->release();
	SAFE_DELETE(_balogIdleAnimShadow);
	_balogMoveAnim->release();
	SAFE_DELETE(_balogMoveAnim);
	_balogMoveAnimShadow->release();
	SAFE_DELETE(_balogMoveAnimShadow);
	_balogAttackAnim->release();
	SAFE_DELETE(_balogAttackAnim);
	_balogAttackAnimShadow->release();
	SAFE_DELETE(_balogAttackAnimShadow);
	_balogDiedAnim->release();
	SAFE_DELETE(_balogDiedAnim);
	_balogDiedAnimShadow->release();
	SAFE_DELETE(_balogDiedAnimShadow);
}

void MonsterImage::balogUpdate(int animAngle, int state)
{
	if (animAngle == 0 && state == 0)
	{
		_balogIdleAnim->setPlayFrame(0, 8, false, true);
		_balogIdleAnimShadow->setPlayFrame(0, 8, false, true);

		_balogIdleAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogIdleAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 0 && state == 1)
	{
		_balogMoveAnim->setPlayFrame(0, 8, false, true);
		_balogMoveAnimShadow->setPlayFrame(0, 8, false, true);

		_balogMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogMoveAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 0 && state == 2)
	{
		_balogAttackAnim->setPlayFrame(0, 16, false, true);
		_balogAttackAnimShadow->setPlayFrame(0, 16, false, true);

		_balogAttackAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogAttackAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 0 && state == 3)
	{
		_balogDiedAnim->setPlayFrame(0, 20, false, false);
		_balogDiedAnimShadow->setPlayFrame(0, 20, false, false);

		_balogDiedAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogDiedAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 0 && state == 4)
	{

	}
	else if (animAngle == 1 && state == 0)
	{
		_balogIdleAnim->setPlayFrame(8, 16, false, true);
		_balogIdleAnimShadow->setPlayFrame(8, 16, false, true);

		_balogIdleAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogIdleAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	}
	else if (animAngle == 1 && state == 1)
	{
		_balogMoveAnim->setPlayFrame(8, 16, false, true);
		_balogMoveAnimShadow->setPlayFrame(8, 16, false, true);

		_balogMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogMoveAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 1 && state == 2)
	{
		_balogAttackAnim->setPlayFrame(16, 32, false, true);
		_balogAttackAnimShadow->setPlayFrame(16, 32, false, true);

		_balogAttackAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogAttackAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 1 && state == 3)
	{
		_balogDiedAnim->setPlayFrame(20, 40, false, false);
		_balogDiedAnimShadow->setPlayFrame(20, 40, false, false);

		_balogDiedAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogDiedAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 1 && state == 4)
	{

	}
	else if (animAngle == 2 && state == 0)
	{
		_balogIdleAnim->setPlayFrame(16, 24, false, true);
		_balogIdleAnimShadow->setPlayFrame(16, 24, false, true);

		_balogIdleAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogIdleAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	}
	else if (animAngle == 2 && state == 1)
	{
		_balogMoveAnim->setPlayFrame(16, 24, false, true);
		_balogMoveAnimShadow->setPlayFrame(16, 24, false, true);

		_balogMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogMoveAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 2 && state == 2)
	{
		_balogAttackAnim->setPlayFrame(32, 48, false, true);
		_balogAttackAnimShadow->setPlayFrame(32, 48, false, true);

		_balogAttackAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogAttackAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 2 && state == 3)
	{
		_balogDiedAnim->setPlayFrame(40, 60, false, false);
		_balogDiedAnimShadow->setPlayFrame(40, 60, false, false);

		_balogDiedAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogDiedAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 2 && state == 4)
	{

	}
	else if (animAngle == 3 && state == 0)
	{
		_balogIdleAnim->setPlayFrame(24, 32, false, true);
		_balogIdleAnimShadow->setPlayFrame(24, 32, false, true);

		_balogIdleAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogIdleAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	}
	else if (animAngle == 3 && state == 1)
	{
		_balogMoveAnim->setPlayFrame(24, 32, false, true);
		_balogMoveAnimShadow->setPlayFrame(24, 32, false, true);

		_balogMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogMoveAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 3 && state == 2)
	{
		_balogAttackAnim->setPlayFrame(48, 64, false, true);
		_balogAttackAnimShadow->setPlayFrame(48, 64, false, true);

		_balogAttackAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogAttackAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 3 && state == 3)
	{
		_balogDiedAnim->setPlayFrame(60, 80, false, false);
		_balogDiedAnimShadow->setPlayFrame(60, 80, false, false);

		_balogDiedAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogDiedAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 3 && state == 4)
	{

	}
	else if (animAngle == 4 && state == 0)
	{
		_balogIdleAnim->setPlayFrame(32, 40, false, true);
		_balogIdleAnimShadow->setPlayFrame(32, 40, false, true);

		_balogIdleAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogIdleAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	}
	else if (animAngle == 4 && state == 1)
	{
		_balogMoveAnim->setPlayFrame(32, 40, false, true);
		_balogMoveAnimShadow->setPlayFrame(32, 40, false, true);

		_balogMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogMoveAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 4 && state == 2)
	{
		_balogAttackAnim->setPlayFrame(64, 80, false, true);
		_balogAttackAnimShadow->setPlayFrame(64, 80, false, true);

		_balogAttackAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogAttackAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 4 && state == 3)
	{
		_balogDiedAnim->setPlayFrame(80, 100, false, false);
		_balogDiedAnimShadow->setPlayFrame(80, 100, false, false);

		_balogDiedAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogDiedAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 4 && state == 4)
	{

	}
	else if (animAngle == 5 && state == 0)
	{
		_balogIdleAnim->setPlayFrame(40, 48, false, true);
		_balogIdleAnimShadow->setPlayFrame(40, 48, false, true);

		_balogIdleAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogIdleAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	}
	else if (animAngle == 5 && state == 1)
	{
		_balogMoveAnim->setPlayFrame(40, 48, false, true);
		_balogMoveAnimShadow->setPlayFrame(40, 48, false, true);

		_balogMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogMoveAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 5 && state == 2)
	{
		_balogAttackAnim->setPlayFrame(80, 96, false, true);
		_balogAttackAnimShadow->setPlayFrame(80, 96, false, true);

		_balogAttackAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogAttackAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 5 && state == 3)
	{
		_balogDiedAnim->setPlayFrame(100, 120, false, false);
		_balogDiedAnimShadow->setPlayFrame(100, 120, false, false);

		_balogDiedAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogDiedAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 5 && state == 4)
	{

	}
	else if (animAngle == 6 && state == 0)
	{
		_balogIdleAnim->setPlayFrame(48, 56, false, true);
		_balogIdleAnimShadow->setPlayFrame(48, 56, false, true);

		_balogIdleAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogIdleAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	}
	else if (animAngle == 6 && state == 1)
	{
		_balogMoveAnim->setPlayFrame(48, 56, false, true);
		_balogMoveAnimShadow->setPlayFrame(48, 56, false, true);

		_balogMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogMoveAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 6 && state == 2)
	{
		_balogAttackAnim->setPlayFrame(96, 112, false, true);
		_balogAttackAnimShadow->setPlayFrame(96, 112, false, true);

		_balogAttackAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogAttackAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 6 && state == 3)
	{
		_balogDiedAnim->setPlayFrame(120, 140, false, false);
		_balogDiedAnimShadow->setPlayFrame(120, 140, false, false);

		_balogDiedAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogDiedAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 6 && state == 4)
	{

	}
	else if (animAngle == 7 && state == 0)
	{
		_balogIdleAnim->setPlayFrame(56, 64, false, true);
		_balogIdleAnimShadow->setPlayFrame(56, 64, false, true);

		_balogIdleAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogIdleAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	}
	else if (animAngle == 7 && state == 1)
	{
		_balogMoveAnim->setPlayFrame(56, 64, false, true);
		_balogMoveAnimShadow->setPlayFrame(56, 64, false, true);

		_balogMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogMoveAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 7 && state == 2)
	{
		_balogAttackAnim->setPlayFrame(112, 128, false, true);
		_balogAttackAnimShadow->setPlayFrame(112, 128, false, true);

		_balogAttackAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogAttackAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 7 && state == 3)
	{
		_balogDiedAnim->setPlayFrame(140, 160, false, false);
		_balogDiedAnimShadow->setPlayFrame(140, 160, false, false);

		_balogDiedAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_balogDiedAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 7 && state == 4)
	{

	}
}

void MonsterImage::balogAnim(HDC hdc, int LocationX, int LocationY, int sta)
{
	switch (sta)
	{
	case 0:
		balogIdle(hdc, LocationX, LocationY);
		break;
	case 1:
		balogMove(hdc, LocationX, LocationY);
		break;
	case 2:
		balogAttack(hdc, LocationX, LocationY);
		break;
	case 3:
		balogDied(hdc, LocationX, LocationY);
		break;
	case 4:
		break;
	default:
		break;
	}

	
	
}

void MonsterImage::balogIdle(HDC hdc, int LocationX, int LocationY)
{
	_balogIdleShadow->aniRender(hdc, LocationX - 60, LocationY - 70, _balogIdleAnimShadow);
	_balogIdle->aniRender(hdc, LocationX, LocationY, _balogIdleAnim);
}

void MonsterImage::balogMove(HDC hdc, int LocationX, int LocationY)
{
	_balogMoveShadow->aniRender(hdc, LocationX - 60, LocationY - 70, _balogMoveAnimShadow);
	_balogMove->aniRender(hdc, LocationX, LocationY, _balogMoveAnim);
}

void MonsterImage::balogAttack(HDC hdc, int LocationX, int LocationY)
{
	_balogAttackShadow->aniRender(hdc, LocationX - 60, LocationY - 70, _balogAttackAnimShadow);
	_balogAttack->aniRender(hdc, LocationX, LocationY, _balogAttackAnim);
}

void MonsterImage::balogDied(HDC hdc, int LocationX, int LocationY)
{
	_balogDiedShadow->aniRender(hdc, LocationX - 60, LocationY - 70, _balogDiedAnimShadow);
	_balogDied->aniRender(hdc, LocationX, LocationY, _balogDiedAnim); 
}

void MonsterImage::balogGetHit(HDC hdc, int LocationX, int LocationY)
{
}


HRESULT MonsterImage::orgeInit(void)
{
	_orge = IMAGEMANAGER->addImage("orge", "Resources/Images/Monster/ogre/Ogre_Idle.BMP", 1064, 1040, true, RGB(255, 0, 255));
	_orgeShadow = IMAGEMANAGER->addImage("orgeS", "Resources/Images/Monster/ogre/Ogre_Idle_shadow.BMP", 1464, 1472, true, RGB(255, 0, 255));

	_orgeMove = IMAGEMANAGER->addImage("orgeM", "Resources/Images/Monster/ogre/Ogre_Walk.BMP", 1256, 1128, true, RGB(255, 0, 255));
	_orgeMoveShadow = IMAGEMANAGER->addImage("ogreMS", "Resources/Images/Monster/ogre/Ogre_Walk_shadow.BMP", 1672, 1656, true, RGB(255, 0, 255));

	_orgeAttack = IMAGEMANAGER->addImage("ogreA", "Resources/Images/Monster/ogre/Ogre_Attack.BMP", 3300, 1728, true, RGB(255, 0, 255));
	_orgeAttackShadow = IMAGEMANAGER->addImage("ogreAS", "Resources/Images/Monster/ogre/Ogre_Attack_shadow.BMP", 4560, 2440, true, RGB(255, 0, 255));

	_orgeDied = IMAGEMANAGER->addImage("ogreD", "Resources/Images/Monster/ogre/Ogre_Dying.BMP", 7475, 1648, true, RGB(255, 0, 255));
	_orgeDiedShadow = IMAGEMANAGER->addImage("ogreDS", "Resources/Images/Monster/ogre/Ogre_Dying_shadow.BMP", 8855, 2848, true, RGB(255, 0, 255));

	_orgeGetHit = IMAGEMANAGER->addImage("ogreGH", "Resources/Images/Monster/ogre/Ogre_GetHit.BMP", 1239, 1304, true, RGB(255, 0, 255));
	_orgeGetHitShadow = IMAGEMANAGER->addImage("ogreGHS", "Resources/Images/Monster/ogre/Ogre_GetHit_shadow.BMP", 1673, 1896, true, RGB(255, 0, 255));


	_orgeAnim = new Animation;
	_orgeAnim->init(_orge->getWidth(), _orge->getHeight(), 133, 130);
	_orgeAnim->setDefPlayFrame(false, true);
	_orgeAnim->setFPS(8);

	_orgeAnimShadow = new Animation;
	_orgeAnimShadow->init(_orgeShadow->getWidth(), _orgeShadow->getHeight(), 183, 184);
	_orgeAnimShadow->setDefPlayFrame(false, true);
	_orgeAnimShadow->setFPS(8);

	_ogreMoveAnim = new Animation;
	_ogreMoveAnim->init(_orgeMove->getWidth(), _orgeMove->getHeight(), 157, 141);
	_ogreMoveAnim->setDefPlayFrame(false, true);
	_ogreMoveAnim->setFPS(8);

	_ogreMoveAnimShadow = new Animation;
	_ogreMoveAnimShadow->init(_orgeMoveShadow->getWidth(), _orgeMoveShadow->getHeight(), 209, 207);
	_ogreMoveAnimShadow->setDefPlayFrame(false, true);
	_ogreMoveAnimShadow->setFPS(8);

	_ogreAttackAnim = new Animation;
	_ogreAttackAnim->init(_orgeAttack->getWidth(), _orgeAttack->getHeight(), 220, 216);
	_ogreAttackAnim->setDefPlayFrame(false, true);
	_ogreAttackAnim->setFPS(8);

	_ogreAttackAnimShadow = new Animation;
	_ogreAttackAnimShadow->init(_orgeAttackShadow->getWidth(), _orgeAttackShadow->getHeight(), 304, 305);
	_ogreAttackAnimShadow->setDefPlayFrame(false, true);
	_ogreAttackAnimShadow->setFPS(8);

	_ogreDiedAnim = new Animation;
	_ogreDiedAnim->init(_orgeDied->getWidth(), _orgeDied->getHeight(), 325, 206);
	_ogreDiedAnim->setDefPlayFrame(false, false);
	_ogreDiedAnim->setFPS(8);

	_ogreDiedAnimShadow = new Animation;
	_ogreDiedAnimShadow->init(_orgeDiedShadow->getWidth(), _orgeDiedShadow->getHeight(), 385, 356);
	_ogreDiedAnimShadow->setDefPlayFrame(false, false);
	_ogreDiedAnimShadow->setFPS(8);
	
	_orgeAnim->aniStart();
	_orgeAnimShadow->aniStart();
	_ogreMoveAnim->aniStart();
	_ogreMoveAnimShadow->aniStart();
	_ogreAttackAnim->aniStart();
	_ogreAttackAnimShadow->aniStart();
	_ogreDiedAnim->aniStart();
	_ogreDiedAnimShadow->aniStart();


	return S_OK;
}

void MonsterImage::ogreRelease(void)
{
	_orgeAnim->release();
	SAFE_DELETE(_orgeAnim);
	_orgeAnimShadow->release();
	SAFE_DELETE(_orgeAnimShadow);
	_ogreMoveAnim->release();
	SAFE_DELETE(_ogreMoveAnim);
	_ogreMoveAnimShadow->release();
	SAFE_DELETE(_ogreMoveAnimShadow);
	_ogreAttackAnim->release();
	SAFE_DELETE(_ogreAttackAnim);
	_ogreAttackAnimShadow->release();
	SAFE_DELETE(_ogreAttackAnimShadow);
	_ogreDiedAnim->release();
	SAFE_DELETE(_ogreDiedAnim);
	_ogreDiedAnimShadow->release();
	SAFE_DELETE(_ogreDiedAnimShadow);
}

void MonsterImage::orgeUpdate(int animAngle, int state)
{	
	if (animAngle == 0 && state == 0)
	{
		_orgeAnim->setPlayFrame(0, 8, false, true);
		_orgeAnimShadow->setPlayFrame(0, 8, false, true);

		_orgeAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_orgeAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 0 && state == 1)
	{
		_ogreMoveAnim->setPlayFrame(0, 8, false, true);
		_ogreMoveAnimShadow->setPlayFrame(0, 8, false, true);

		_ogreMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreMoveAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 0 && state == 2)
	{
		_ogreAttackAnim->setPlayFrame(0, 15, false, true);
		_ogreAttackAnimShadow->setPlayFrame(0, 15, false, true);

		_ogreAttackAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreAttackAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 0 && state == 3)
	{
		_ogreDiedAnim->setPlayFrame(0, 23, false, false);
		_ogreDiedAnimShadow->setPlayFrame(0, 23, false, false);

		_ogreDiedAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreDiedAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 0 && state == 4)
	{
		
	}
	else if (animAngle == 1 && state == 0)
	{
		_orgeAnim->setPlayFrame(8, 16, false, true);
		_orgeAnimShadow->setPlayFrame(8, 16, false, true);

		_orgeAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_orgeAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	}
	else if (animAngle == 1 && state == 1)
	{
		_ogreMoveAnim->setPlayFrame(8, 16, false, true);
		_ogreMoveAnimShadow->setPlayFrame(8, 16, false, true);

		_ogreMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreMoveAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 1 && state == 2)
	{
		_ogreAttackAnim->setPlayFrame(15, 30, false, true);
		_ogreAttackAnimShadow->setPlayFrame(15, 30, false, true);

		_ogreAttackAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreAttackAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 1 && state == 3)
	{
		_ogreDiedAnim->setPlayFrame(23, 46, false, false);
		_ogreDiedAnimShadow->setPlayFrame(23, 46, false, false);

		_ogreDiedAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreDiedAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 1 && state == 4)
	{

	}
	else if (animAngle == 2 && state == 0)
	{
		_orgeAnim->setPlayFrame(16, 24, false, true);
		_orgeAnimShadow->setPlayFrame(16, 24, false, true);

		_orgeAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_orgeAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	}
	else if (animAngle == 2 && state == 1)
	{
		_ogreMoveAnim->setPlayFrame(16, 24, false, true);
		_ogreMoveAnimShadow->setPlayFrame(16, 24, false, true);

		_ogreMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreMoveAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 2 && state == 2)
	{
		_ogreAttackAnim->setPlayFrame(30, 45, false, true);
		_ogreAttackAnimShadow->setPlayFrame(30, 45, false, true);

		_ogreAttackAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreAttackAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 2 && state == 3)
	{
		_ogreDiedAnim->setPlayFrame(46, 69, false, false);
		_ogreDiedAnimShadow->setPlayFrame(46, 69, false, false);

		_ogreDiedAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreDiedAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 2 && state == 4)
	{
	}
	else if (animAngle == 3 && state == 0)
	{
		_orgeAnim->setPlayFrame(24, 32, false, true);
		_orgeAnimShadow->setPlayFrame(24, 32, false, true);

		_orgeAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_orgeAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	}
	else if (animAngle == 3 && state == 1)
	{
		_ogreMoveAnim->setPlayFrame(24, 32, false, true);
		_ogreMoveAnimShadow->setPlayFrame(24, 32, false, true);

		_ogreMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreMoveAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 3 && state == 2)
	{
		_ogreAttackAnim->setPlayFrame(45, 60, false, true);
		_ogreAttackAnimShadow->setPlayFrame(45, 60, false, true);

		_ogreAttackAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreAttackAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 3 && state == 3)
	{
		_ogreDiedAnim->setPlayFrame(69, 92, false, false);
		_ogreDiedAnimShadow->setPlayFrame(69, 92, false, false);

		_ogreDiedAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreDiedAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 3 && state == 4)
	{
	}
	else if (animAngle == 4 && state == 0)
	{
		_orgeAnim->setPlayFrame(32, 40, false, true);
		_orgeAnimShadow->setPlayFrame(32, 40, false, true);

		_orgeAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_orgeAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	}
	else if (animAngle == 4 && state == 1)
	{
		_ogreMoveAnim->setPlayFrame(32, 40, false, true);
		_ogreMoveAnimShadow->setPlayFrame(32, 40, false, true);

		_ogreMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreMoveAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 4 && state == 2)
	{
		_ogreAttackAnim->setPlayFrame(60, 75, false, true);
		_ogreAttackAnimShadow->setPlayFrame(60, 75, false, true);

		_ogreAttackAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreAttackAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 4 && state == 3)
	{
		_ogreDiedAnim->setPlayFrame(92, 115, false, false);
		_ogreDiedAnimShadow->setPlayFrame(92, 115, false, false);

		_ogreDiedAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreDiedAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 4 && state == 4)
	{

	}
	else if (animAngle == 5 && state == 0)
	{
		_orgeAnim->setPlayFrame(40, 48, false, true);
		_orgeAnimShadow->setPlayFrame(40, 48, false, true);

		_orgeAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_orgeAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	}
	else if (animAngle == 5 && state == 1)
	{
		_ogreMoveAnim->setPlayFrame(40, 48, false, true);
		_ogreMoveAnimShadow->setPlayFrame(40, 48, false, true);

		_ogreMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreMoveAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 5 && state == 2)
	{
		_ogreAttackAnim->setPlayFrame(75, 90, false, true);
		_ogreAttackAnimShadow->setPlayFrame(75, 90, false, true);

		_ogreAttackAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreAttackAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 5 && state == 3)
	{
		_ogreDiedAnim->setPlayFrame(115, 138, false, false);
		_ogreDiedAnimShadow->setPlayFrame(115, 138, false, false);

		_ogreDiedAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreDiedAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 5 && state == 4)
	{

	}
	else if (animAngle == 6 && state == 0)
	{
		_orgeAnim->setPlayFrame(48, 56, false, true);
		_orgeAnimShadow->setPlayFrame(48, 56, false, true);

		_orgeAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_orgeAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	}
	else if (animAngle == 6 && state == 1)
	{
		_ogreMoveAnim->setPlayFrame(48, 56, false, true);
		_ogreMoveAnimShadow->setPlayFrame(48, 56, false, true);

		_ogreMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreMoveAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 6 && state == 2)
	{
		_ogreAttackAnim->setPlayFrame(90, 105, false, true);
		_ogreAttackAnimShadow->setPlayFrame(90, 105, false, true);

		_ogreAttackAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreAttackAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 6 && state == 3)
	{
		_ogreDiedAnim->setPlayFrame(138, 161, false, false);
		_ogreDiedAnimShadow->setPlayFrame(138, 161, false, false);

		_ogreDiedAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreDiedAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 6 && state == 4)
	{

	}
	else if (animAngle == 7 && state == 0)
	{
		_orgeAnim->setPlayFrame(56, 64, false, true);
		_orgeAnimShadow->setPlayFrame(56, 64, false, true);

		_orgeAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_orgeAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	}
	else if (animAngle == 7 && state == 1)
	{
		_ogreMoveAnim->setPlayFrame(56, 64, false, true);
		_ogreMoveAnimShadow->setPlayFrame(56, 64, false, true);

		_ogreMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreMoveAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 7 && state == 2)
	{
		_ogreAttackAnim->setPlayFrame(105, 120, false, true);
		_ogreAttackAnimShadow->setPlayFrame(105, 120, false, true);

		_ogreAttackAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreAttackAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 7 && state == 3)
	{
		_ogreDiedAnim->setPlayFrame(161, 184, false, false);
		_ogreDiedAnimShadow->setPlayFrame(161, 184, false, false);

		_ogreDiedAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		_ogreDiedAnimShadow->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}
	else if (animAngle == 7 && state == 4)
	{
	}
}

void MonsterImage::orgeAnim(HDC hdc, int LocationX, int LocationY, int sta)
{
	switch (sta)
	{
	case 0:
		orgeIdle(hdc, LocationX, LocationY);
		break;
	case 1:
		orgeMove(hdc, LocationX, LocationY);
		break;
	case 2:
		orgeAttack(hdc, LocationX, LocationY);
		break;
	case 3:
		orgeDied(hdc, LocationX, LocationY);
		break;
	case 4:
		break;
	default:
		break;
	}
}

void MonsterImage::orgeIdle(HDC hdc, int LocationX, int LocationY)
{
	_orgeShadow->aniRender(hdc, LocationX - 50, LocationY - 54, _orgeAnimShadow);
	_orge->aniRender(hdc, LocationX, LocationY, _orgeAnim);
}

void MonsterImage::orgeMove(HDC hdc, int LocationX, int LocationY)
{
	_orgeMoveShadow->aniRender(hdc, LocationX - 50, LocationY - 54, _ogreMoveAnimShadow);
	_orgeMove->aniRender(hdc, LocationX, LocationY, _ogreMoveAnim);
}

void MonsterImage::orgeAttack(HDC hdc, int LocationX, int LocationY)
{
	_orgeAttackShadow->aniRender(hdc, LocationX - 95, LocationY - 100, _ogreAttackAnimShadow);
	_orgeAttack->aniRender(hdc, LocationX - 31, LocationY - 46, _ogreAttackAnim);
}

void MonsterImage::orgeDied(HDC hdc, int LocationX, int LocationY)
{
	_orgeDiedShadow->aniRender(hdc, LocationX - 120, LocationY - 95, _ogreDiedAnimShadow);
	_orgeDied->aniRender(hdc, LocationX - 95, LocationY - 12, _ogreDiedAnim);
}

void MonsterImage::orgeGetHit(HDC hdc, int LocationX, int LocationY)
{
}


