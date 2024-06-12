#include "Stdafx.h"
#include "DungeonScene.h"

HRESULT DungeonScene::init(void)
{
	_player = SCENEMANAGER->getPLAYER();
	_player->setPlayerRouteErase();
	_player->setPlayerCoord(Point2D(3300, 5500));
	
	_boss = new Boss;
	_boss->init();
	_diaMap = new DiabloMap;
	_diaMap->init();
	_combat = new Combat;

	_isLoadingSceneImg = true;
	_loadingDcnt = 0;
	_loadingPlusImg = IMAGEMANAGER->findImage("로딩이미지");
	_loadingPlusImg->setFrameX(0);
	SOUNDMANAGER->FindSound("FightBGM")->Play(1);
	_tyrael.x = 3000;
	_tyrael.y = 5200;
	_tyrael.imgFrameX, _tyrael.imgFrameX, _comingCount = 0;
	
	// 다이얼 로그
	_tyrael.click = false;
	
	_text = 100;
	
	_alterActive = false;

	SOUNDMANAGER->FindSound("FightBGM")->Play(1);

	return S_OK;
}

void DungeonScene::release(void)
{
	_boss->release();
	SAFE_DELETE(_boss);
	_diaMap->release();
	SAFE_DELETE(_diaMap);
	SAFE_DELETE(_combat);
}

void DungeonScene::update(void)
{
	_count++;

	if (!_isLoadingSceneImg)
	{
		_diaMap->update(_player->getCamera(), _player->getPlayerHitRc(), _player->getPlayerCoord());
		_alterRc = RectMake(9720 - SCENEMANAGER->getPLAYER()->getCamera().x, 1950 - SCENEMANAGER->getPLAYER()->getCamera().y, IMAGEMANAGER->findImage("Alter")->getWidth(), IMAGEMANAGER->findImage("Alter")->getHeight());

		_player->update(_boss);
		if (_player->getIsDiaSummon())
		{
			_boss->update(_player);
			collision();
		}
		else _combat->update(_player, _diaMap);

		if (IntersectRect(&_temp, &_player->getPlayerStat().rc, &_alterRc))
		{
			_alterActive = true;			
		}

		if (_alterActive)
		{
			_player->CShake(); 
			if (_player->getIsDiaSummon()) _alterActive = false;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_F9))
		{
			SCENEMANAGER->changeScene("마을");
		}
	}
	else
	{
		_loadingDcnt++;
		if (_loadingDcnt % 14 == 0)
		{
			_loadingPlusImg->setFrameX(_loadingPlusImg->getFrameX() + 1);
			if (_loadingPlusImg->getFrameX() > 8)
			{
				_loadingPlusImg->setFrameX(0);
				_isLoadingSceneImg = false;
				SCENEMANAGER->setIsLoadingImg(false);
			}
		}
	}
	// 티리엘 프레임
	if (_count % 4 == 0)
	{
		_tyrael.imgFrameX++;
		if (_tyrael.imgFrameX >= 30 && _tyrael.imgFrameY == 0)
		{
			_tyrael.imgFrameY = 1;
			_tyrael.imgFrameX = 0;
		}
		else if (_tyrael.imgFrameX >= 30 && _tyrael.imgFrameY == 1)
		{
			_tyrael.imgFrameY = 0;
			_tyrael.imgFrameX = 0;
		}
	}
	// 티리엘 등장 카운트
	if (_boss->getIsDead() == true && _count % 16 == 0 )
	{
		_comingCount++;
	}

	// 티리엘 렉트
	if (_boss->getIsDead() == true)
	{
		_tyrael.tyRc = RectMake(_boss->getX() - SCENEMANAGER->getPLAYER()->getCamera().x,
			_boss->getY() - SCENEMANAGER->getPLAYER()->getCamera().y - 150, 42, 90);
	}
	// 티리엘 렉트 클릭
	if (PtInRect(&_tyrael.tyRc,_ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_tyrael.click = true;
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_tyrael.click = false;
			_text = 100;
		}
	}
	if (_tyrael.click)
	{
		// 다이얼로그 텍스트 속도
		if (_count % 15 == 0)
		{
			_text -= 1;
		}
	}
}

