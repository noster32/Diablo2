#include "Stdafx.h"
#include "World.h"

HRESULT World::init()
{
    TILEMANAGER->init();
    TILEMANAGER->MapSetting(TechTile);
    TILEMANAGER->VilliageMapInput();
    TILEMANAGER->SetWorldSize(20, 15);
    TILEMANAGER->InsertWorldInfo();

    return S_OK;
}

void World::release(void)
{
    TILEMANAGER->release();
}

void World::update(Point2D camera)
{
    TILEMANAGER->update(camera);
}

void World::render(HDC hdc, int playerX)
{
    TILEMANAGER->DrawWorld(hdc);
    TILEMANAGER->DrawAlphaWall(hdc, playerX);
}


