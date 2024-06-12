#include "Stdafx.h"
#include "BossSkill.h"
#include "Player.h"

HRESULT FlameCircle::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_range = range;
	_amountMax = bulletMax;

	_count = 0;
	_frame = 0;
	return S_OK;
}

void FlameCircle::release(void)
{
	_vProjectile.clear();
}

void FlameCircle::update(void)
{
	_count++;
	if (_count % 7 == 0) _frame++;

	for (_viProjectile = _vProjectile.begin(); _viProjectile != _vProjectile.end();)
	{
		_viProjectile->x += cosf(_viProjectile->angle) * _viProjectile->speed;
		_viProjectile->y += -sinf(_viProjectile->angle) * _viProjectile->speed;

		_viProjectile->rc = RectMakeCenter(_viProjectile->x-SCENEMANAGER->getPLAYER()->getCamera().x, _viProjectile->y+20 - SCENEMANAGER->getPLAYER()->getCamera().y,
			_viProjectile->img->getFrameWidth()/1.5, _viProjectile->img->getFrameHeight()/3);

		if (_range < getDistance(_viProjectile->fireX, _viProjectile->fireY,
			_viProjectile->x, _viProjectile->y))
		{
			_viProjectile = _vProjectile.erase(_viProjectile);
		}
		else ++_viProjectile;
	}
}


void FlameCircle::render(void)
{
	for (_viProjectile = _vProjectile.begin(); _viProjectile != _vProjectile.end(); ++_viProjectile)
	{
		_viProjectile->img->frameRender(getMemDC(), _viProjectile->rc.left-10, _viProjectile->rc.top-110, _frame, 0);
	}
}

void FlameCircle::fire(float x, float y, float angle, float speed)
{
	if (_amountMax <= _vProjectile.size()) return;

	tagProjectile bullet;
	ZeroMemory(&bullet, sizeof(tagProjectile));

	bullet.img = IMAGEMANAGER->findImage(_imageName);

	bullet.speed = speed;
	bullet.angle = angle;

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

	_vProjectile.push_back(bullet);
}

void FlameCircle::removeBullet(int arrNum)
{
	_vProjectile.erase(_vProjectile.begin() + arrNum);
}

//=========================================

HRESULT RedHose::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_range = range;
	_amountMax = bulletMax;

	return S_OK;
}

void RedHose::release(void)
{
	_vProjectile.clear();
}

