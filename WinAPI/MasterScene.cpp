#include "Stdafx.h"
#include "MasterScene.h"

HRESULT MasterScene::init(void)
{
	_player = new Player;
	_player->init();
	SCENEMANAGER->setPLAYER(_player);
	_ui = new UI2;
	_ui->init();

	return S_OK;
}

void MasterScene::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
	_ui->release();
	SAFE_DELETE(_ui);
}

void MasterScene::update(void)
{

	if (!SCENEMANAGER->getIsLoadingImg()) _ui->update();

}

void MasterScene::render(void)
{
	if (!SCENEMANAGER->getIsLoadingImg()) _ui->render(_player);
}