void DungeonScene::render(void)
{
	if (!_isLoadingSceneImg)
	{
		_diaMap->render(getMemDC());
		_player->render(false);
		IMAGEMANAGER->render("Alter", getMemDC(), _alterRc.left, _alterRc.top);

	
		if (_alterActive)
		{
			 IMAGEMANAGER->frameRender("AlterActive", getMemDC(), _alterRc.left, _alterRc.top - 100, 0, 0);
		}
		_combat->render(getMemDC(), _player);

		if (_player->getIsDiaSummon())
		{
			_boss->render();
		}
		effectrender();
	}
	else
	{
		_loadingPlusImg->frameRender(getMemDC(), 300, 200, _loadingPlusImg->getFrameX(), 0);
	}


	if (_boss->getIsDead()==true)
	{
		// 티리엘 등장
		if (_comingCount <= 30)
		{
		IMAGEMANAGER->frameRender("티리엘등장", getMemDC(), _tyrael.tyRc.left-80,
			_tyrael.tyRc.top-330, _comingCount, 0);
		}
		if (_comingCount >= 15)
		{
			// 티리엘
			IMAGEMANAGER->frameRender("티리엘", getMemDC(), _tyrael.tyRc.left-230,
				_tyrael.tyRc.top-220, _tyrael.imgFrameX, _tyrael.imgFrameY);
		}
	}
	
	// 다이얼 로그 출력
	if (_tyrael.click)
	{
		IMAGEMANAGER->render("티리엘텍스트배경", getMemDC(), 234, 5);
		IMAGEMANAGER->render("티리엘배경블랙", getTyDC(), 234, 5);
		IMAGEMANAGER->render("티리엘텍스트", getTyDC(), 240, _text);
		BitBlt(getMemDC(), 236, 10, 1000, 400, getTyDC(), 234, 5, SRCCOPY);
	}
}

