#include "Stdafx.h"
#include "DiabloMap.h"
#include "Inventory.h"


HRESULT DiabloMap::init()
{
    TILEMANAGER->init();
    TILEMANAGER->MapSetting(BossTile);
    TILEMANAGER->DiaMapInput();
    TILEMANAGER->SetWorldSize(70, 110);
    TILEMANAGER->InsertWorldInfo();
    setMobSpawn();

    for (Balog* b : _vBalogSpawnLocation)
    {
        b->init();
    }
    for (Orge* o : _vOrgeSpawnLocation)
    {
        o->init();
    }
    return S_OK;
}

void DiabloMap::release(void)
{
    TILEMANAGER->release();
    for (Balog* b : _vBalogSpawnLocation)
    {
        b->release();
        SAFE_DELETE(b);
    }
    for (Orge* o : _vOrgeSpawnLocation)
    {
        o->release();
        SAFE_DELETE(o);

    }
    
}

void DiabloMap::update(Point2D camera, RECT playerRect, Point2D playerCoord)
{
    _camera = camera;
    TILEMANAGER->update(camera);
   
    for (Balog* b : _vBalogSpawnLocation)
    {
        if (b->getMonsterX() > _camera.x && b->getMonsterY() > _camera.y && b->getMonsterX() <= _camera.x + 800 && b->getMonsterY() <= _camera.y + 600)
            b->update(camera,playerRect,playerCoord);
    }
    for (Orge* o : _vOrgeSpawnLocation)
    {
        if (o->getMonsterX() > _camera.x && o->getMonsterY() > _camera.y && o->getMonsterX() <= _camera.x + 800 && o->getMonsterY() <= _camera.y + 600)
            o->update(camera,playerRect,playerCoord);
    }
}

void DiabloMap::render(HDC hdc)
{
    TILEMANAGER->DrawWorld(hdc);

    for (Balog* b : _vBalogSpawnLocation)
    {
        if(b->getMonsterX() > _camera.x && b->getMonsterY() > _camera.y && b->getMonsterX() <= _camera.x + 800 && b->getMonsterY() <= _camera.y + 600)
            b->render(hdc);
    }
    for (Orge* o : _vOrgeSpawnLocation)
    {
        if (o->getMonsterX() > _camera.x && o->getMonsterY() > _camera.y && o->getMonsterX() <= _camera.x + 800 && o->getMonsterY() <= _camera.y + 600)
            o->render(hdc);
    }
}

void DiabloMap::setMobSpawn()
{
    _vOrgeSpawnLocation.push_back(new Orge(Point2D(4372, 4704)));
    _vOrgeSpawnLocation.push_back(new Orge(Point2D(4335, 4799)));
    _vOrgeSpawnLocation.push_back(new Orge(Point2D(4457, 4894)));
 
    _vBalogSpawnLocation.push_back(new Balog(Point2D(4726, 4964)));

    _vOrgeSpawnLocation.push_back(new Orge(Point2D(5204, 4347)));
    _vOrgeSpawnLocation.push_back(new Orge(Point2D(5982, 4392)));
  
    _vBalogSpawnLocation.push_back(new Balog(Point2D(6239, 4383)));
    _vBalogSpawnLocation.push_back(new Balog(Point2D(6129, 4325)));

    _vOrgeSpawnLocation.push_back(new Orge(Point2D(6710, 3670)));
    _vOrgeSpawnLocation.push_back(new Orge(Point2D(6925, 3652)));
    _vOrgeSpawnLocation.push_back(new Orge(Point2D(6945, 3632)));
    _vOrgeSpawnLocation.push_back(new Orge(Point2D(7040, 3602)));
    _vBalogSpawnLocation.push_back(new Balog(Point2D(7007, 3880)));
    _vBalogSpawnLocation.push_back(new Balog(Point2D(7230, 3748)));
    _vBalogSpawnLocation.push_back(new Balog(Point2D(7379, 3935)));
    _vBalogSpawnLocation.push_back(new Balog(Point2D(7279, 3935)));

    _vOrgeSpawnLocation.push_back(new Orge(Point2D(9732, 2671)));
    _vOrgeSpawnLocation.push_back(new Orge(Point2D(10138, 2600)));
    _vOrgeSpawnLocation.push_back(new Orge(Point2D(10352, 2385)));
    _vOrgeSpawnLocation.push_back(new Orge(Point2D(10045, 2193)));
    _vBalogSpawnLocation.push_back(new Balog(Point2D(10183, 2240)));
    _vBalogSpawnLocation.push_back(new Balog(Point2D(9926, 2174)));
}