#include "Stdafx.h"
#include "MainGame.h"
#include "VillageScene.h"
#include "DungeonScene.h"
#include "MenuScene.h"
#include "LoadingScene.h"
#include "OpeningScene.h"
#include "testScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	
	SCENEMANAGER->addScene("����", new DungeonScene);
	SCENEMANAGER->addScene("����", new VillageScene);
	SCENEMANAGER->addScene("����ȭ��", new MenuScene);
	SCENEMANAGER->addScene("�ε���", new LoadingScene);
	SCENEMANAGER->addScene("�����׾�", new OpeningScene);
	SCENEMANAGER->addScene("����", new testScene);
	SCENEMANAGER->changeScene("�����׾�");

	SOUNDMANAGER->init(_hWnd);

	_master = new MasterScene;
	_master->init();
	
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	_master->release();
	SAFE_DELETE(_master);
}

void MainGame::update(void)
{
	GameNode::update();
	_master->update();
	SCENEMANAGER->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	
	SCENEMANAGER->render();
	_master->render();
	
	TIMEMANAGER->render(getMemDC());

	if (!SCENEMANAGER->getIsOpening())
		this->getBackBuffer()->render(getHDC());
}


