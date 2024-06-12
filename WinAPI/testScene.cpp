#include "Stdafx.h"
#include "testScene.h"

HRESULT testScene::init(void)
{
	_cameraCenter.x = 640;
	_cameraCenter.y = 360;

	//_dia = new DiabloMap;
	//_dia->init();
	
	w = new World;
	w->init();

	return S_OK;
}

void testScene::release(void)
{
	//_dia->release();
	//SAFE_DELETE(_dia);
	w->release();
	SAFE_DELETE(w);
}

void testScene::update(void)
{
	keyBind();
	RECT rc = RectMake(0, 0, 0, 0);
	Point2D temp = Point2D(0, 0);
	//_dia->update(_camera, rc, temp);
	w->update(_camera);
}

void testScene::render(void)
{
	cameraUpdate();
	//_dia->render(getMemDC());
	w->render(getMemDC(), 0);
}

void testScene::cameraUpdate(void)
{
	_camera.x = _cameraCenter.x - WINSIZE_X / 2;
	_camera.y = _cameraCenter.y - WINSIZE_Y / 2;

	if (_camera.x < 0)
		_camera.x = 0;
	else if (_camera.x >= 15000 - WINSIZE_X)
		_camera.x = 15000 - WINSIZE_X;

	if (_camera.y < 0)
		_camera.y = 0;
	else if (_camera.y >= 15000 - WINSIZE_Y)
		_camera.y = 15000 - WINSIZE_Y;
}

void testScene::keyBind(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_cameraCenter.x -= 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_cameraCenter.x += 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_cameraCenter.y -= 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_cameraCenter.y += 10;
	}
}