void RedHose::update(void)
{

	for (_viProjectile = _vProjectile.begin(); _viProjectile != _vProjectile.end();)
	{
		_viProjectile->count++;
		if (_viProjectile->count % 7 == 0)
		{
			_viProjectile->frameX++;
			if (_viProjectile->frameX > 11) _viProjectile->frameX = 1;
		}
		_viProjectile->x += cosf(_viProjectile->angle) * _viProjectile->speed;
		_viProjectile->y += -sinf(_viProjectile->angle) * _viProjectile->speed;

		if ((_angle > 337.5 * (PI / 180) && _angle < 360 * (PI / 180)) || (_angle < 22.5 * (PI / 180) && _angle > 0 * (PI / 180)))
		{
			_viProjectile->rc = RectMakeCenter(_viProjectile->x - SCENEMANAGER->getPLAYER()->getCamera().x, _viProjectile->y - SCENEMANAGER->getPLAYER()->getCamera().y,
				_viProjectile->img->getFrameWidth()-50, _viProjectile->img->getFrameHeight() / 3);
		}
		else if (_angle > 22.5 * (PI / 180) && _angle < 57.5 * (PI / 180))
		{
			_viProjectile->rc = RectMakeCenter(_viProjectile->x - SCENEMANAGER->getPLAYER()->getCamera().x, _viProjectile->y - SCENEMANAGER->getPLAYER()->getCamera().y,
				_viProjectile->img->getFrameWidth() - 50, _viProjectile->img->getFrameHeight() / 3);
		}
		else if (_angle > 57.5 * (PI / 180) && _angle < 122.5 * (PI / 180))
		{
			_viProjectile->rc = RectMakeCenter(_viProjectile->x - SCENEMANAGER->getPLAYER()->getCamera().x, _viProjectile->y - SCENEMANAGER->getPLAYER()->getCamera().y,
				_viProjectile->img->getFrameWidth() / 2, _viProjectile->img->getFrameHeight() / 2);
		}
		else if (_angle > 122.5 * (PI / 180) && _angle < 157.5 * (PI / 180))
		{
			_viProjectile->rc = RectMakeCenter(_viProjectile->x - SCENEMANAGER->getPLAYER()->getCamera().x, _viProjectile->y - SCENEMANAGER->getPLAYER()->getCamera().y,
				_viProjectile->img->getFrameWidth()-50, _viProjectile->img->getFrameHeight() / 4);
		}
		else if (_angle > 157.5 * (PI / 180) && _angle < 202.5 * (PI / 180))
		{
			_viProjectile->rc = RectMakeCenter(_viProjectile->x - SCENEMANAGER->getPLAYER()->getCamera().x, _viProjectile->y - SCENEMANAGER->getPLAYER()->getCamera().y,
				_viProjectile->img->getFrameWidth()-70, _viProjectile->img->getFrameHeight() / 3);
		}
		else if (_angle > 202.5 * (PI / 180) && _angle < 237.5 * (PI / 180))
		{
			_viProjectile->rc = RectMakeCenter(_viProjectile->x - SCENEMANAGER->getPLAYER()->getCamera().x, _viProjectile->y - SCENEMANAGER->getPLAYER()->getCamera().y,
				_viProjectile->img->getFrameWidth()-60, _viProjectile->img->getFrameHeight() / 4);
		}
		else if (_angle > 237.5 * (PI / 180) && _angle < 302.5 * (PI / 180))
		{
			_viProjectile->rc = RectMakeCenter(_viProjectile->x - SCENEMANAGER->getPLAYER()->getCamera().x, _viProjectile->y - SCENEMANAGER->getPLAYER()->getCamera().y,
				_viProjectile->img->getFrameWidth()/2, _viProjectile->img->getFrameHeight() / 3);
		}
		else if (_angle > 302.5 * (PI / 180) && _angle < 337.5 * (PI / 180))
		{
			_viProjectile->rc = RectMakeCenter(_viProjectile->x - SCENEMANAGER->getPLAYER()->getCamera().x, _viProjectile->y - SCENEMANAGER->getPLAYER()->getCamera().y,
				_viProjectile->img->getFrameWidth() / 2, _viProjectile->img->getFrameHeight() / 3);
		}
		

		if (_range < getDistance(_viProjectile->fireX, _viProjectile->fireY,
			_viProjectile->x, _viProjectile->y))
		{
			_viProjectile = _vProjectile.erase(_viProjectile);
		}
		else ++_viProjectile;
	}
}

void RedHose::render(void)
{
	for (_viProjectile = _vProjectile.begin(); _viProjectile != _vProjectile.end(); ++_viProjectile)
	{
		if ((_angle > 337.5 * (PI / 180) && _angle < 360 * (PI / 180)) || (_angle < 22.5 * (PI / 180) && _angle > 0 * (PI / 180)))
		{
			_viProjectile->img->frameRender(getMemDC(), _viProjectile->rc.left-20, _viProjectile->rc.top-40, _viProjectile->frameX, 0);
		}
		else if (_angle > 22.5 * (PI / 180) && _angle < 57.5 * (PI / 180))
		{
			_viProjectile->img->frameRender(getMemDC(), _viProjectile->rc.left - 20, _viProjectile->rc.top - 60, _viProjectile->frameX, 0);
		}
		else if (_angle > 57.5 * (PI / 180) && _angle < 122.5 * (PI / 180))
		{
			_viProjectile->img->frameRender(getMemDC(), _viProjectile->rc.left - 30, _viProjectile->rc.top - 40, _viProjectile->frameX, 0);
		}
		else if (_angle > 122.5 * (PI / 180) && _angle < 157.5 * (PI / 180)) 
		{
			_viProjectile->img->frameRender(getMemDC(), _viProjectile->rc.left - 25, _viProjectile->rc.top - 50, _viProjectile->frameX, 0);
		}
		else if (_angle > 157.5 * (PI / 180) && _angle < 202.5 * (PI / 180))
		{
			_viProjectile->img->frameRender(getMemDC(), _viProjectile->rc.left - 40, _viProjectile->rc.top - 50, _viProjectile->frameX, 0);
		}
		else if (_angle > 202.5 * (PI / 180) && _angle < 237.5 * (PI / 180))
		{
			_viProjectile->img->frameRender(getMemDC(), _viProjectile->rc.left - 20, _viProjectile->rc.top - 60, _viProjectile->frameX, 0);
		}
		else if (_angle > 237.5 * (PI / 180) && _angle < 302.5 * (PI / 180))
		{
			_viProjectile->img->frameRender(getMemDC(), _viProjectile->rc.left - 20, _viProjectile->rc.top - 40, _viProjectile->frameX, 0);
		}
		else if (_angle > 302.5 * (PI / 180) && _angle < 337.5 * (PI / 180))
		{
			_viProjectile->img->frameRender(getMemDC(), _viProjectile->rc.left - 20, _viProjectile->rc.top - 40, _viProjectile->frameX, 0);
		}
	}
}

