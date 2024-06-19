#include "Stdafx.h"
#include "testScene.h"

HRESULT testScene::init(void)
{
	_cameraCenter.x = 640;
	_cameraCenter.y = 360;

	TILEMANAGER->init();
	TILEMANAGER->MapSetting(TechTile);
	TILEMANAGER->DefaultMapSetting(20, 15);
	TILEMANAGER->SetWorldSize(20, 15);
	TILEMANAGER->InsertWorldInfo();

	return S_OK;
}

void testScene::release(void)
{

	TILEMANAGER->release();
}

void testScene::update(void)
{
	keyBind();
	RECT rc = RectMake(0, 0, 0, 0);
	Point2D temp = Point2D(0, 0);

	TILEMANAGER->update(_camera);
	TILEMANAGER->MapToolUpdate();

	if (KEYMANAGER->isOnceKeyDown(VK_F12))
	{
		SCENEMANAGER->changeScene("메인화면");
	}
}

void testScene::render(void)
{
	cameraUpdate();

	TILEMANAGER->DrawWorld(getMemDC());
	TILEMANAGER->DrawAlphaWall(getMemDC(), 0);
	TILEMANAGER->MapToolRender(getMemDC());
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