void DungeonScene::collision(void)
{
	for (int i = 0; i < _boss->getFireS()->getProjectile().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_boss->getFireS()->getProjectile()[i].rc, &_player->getPlayerStat().hitRC))
		{
			if(_count % 10==0)	_player->hitDamage(15);
		}
	}

	for (int i = 0; i < _boss->getRedH()->getProjectile().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_boss->getRedH()->getProjectile()[i].rc, &_player->getPlayerStat().hitRC))
		{
			if (_count % 20 == 0) _player->hitDamage(40);
		}
	}

	for (int i = 0; i < _boss->getFlameC()->getProjectile().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_boss->getFlameC()->getProjectile()[i].rc, &_player->getPlayerStat().hitRC))
		{
			if (_count % 20 == 0) _player->hitDamage(120);
		}
	}

	for (int i = 0; i < _player->getHYDRASKILL()->getHydraInfo().size(); i++)
	{
		for (int j = 0; j < _player->getHYDRASKILL()->getHydraInfo()[i].bullet.size(); j++)
		{
			RECT tempRC;
			if (IntersectRect(&tempRC, &_player->getHYDRASKILL()->getHydraInfo()[i].bullet[j].rc, &_boss->getHitBox())
				&& _boss->getHp() > 0 && !_player->getHYDRASKILL()->getHydraInfo()[i].bullet[j].hit)
			{
				_boss->hitDamage(20);
				_player->getHYDRASKILL()->setHydraBulletHit(i, j, true);
				_vDiafireHitEffect.push_back({ 0,0,_boss->getX(),_boss->getY(),false });
	
				continue;
			}
		}
	}

	for (int i = 0; i < _player->getMETEORSKILL()->getExplosion().size(); i++)
	{
		_fireDelay++;
		if (_fireDelay % 40 == 0)
		{
			RECT tempRC;
			if (IntersectRect(&tempRC, &_player->getMETEORSKILL()->getExplosion()[i].rc, &_boss->getHitBox())
				&& _boss->getHp() > 0)
			{
				_boss->hitDamage(20);
				_vDiafireHitEffect.push_back({ 0, 0,_boss->getX(),_boss->getY(), false });
			}
			_fireDelay = 0;
		}
	}

	for (int i = 0; i < _player->getFROZENORBSKILL()->getIceBolt1().size(); i++)
	{
		RECT tempRC;
		if (IntersectRect(&tempRC, &_player->getFROZENORBSKILL()->getIceBolt1()[i].rc, &_boss->getHitBox())
			&& _boss->getHp() > 0 && !_player->getFROZENORBSKILL()->getIceBolt1()[i].hit)
		{
			_boss->hitDamage(30);
			_player->getFROZENORBSKILL()->setIceBolt1Hit(i, true);
			_vDiaiceHitEffect.push_back({ 0,0,_boss->getX(),_boss->getY(),false });
			continue;
		}
	}
	for (int i = 0; i < _player->getFROZENORBSKILL()->getIceBolt5().size(); i++)
	{
		RECT tempRC;
		if (IntersectRect(&tempRC, &_player->getFROZENORBSKILL()->getIceBolt5()[i].rc, &_boss->getHitBox())
			&& _boss->getHp() > 0 && !_player->getFROZENORBSKILL()->getIceBolt5()[i].hit)
		{
			_boss->hitDamage(30);
			_player->getFROZENORBSKILL()->setIceBolt5Hit(i, true);
			_vDiaiceHitEffect.push_back({ 0,0,_boss->getX(),_boss->getY(),false });

			continue;
		}
	}


	for (_viDiafireHitEffect = _vDiafireHitEffect.begin(); _viDiafireHitEffect != _vDiafireHitEffect.end(); )
	{
		if (!_viDiafireHitEffect->hitend)
		{
			_viDiafireHitEffect->count++;
			if (_viDiafireHitEffect->count % 8 == 0)
			{
				_viDiafireHitEffect->curidx++;
				if (_viDiafireHitEffect->curidx > 11) _viDiafireHitEffect->hitend = true;
				_viDiafireHitEffect->count = 0;
			}
			else ++_viDiafireHitEffect;
		}
		else
		{
			_viDiafireHitEffect = _vDiafireHitEffect.erase(_viDiafireHitEffect);
		}
	}

	for (_viDiaiceHitEffect = _vDiaiceHitEffect.begin(); _viDiaiceHitEffect != _vDiaiceHitEffect.end(); )
	{
		if (!_viDiaiceHitEffect->hitend)
		{
			_viDiaiceHitEffect->count++;
			if (_viDiaiceHitEffect->count % 8 == 0)
			{
				_viDiaiceHitEffect->curidx++;
				if (_viDiaiceHitEffect->curidx > 16) _viDiaiceHitEffect->hitend = true;
				_viDiaiceHitEffect->count = 0;
			}
			else ++_viDiaiceHitEffect;
		}
		else
		{
			_viDiaiceHitEffect = _vDiaiceHitEffect.erase(_viDiaiceHitEffect);
		}
	}
}

void DungeonScene::effectrender(void)
{
	for (_viDiafireHitEffect = _vDiafireHitEffect.begin(); _viDiafireHitEffect != _vDiafireHitEffect.end(); ++_viDiafireHitEffect)
	{
		IMAGEMANAGER->findImage("메테오폭발")->frameRender(getMemDC(), _viDiafireHitEffect->x - 50 - _player->getCamera().x,
			_viDiafireHitEffect->y - 50 - _player->getCamera().y, _viDiafireHitEffect->curidx, 0);
	}

	for (_viDiaiceHitEffect = _vDiaiceHitEffect.begin(); _viDiaiceHitEffect != _vDiaiceHitEffect.end(); ++_viDiaiceHitEffect)
	{
		IMAGEMANAGER->findImage("아이스볼트히트")->frameRender(getMemDC(), _viDiaiceHitEffect->x - 50 - _player->getCamera().x,
			_viDiaiceHitEffect->y - 50 - _player->getCamera().y, _viDiaiceHitEffect->curidx, 0);
	}
}
