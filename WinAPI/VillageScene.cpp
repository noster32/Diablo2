#include "Stdafx.h"
#include "VillageScene.h"

HRESULT VillageScene::init(void)
{
	_player = SCENEMANAGER->getPLAYER();
	_player->setPlayerCoord(Point2D(900, 500));

	_world = new World;
	_world->init();
	_WP = new WAYPOINT;
	_WP->init();
	SCENEMANAGER->setWAYP(_WP);
	SOUNDMANAGER->AddSound("TownBGM", "Resources/Sounds/Boss/townbgm.wav")->SetVolume(80);
	SOUNDMANAGER->AddSound("OgreDie", "Resources/Sounds/ogreDie.wav")->SetVolume(100);
	SOUNDMANAGER->AddSound("BalocDie", "Resources/Sounds/balogDie.wav")->SetVolume(100);
	SOUNDMANAGER->FindSound("TownBGM")->Play(1);

    return S_OK;
}

void VillageScene::release(void)
{
	_world->release();
	SAFE_DELETE(_world);
}

void VillageScene::update(void)
{
	_world->update(_player->getCamera());
	_player->update();

	_WP->update(_player);
	if (KEYMANAGER->isOnceKeyDown(VK_F11))
	{
		SCENEMANAGER->changeScene("´øÀü");
	}
}

void VillageScene::render(void)
{
	_world->render(getMemDC(), TILEMANAGER->CoordCheck(_player->getPlayerX(), _player->getPlayerY()).x);
	_WP->render();
	_player->render(true);
}
