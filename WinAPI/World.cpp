#include "Stdafx.h"
#include "World.h"

HRESULT World::init()
{
    TILEMANAGER->init();
    TILEMANAGER->MapSetting(TechTile);
    TILEMANAGER->VilliageMapInput();
    TILEMANAGER->SetWorldSize(20, 15);
    TILEMANAGER->InsertWorldInfo();

    temp = 0;

    return S_OK;
}

void World::release(void)
{
    TILEMANAGER->release();
}

void World::update(Point2D camera)
{
    TILEMANAGER->update(camera);
    //TILEMANAGER->MapToolUpdate();

    if (KEYMANAGER->isOnceKeyDown(VK_HOME))
    {
        TILEMANAGER->VilliageMapOutput();
    }
    if (KEYMANAGER->isOnceKeyDown('E'))
    {
        temp++;
    }
    if (KEYMANAGER->isOnceKeyDown('Q'))
    {
        temp--;
        if (temp <= 0) temp = 0;
    }
    TILEMANAGER->setTileY(temp);

}

void World::render(HDC hdc, int playerX)
{
    TILEMANAGER->DrawWorld(hdc);
    TILEMANAGER->DrawAlphaWall(hdc, playerX);
    //TILEMANAGER->MapToolRender(hdc);
}


