#include "Stdafx.h"
#include "Combat.h"
#include "Player.h"
#include "DiabloMap.h"

void Combat::update(Player* player, DiabloMap* diaMap)
{
	for (auto orge : diaMap->getOrge())
	{
		if (orge->getIsAttack())
		{
			RECT rc;
			if (IntersectRect(&rc, &orge->getAttackRange(), &player->getPlayerHitRc()))
			{
				player->hitDamage(1);
				break;
			}
		}
	}

	for (int i=0; i < player->getMETEORSKILL()->getExplosion().size();i++)
	{
		_fireDelay++;
		if (_fireDelay % 40 == 0)
		{
			for (auto orge : diaMap->getOrge())
			{
				RECT tempRC;
				if (IntersectRect(&tempRC, &player->getMETEORSKILL()->getExplosion()[i].rc, &orge->getHitBox())
					&& orge->getHp() > 0)
				{
					orge->hitEnemy(50);
					_vfireHitEffect.push_back({ 0, 0, orge->getMonsterX(), orge->getMonsterY(), false });
				}
			}
			for (auto balog : diaMap->getBalog())
			{
				RECT tempRC;
				if (IntersectRect(&tempRC, &player->getMETEORSKILL()->getExplosion()[i].rc, &balog->getHitBox())
					&& balog->getHp() > 0)
				{
					balog->hitEnemy(50);
					_vfireHitEffect.push_back({ 0, 0, balog->getMonsterX(), balog->getMonsterY(), false });
				}
			}
			_fireDelay = 0;
		}
	}

	for (int i = 0; i < player->getFROZENORBSKILL()->getIceBolt1().size(); i++)
	{
		for (auto orge : diaMap->getOrge())
		{
			RECT tempRC;
			if (IntersectRect(&tempRC, &player->getFROZENORBSKILL()->getIceBolt1()[i].rc, &orge->getHitBox())
				&& orge->getHp() > 0)
			{
				orge->hitEnemy(15);
				player->getFROZENORBSKILL()->setIceBolt1Hit(i, true);
				_viceHitEffect.push_back({ 0, 0, orge->getMonsterX(), orge->getMonsterY(), false });
			}
		}
		for (auto balog : diaMap->getBalog())
		{
			RECT tempRC;
			if (IntersectRect(&tempRC, &player->getFROZENORBSKILL()->getIceBolt1()[i].rc, &balog->getHitBox())
				&& balog->getHp() > 0)
			{
				balog->hitEnemy(15);
				player->getFROZENORBSKILL()->setIceBolt1Hit(i, true);
				_viceHitEffect.push_back({ 0, 0, balog->getMonsterX(), balog->getMonsterY(), false });
			}
		}
	}
	for (int i = 0; i < player->getFROZENORBSKILL()->getIceBolt5().size(); i++)
	{
		for (auto orge : diaMap->getOrge())
		{
			RECT tempRC;
			if (IntersectRect(&tempRC, &player->getFROZENORBSKILL()->getIceBolt5()[i].rc, &orge->getHitBox())
				&& orge->getHp() > 0)
			{
				orge->hitEnemy(15);
				player->getFROZENORBSKILL()->setIceBolt5Hit(i, true);
				_viceHitEffect.push_back({ 0, 0, orge->getMonsterX(), orge->getMonsterY(), false });
			}
		}
		for (auto balog : diaMap->getBalog())
		{
			RECT tempRC;
			if (IntersectRect(&tempRC, &player->getFROZENORBSKILL()->getIceBolt5()[i].rc, &balog->getHitBox())
				&& balog->getHp() > 0)
			{
				balog->hitEnemy(15);
				player->getFROZENORBSKILL()->setIceBolt5Hit(i, true);
				_viceHitEffect.push_back({ 0, 0, balog->getMonsterX(), balog->getMonsterY(), false });
			}
		}
	}

	for (_vifireHitEffect = _vfireHitEffect.begin(); _vifireHitEffect != _vfireHitEffect.end();)
	{
		if (!_vifireHitEffect->hitend)
		{
			_vifireHitEffect->count++;
			if (_vifireHitEffect->count % 8 == 0)
			{
				_vifireHitEffect->curidx++;
				if (_vifireHitEffect->curidx > 11) _vifireHitEffect->hitend = true;
				_vifireHitEffect->count = 0;
			}
			else ++_vifireHitEffect;
		}
		else
		{
			_vifireHitEffect = _vfireHitEffect.erase(_vifireHitEffect);
		}
	}

	for (_viiceHitEffect = _viceHitEffect.begin(); _viiceHitEffect != _viceHitEffect.end();)
	{
		if (!_viiceHitEffect->hitend)
		{
			_viiceHitEffect->count++;
			if (_viiceHitEffect->count % 8 == 0)
			{
				_viiceHitEffect->curidx++;
				if (_viiceHitEffect->curidx > 16) _viiceHitEffect->hitend = true;
				_viiceHitEffect->count = 0;
			}
			else ++_viiceHitEffect;
		}
		else
		{
			_viiceHitEffect = _viceHitEffect.erase(_viiceHitEffect);
		}
	}
}

void Combat::render(HDC hdc, Player* player)
{
	for (_vifireHitEffect = _vfireHitEffect.begin(); _vifireHitEffect != _vfireHitEffect.end(); ++_vifireHitEffect)
	{
		IMAGEMANAGER->findImage("메테오폭발")->frameRender(hdc, _vifireHitEffect->x - 50 - player->getCamera().x,
			_vifireHitEffect->y - 50 - player->getCamera().y, _vifireHitEffect->curidx, 0);
	}

	for (_viiceHitEffect = _viceHitEffect.begin(); _viiceHitEffect != _viceHitEffect.end(); ++_viiceHitEffect)
	{
		IMAGEMANAGER->findImage("아이스볼트히트")->frameRender(hdc, _viiceHitEffect->x - 50 - player->getCamera().x,
			_viiceHitEffect->y - 50 - player->getCamera().y, _viiceHitEffect->curidx, 0);
	}
}