void RedHose::fire(float x, float y, float angle, float speed)
{
	if (_amountMax <= _vProjectile.size()) return;

	tagProjectile bullet;
	ZeroMemory(&bullet, sizeof(tagProjectile));

	bullet.img = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.angle = angle;

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;

	if ((bullet.angle > 337.5 * (PI / 180) && bullet.angle < 360 * (PI / 180)) || (bullet.angle < 22.5 * (PI / 180) && bullet.angle > 0 * (PI / 180)))
	{
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.img->getFrameWidth() - 50, bullet.img->getFrameHeight() / 3);
	}
	else if (bullet.angle > 22.5 * (PI / 180) && bullet.angle < 57.5 * (PI / 180))
	{
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.img->getFrameWidth() - 50, bullet.img->getFrameHeight() / 3);
	}
	else if (bullet.angle > 57.5 * (PI / 180) && bullet.angle < 122.5 * (PI / 180))
	{
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.img->getFrameWidth() / 2, bullet.img->getFrameHeight() / 2);
	}
	else if (bullet.angle > 122.5 * (PI / 180) && bullet.angle < 157.5 * (PI / 180))
	{
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.img->getFrameWidth() - 50, bullet.img->getFrameHeight() / 4);
	}
	else if (bullet.angle > 157.5 * (PI / 180) && bullet.angle < 202.5 * (PI / 180))
	{
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.img->getFrameWidth() - 70, bullet.img->getFrameHeight() / 3);
	}
	else if (bullet.angle > 202.5 * (PI / 180) && bullet.angle < 237.5 * (PI / 180))
	{
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.img->getFrameWidth() - 60, bullet.img->getFrameHeight() / 4);
	}
	else if (bullet.angle > 237.5 * (PI / 180) && bullet.angle < 302.5 * (PI / 180))
	{
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.img->getFrameWidth() / 2, bullet.img->getFrameHeight() / 3);
	}
	else if (bullet.angle > 302.5 * (PI / 180) && bullet.angle < 337.5 * (PI / 180))
	{
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.img->getFrameWidth() / 2, bullet.img->getFrameHeight() / 3);
	}

	_vProjectile.push_back(bullet);
}

void RedHose::removeBullet(int arrNum)
{	
	_vProjectile.erase(_vProjectile.begin() + arrNum);
}

// ===================================================


HRESULT FireStorm::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_range = range;
	_amountMax = bulletMax;

	_count = 0;

	return S_OK;
}

void FireStorm::release(void)
{
	_vProjectile.clear();
}

void FireStorm::update(void)
{
	for (_viProjectile = _vProjectile.begin(); _viProjectile != _vProjectile.end();)
	{
		_viProjectile->count++;
		if (_viProjectile->count % 4 == 0)
		{
			_viProjectile->frameX++;
		}

		_viProjectile->rc = RectMakeCenter(_viProjectile->x-30 - SCENEMANAGER->getPLAYER()->getCamera().x, _viProjectile->y - 60 - SCENEMANAGER->getPLAYER()->getCamera().y,
			_viProjectile->img->getFrameWidth() / 1.5, _viProjectile->img->getFrameHeight() / 3);

		if (_viProjectile->frameX > 52)
		{
			_viProjectile = _vProjectile.erase(_viProjectile);
		}
		else ++_viProjectile;
	}
}

void FireStorm::render(void)
{
	for (_viProjectile = _vProjectile.begin(); _viProjectile != _vProjectile.end(); ++_viProjectile)
	{
		_viProjectile->img->frameRender(getMemDC(), _viProjectile->rc.left - 10, _viProjectile->rc.top - 60, _viProjectile->frameX, 0);
	}
}

void FireStorm::fire(float x, float y, float angle, float speed)
{
	if (_amountMax <= _vProjectile.size()) return;

	tagProjectile bullet;
	ZeroMemory(&bullet, sizeof(tagProjectile));

	bullet.img = IMAGEMANAGER->findImage(_imageName);

	bullet.speed = speed;
	bullet.angle = angle;

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());
	
	_vProjectile.push_back(bullet);
}

void FireStorm::removeBullet(int arrNum)
{
	_vProjectile.erase(_vProjectile.begin() + arrNum);
}
