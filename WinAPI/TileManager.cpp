#include "Stdafx.h"
#include "TileManager.h"


HRESULT TileManager::init(void)
{
    _tileTexture = new TileTexture();
    _tileTexture->init();

    _wallTexture = new WallTexture();
    _wallTexture->init();

    _alphaWallTexture = new AlphaWallTexture();
    _alphaWallTexture->init();

    _floorTexture = new FloorTexture();
    _floorTexture->init();

    _tileSelected = false;

    _selectTileNum = 0;
    _tileIndexY = 0;

    _setTileImage = TechTile;
    _setImageMode = TileEdit;

    _setTile = _tileTexture->getImg();

    _pSelected.x = 0;
    _pSelected.y = 0;
    _pTestSelect.x = 0;
    _pTestSelect.y = 0;
    count = 0;
    index = 0;
    page = 0; 

    return S_OK;
}

void TileManager::release(void)
{
    _tileTexture->release();
    _wallTexture->release();
    _alphaWallTexture->release();
  
    if (_wallTexture != nullptr)
    {
        SAFE_DELETE(_wallTexture);
        _wallTexture = nullptr;
    }
    if (_alphaWallTexture != nullptr)
    {
        SAFE_DELETE(_alphaWallTexture);
        _alphaWallTexture = nullptr;
    }
    if (_floorTexture != nullptr)
    {
        SAFE_DELETE(_floorTexture);
        _floorTexture = nullptr;
    }

}

void TileManager::update(Point2D camera)
{
    _pt2dMouse.x = _ptMouse.x;
    _pt2dMouse.y = _ptMouse.y;
    _camera.x = camera.x;
    _camera.y = camera.y;
    _realCursor = _pt2dMouse + camera;
    
    count++;

    if (count % 20 == 0)
    {
        index++;
    }

    tileLocationCal();

    vector<Point2D>::iterator _mapCoordIter(_vMapRenderLocation.begin());
    vector<int>::iterator _floorTileIter(_vFloorMap.begin());
    vector<FloorTexture>::iterator _floorTextureiter(_vFloorTexture.begin());
    for (; _mapCoordIter != _vMapRenderLocation.end();)
    {
        if (_mapCoordIter->x > camera.x - 200 && _mapCoordIter->y > camera.y - 200 && _mapCoordIter->x < camera.x + 800 && _mapCoordIter->y < camera.y + 600)
        {
            if (*_floorTileIter == 2 || *_floorTileIter == 3 || *_floorTileIter == 4 || *_floorTileIter == 5)
            {
                _floorTextureiter->update(index);
            }
        }

        ++_mapCoordIter;
        ++_floorTileIter;
        ++_floorTextureiter;
    }

    if (index >= 9)
    {
        index = 0;
        count = 0;
    }

    _pSelected = ObjectCoordCal(_realCursor);
    _pTestSelect = ObjectCoordCal2(_realCursor);
}

void TileManager::MapSetting(enum TileImage tileImg)
{
    _setTileImage = tileImg;
}

void TileManager::SetWorldSize(int worldX, int worldY)
{
    _pWorldSize.x = worldX;
    _pWorldSize.y = worldY;

    SetOrigin();
}


//tile Origin setting
void TileManager::SetOrigin(void)
{
    _pOrigin.x = _pWorldSize.y / 2;
    _pOrigin.y = 1;
}


//draw TileMap
void TileManager::DrawWorld(HDC hdc)
{
    int temp = 0;

    if (_tileTexture != nullptr)
    {
        for (Point2D Coord : _vMapRenderLocation)
        {
            if (Coord.x > _camera.x - 200 && Coord.y > _camera.y - 200 && Coord.x < _camera.x + 800 && Coord.y < _camera.y + 600)
            {
                DrawFloor(hdc, Coord.x - _camera.x, Coord.y - _camera.y, temp);
                DrawTile(hdc, Coord.x - _camera.x, Coord.y - _camera.y, temp);
                DrawWall(hdc, Coord.x - _camera.x, Coord.y - _camera.y, temp);
            }
            temp++;
        }
    }

    char test[256];
    sprintf_s(test, "x : (%d, %d)", _pSelected.x, _pSelected.y);
    TextOut(hdc, 0, 20, test, strlen(test));
    char test2[256];
    sprintf_s(test2, "Q : 이전 E : 다음");
    TextOut(hdc, 0, 40, test2, strlen(test2));
    char test6[256];
    sprintf_s(test6, "방향키 : 카메라 움직임");
    TextOut(hdc, 0, 60, test6, strlen(test6));
    char test3[256];
    sprintf_s(test3, "F1 : 타일 F2: 벽 F3: 투명벽 F4: 바닥");
    TextOut(hdc, 0, 80, test3, strlen(test3));
    char test4[256];
    sprintf_s(test4, "F5 ~ F8 : 타일 종류 변경");
    TextOut(hdc, 0, 100, test4, strlen(test4));
    char test5[256];
    sprintf_s(test5, "F12 : 메인메뉴");
    TextOut(hdc, 0, 120, test5, strlen(test5));
}

void TileManager::DrawAlphaWall(HDC hdc, int playerLocationX)
{
    int temp = 0;

    if (_tileTexture != nullptr)
    {
        for (Point2D Coord : _vMapRenderLocation)
        {
            if (Coord.x > _camera.x - 200 && Coord.y > _camera.y - 200 && Coord.x < _camera.x + 800 && Coord.y < _camera.y + 700)
            {
                DrawAlphaWall(hdc, Coord.x - _camera.x, Coord.y - _camera.y, temp, playerLocationX);
            }
            temp++;
        }
    }
}

Point2D TileManager::ObjectCoordCal(Point2D Location)
{
    Point2D coord;
    Point2D _pCell = Point2D(Location.x / TILE_WIDTH, Location.y / TILE_HEIGHT);

    coord = Point2D(
        (_pCell.y - TILEMANAGER->getOrigin().y) + (_pCell.x - TILEMANAGER->getOrigin().x),
        (_pCell.y - TILEMANAGER->getOrigin().y) - (_pCell.x - TILEMANAGER->getOrigin().x));
    
    COLORREF color = GetPixel(_tileTexture->getImg()->getMemDC(), Location.x % TILE_WIDTH, Location.y % TILE_HEIGHT);

    int r = GetRValue(color);
    int g = GetGValue(color);
    int b = GetBValue(color);

    if (r == 255 && g == 0 && b == 0)
    {
        coord += Point2D(-1, 0);
    }
    else if (r == 0 && g == 0 && b == 255)
    {
        coord += Point2D(0, -1);
    }
    else if (r == 0 && g == 255 && b == 0)
    {
        coord += Point2D(0, 1);
    }
    else if (r == 255 && g == 255 && b == 0)
    {
        coord += Point2D(1, 0);
    }
    
    return coord;
}

Point2D TileManager::ObjectCoordCal2(Point2D location)
{
    Point2D coord;

    Point2D isomaticMatrixX = Point2D( TILE_WIDTH, TILE_HEIGHT);
    Point2D isomaticMatrixY = Point2D(-TILE_WIDTH, TILE_HEIGHT);

    float a = 0.5f * isomaticMatrixX.x;
    float b = 0.5f * isomaticMatrixY.x;
    float c = 0.5f * isomaticMatrixX.y;
    float d = 0.5f * isomaticMatrixY.y;

    double determinant = a * d - b * c;
    double inverseDet = 1.0f / determinant;

    double invA = inverseDet * d;
    double invB = inverseDet * -b;
    double invC = inverseDet * -c;
    double invD = inverseDet * a;

    coord = Point2D(location.x * invA + location.y * invB, location.x * invC + location.y * invD);

    return coord;
} 

void TileManager::setTileY(int index)
{
    _tileIndexY = index * 2;
}



void TileManager::InsertWorldInfo(void)
{
    int index = 0;
    for (int wy = 0; wy < _pWorldSize.y; wy++)
    {
        for (int wx = 0; wx < _pWorldSize.x; wx++)
        {
            InsertTileInfo(_vTileMap[index]);
            InsertWallInfo(_vWallMap[index]);
            InsertAlphaWallInfo(_vAlphaWallMap[index]);
            InsertFloorInfo(_vFloorMap[index]);

            _vNode.push_back(Node(0, 0, index));
            index++;
        }
    }
}

//TILE

void TileManager::TileImageChange(void)
{
    if (KEYMANAGER->isStayKeyDown(VK_F5))
    {
        _setTileImage = TechTile;
    }
    if (KEYMANAGER->isStayKeyDown(VK_F6))
    {
        _setTileImage = EnemyTile;
    }
    if (KEYMANAGER->isStayKeyDown(VK_F7))
    {
        _setTileImage = BossTile;
    }
    if (KEYMANAGER->isStayKeyDown(VK_F8))
    {
        _setTileImage = TestTile;
    }

    switch (_setTileImage)
    {
    case TechTile:
        _setTile = _tileTexture->getImg2();
        break;
    case EnemyTile:
        _setTile = _tileTexture->getImg();
        break;
    case BossTile:
        _setTile = _tileTexture->getBossTile();
        break;
    case TestTile:
        _setTile = _tileTexture->getImg();
        break;
    }
}

//tileTexture insert to tileMap
void TileManager::InputTileImage(int texture, int mapPosition)
{
    _vTileMap.erase(_vTileMap.begin() + mapPosition);
    _vTileMap.insert(_vTileMap.begin() + mapPosition, texture);
    _vTileTexture.erase(_vTileTexture.begin() + mapPosition);
    _vTileTexture.insert(_vTileTexture.begin() + mapPosition, _vTileMap[mapPosition]);
}

//imageTexture informantion insert to Tile.h
void TileManager::InsertTileInfo(int index)
{
    _vTileTexture.push_back(TileTexture(index));
}

//tileTexture pushBack to tileMap
void TileManager::PushBackTileImage(int index)
{
    _vTileMap.push_back(index);
}

void TileManager::SelectTileMake(void)
{
    int temp = 0;
    for (int x = 1; x < 3; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            _selectTileRect[temp] = RectMake(WINSIZE_X - (x * TILE_WIDTH), y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
            temp++;
        }
    }
}



//WALL
void TileManager::InputWallImage(int texture, int mapPosition)
{
    _vWallMap.erase(_vWallMap.begin() + mapPosition);
    _vWallMap.insert(_vWallMap.begin() + mapPosition, texture);
    _vWallTexture.erase(_vWallTexture.begin() + mapPosition);
    _vWallTexture.insert(_vWallTexture.begin() + mapPosition, _vWallMap[mapPosition]);
}

void TileManager::InsertWallInfo(int index)
{
    _vWallTexture.push_back(WallTexture(index));
}

void TileManager::PushBackWallImage(int index)
{
    _vWallMap.push_back(index);
}

void TileManager::SelectWallMake(void)
{
    int temp = 0;
    for (int x = 1; x < 3; x++)
    {
            _selectWallRect[temp] = RectMake(WINSIZE_X - (x * TILE_WIDTH), 0, TILE_WIDTH, WALL_HEIGHT);
            temp++;
    }
}



//ALPHA WALL
void TileManager::InputAlphaWallImage(int texture, int mapPosition)
{
    _vAlphaWallMap.erase(_vAlphaWallMap.begin() + mapPosition);
    _vAlphaWallMap.insert(_vAlphaWallMap.begin() + mapPosition, texture);
    _vAlphaWallTexture.erase(_vAlphaWallTexture.begin() + mapPosition);
    _vAlphaWallTexture.insert(_vAlphaWallTexture.begin() + mapPosition, _vAlphaWallMap[mapPosition]);
}

void TileManager::InsertAlphaWallInfo(int index)
{
    _vAlphaWallTexture.push_back(AlphaWallTexture(index));
}

void TileManager::PushBackAlphaWallImage(int index)
{
    _vAlphaWallMap.push_back(index);
}

void TileManager::SelectAlphaWallMake(void)
{
    int temp = 0;
    for (int x = 1; x < 3; x++)
    {
        _selectAlphaWallRect[temp] = RectMake(WINSIZE_X - (x * TILE_WIDTH), 0, TILE_WIDTH, WALL_HEIGHT);
        temp++;
    }
}


void TileManager::InputAlphaWall2Image(int texture, int mapPosition)
{
    _vAlphaWallMap2.erase(_vAlphaWallMap2.begin() + mapPosition);
    _vAlphaWallMap2.insert(_vAlphaWallMap2.begin() + mapPosition, texture);
    _vAlphaWallTexture2.erase(_vAlphaWallTexture2.begin() + mapPosition);
    _vAlphaWallTexture2.insert(_vAlphaWallTexture2.begin() + mapPosition, _vAlphaWallMap2[mapPosition]);
}

void TileManager::InsertAlphaWall2Info(int index)
{
    _vAlphaWallTexture2.push_back(AlphaWallTexture(index));
}

void TileManager::PushBackAlphaWall2Image(int index)
{
    _vAlphaWallMap2.push_back(index);
}

void TileManager::SelectAlphaWall2Make(void)
{
    int temp = 0;
    for (int x = 1; x < 3; x++)
    {
        _selectAlphaWallRect2[temp] = RectMake(WINSIZE_X - (x * TILE_WIDTH), 0, TILE_WIDTH, WALL_HEIGHT);
        temp++;
    }
}



//FLOOR
void TileManager::InputFloorImage(int texture, int mapPosition)
{
    _vFloorMap.erase(_vFloorMap.begin() + mapPosition);
    _vFloorMap.insert(_vFloorMap.begin() + mapPosition, texture);
    _vFloorTexture.erase(_vFloorTexture.begin() + mapPosition);
    _vFloorTexture.insert(_vFloorTexture.begin() + mapPosition, _vFloorMap[mapPosition]);
}

void TileManager::InsertFloorInfo(int index)
{
    _vFloorTexture.push_back(FloorTexture(index));
}

void TileManager::PushBackFloorImage(int index)
{
    _vFloorMap.push_back(index);
}

void TileManager::SelectFloorMake(void)
{
    int temp = 0;
    switch (_setTileImage)
    {
    case TechTile:
        for (int x = 1; x < 3; x++)
        {
            _selectFloorRect[temp] = RectMake(WINSIZE_X - (x * TILE_WIDTH), 0, TILE_WIDTH, FLOOR_HEIGHT);
            temp++;
        }
        break;
    case BossTile:
        for (int x = 1; x < 3; x++)
        {
            for (int y = 0; y < 9; y++)
            {
                _selectFloorLavaRect[temp] = RectMake(WINSIZE_X - (x * TILE_WIDTH), y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
                temp++;
            }
        }
        break;
    }
}



//MAP TILE DRAW

void TileManager::DrawTile(HDC hdc, int x, int y, int index)
{
    if (_vTileMap[index] > 1)
    {
        _vTileTexture[index].DrawTile(hdc, x, y, _setTileImage);
    }

}

void TileManager::DrawWall(HDC hdc, int x, int y, int index)
{
    if (_vWallMap[index] > 1 )
    {
        _vWallTexture[index].DrawWall(hdc, x, y, _setTileImage);
    }

}

void TileManager::DrawAlphaWall(HDC hdc, int x, int y, int index, int playerX)
{
    int alpha2;
    if (_vAlphaWallMap[index] > 1)
    {
        if (playerX < (index % _pWorldSize.x))
        {
            alpha2 = 150;
        }
        else
            alpha2 = 255;

        _vAlphaWallTexture[index].DrawAlphaWall(hdc, x, y, alpha2);

    }
}

void TileManager::DrawAlphaWall2(HDC hdc, int x, int y, int index)
{
    int alpha2;
    if (_vAlphaWallMap[index] > 1)
    {
        if (_pSelected.x < (index % _pWorldSize.x))
        {
            alpha2 = 150;
        }
        else
            alpha2 = 255;

        _vAlphaWallTexture[index].DrawAlphaWall(hdc, x, y, alpha2);

    }
}

void TileManager::DrawFloor(HDC hdc, int x, int y, int index)
{
    switch (_setTileImage)
    {
    case TechTile:
        if (_vFloorMap[index] != 1)
        {
            _vFloorTexture[index].DrawFloor(hdc, x, y);
        }
        break;
    case BossTile:
        if (_vFloorMap[index] == 0)
        {
            _vFloorTexture[index].DrawTempLava(hdc, x, y);
        }
        else if (_vFloorMap[index] == 2)
        {
            _vFloorTexture[index].DrawLava(hdc, x, y);
        }
        else if (_vFloorMap[index] == 3)
        {
            _vFloorTexture[index].DrawLava2(hdc, x, y);
        }
        else if (_vFloorMap[index] == 4)
        {
            _vFloorTexture[index].DrawLava3(hdc, x, y);
        }
        else if (_vFloorMap[index] == 5)
        {
            _vFloorTexture[index].DrawLava4(hdc, x, y);
        }

        break;
    default:

        break;
    }
}




//MAP TOOL FUNCTION

void TileManager::DefaultMapSetting(int worldX, int worldY)
{
    _pWorldSize.x = worldX;
    _pWorldSize.y = worldY;

    for (int wy = 0; wy < worldY; wy++)
    {
        for (int wx = 0; wx < worldX; wx++)
        {
            PushBackTileImage(0);
            PushBackWallImage(0);
            PushBackAlphaWallImage(1);
            PushBackAlphaWall2Image(0);
            PushBackFloorImage(1);
        }
    }
}

//Default Tile setting
void TileManager::DefaultTile(int worldX, int worldY)
{
    _pWorldSize.x = worldX;
    _pWorldSize.y = worldY;
    
    for (int wy = 0; wy < worldY;  wy++)
    {
        for (int wx = 0; wx < worldX; wx++)
        {
            PushBackTileImage(0);
        }
    }
}

void TileManager::DefaultWall(int worldX, int worldY)
{
    for (int wy = 0; wy < worldY; wy++)
    {
        for (int wx = 0; wx < worldX; wx++)
        {
            PushBackWallImage(0);
        }
    }
}

void TileManager::DefaultAlphaWall(int worldX, int worldY)
{
    for (int wy = 0; wy < worldY; wy++)
    {
        for (int wx = 0; wx < worldX; wx++)
        {
            PushBackAlphaWallImage(1);
        }
    }
}

void TileManager::DefaultAlphaWall2(int worldX, int worldY)
{
    for (int wy = 0; wy < worldY; wy++)
    {
        for (int wx = 0; wx < worldX; wx++)
        {
            PushBackAlphaWall2Image(0);
        }
    }
}

void TileManager::DefaultFloor(int worldX, int worldY)
{
    for (int wy = 0; wy < worldY; wy++)
    {
        for (int wx = 0; wx < worldX; wx++)
        {
            PushBackFloorImage(1);
        }
    }
}

//TILE

//load tile image for insert tile texture
void TileManager::loadTile(HDC hdc)
{
    int temp = 0;

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 2; x++)
        {
            _setTile->render(hdc,
                _selectTileRect[temp].left, _selectTileRect[temp].top,
                (temp % 9) * TILE_WIDTH, (temp / 9 + _tileIndexY) * TILE_HEIGHT,
                TILE_WIDTH, TILE_HEIGHT);
            temp++;
        }
    }
}

void TileManager::SelectTile(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
    {
        for (int i = 0; i < 18; i++)
        {
            if (PtInRect(&_selectTileRect[i], _ptMouse))
            {
                _tileSelected = true;
                _selectTileNum = i + (_tileIndexY * 9);

                break;
            }
        }
    }

    if (KEYMANAGER->isOnceKeyDown(VK_F10))
    {
        _tileSelected = false;
    }
}

void TileManager::SelectTileRender(HDC hdc)
{
    if (_tileSelected)
    {
        _mouseRect = RectMakeCenter(_ptMouse.x, _ptMouse.y, TILE_WIDTH, TILE_HEIGHT);
        _setTile->render(hdc, _mouseRect.left, _mouseRect.top, (_selectTileNum % 9) * TILE_WIDTH, (_selectTileNum / 9) * TILE_HEIGHT,
            TILE_WIDTH, TILE_HEIGHT);
    }
}

void TileManager::TileSelectInput(void)
{
    if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _tileSelected)
    {
        if (_pSelected.x < _pWorldSize.x && _pSelected.y < _pWorldSize.y && _pSelected.x >= 0 && _pSelected.y >= 0)
        {
            InputTileImage(_selectTileNum, _pSelected.x % _pWorldSize.x + _pSelected.y * _pWorldSize.x);
        }
    }
}


//WALL
void TileManager::loadWall(HDC hdc)
{
    int temp = 0;
    if (_setTileImage == TechTile)
    {
        for (int x = 0; x < 2; x++)
        {
            _setWall->render(hdc,
                _selectWallRect[temp].left, _selectWallRect[temp].top,
                ((temp + _tileIndexY) % 10) * TILE_WIDTH, (_tileIndexY / 10) * WALL_HEIGHT,
                TILE_WIDTH, WALL_HEIGHT);
            temp++;
        }
    }
    else if (_setTileImage == BossTile)
    {
        for (int x = 0; x < 2; x++)
        {
            _setWall->render(hdc,
                _selectWallRect[temp].left, _selectWallRect[temp].top,
                ((temp + _tileIndexY) % 10) * TILE_WIDTH, (_tileIndexY / 10) * 480,
                TILE_WIDTH, 480);
            temp++;
        }
    }

}

void TileManager::SelectWall(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
    {
        for (int i = 0; i < 2; i++)
        {
            if (PtInRect(&_selectWallRect[i], _ptMouse))
            {
                _wallSelected = true;
                _selectWallNum = i + _tileIndexY;

                break;
            }
        }
    }

    if (KEYMANAGER->isStayKeyDown(VK_F11))

    {
        _selectWallNum = 0;
    }

    if (KEYMANAGER->isOnceKeyDown(VK_F10))
    {
        _wallSelected = false;
    }
}

void TileManager::SelectWallRender(HDC hdc)
{
    if (_wallSelected)
    {
        if (_setTileImage == TechTile)
        {
            _mouseRect = RectMakeCenter(_ptMouse.x, _ptMouse.y - 160, TILE_WIDTH, WALL_HEIGHT);
            _setWall->render(hdc, _mouseRect.left, _mouseRect.top, (_selectWallNum % 10) * TILE_WIDTH, (_selectWallNum / 10) * WALL_HEIGHT,
                TILE_WIDTH, WALL_HEIGHT);
        }
        else if (_setTileImage == BossTile)
        {
            _mouseRect = RectMakeCenter(_ptMouse.x, _ptMouse.y - 160, TILE_WIDTH, WALL_HEIGHT);
            _setWall->render(hdc, _mouseRect.left, _mouseRect.top, (_selectWallNum % 10) * TILE_WIDTH, (_selectWallNum / 10) * 480,
                TILE_WIDTH, 480);
        }

    }
}

void TileManager::WallSelectInput(void)
{
    if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _wallSelected)
    {
        if (_pSelected.x < _pWorldSize.x && _pSelected.y < _pWorldSize.y && _pSelected.x >= 0 && _pSelected.y >= 0)
        {
            InputWallImage(_selectWallNum, _pSelected.x % _pWorldSize.x + _pSelected.y * _pWorldSize.x);
        }
    }
}

void TileManager::WallImageChange(void)
{
    switch (_setTileImage)
    {
    case TechTile:
        _setWall = _wallTexture->getWall1();
        break;
    case EnemyTile:

        _setWall = _wallTexture->getWall1();
        break;
    case BossTile:
        _setWall = _wallTexture->getDiaWall();
        break;
    case TestTile:

        _setWall = _wallTexture->getWall1();
        break;
    }
}

//ALPHA WALL
void TileManager::loadAlphaWall(HDC hdc)
{
    int temp = 0;

    for (int x = 0; x < 2; x++)
    {
        _alphaWallTexture->getAlphaWall()->render(hdc,
            _selectAlphaWallRect[temp].left, _selectAlphaWallRect[temp].top,
            ((temp + _tileIndexY) % 10) * TILE_WIDTH, (_tileIndexY / 10) * WALL_HEIGHT,
            TILE_WIDTH, WALL_HEIGHT);
        temp++;
    }
}

void TileManager::SelectAlphaWall(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
    {
        for (int i = 0; i < 2; i++)
        {
            if (PtInRect(&_selectAlphaWallRect[i], _ptMouse))
            {
                _alphaWallSelected = true;
                _selectAlphaWallNum = i + _tileIndexY;

                break;
            }
        }
    }

    if (KEYMANAGER->isOnceKeyDown(VK_F10))
    {
        _alphaWallSelected = false;
    }
}

void TileManager::SelectAlphaWallRender(HDC hdc)
{
    if (_alphaWallSelected)
    {
        _mouseRect = RectMakeCenter(_ptMouse.x, _ptMouse.y - 160, TILE_WIDTH, WALL_HEIGHT);
        _alphaWallTexture->getAlphaWall()->render(hdc, _mouseRect.left, _mouseRect.top, (_selectAlphaWallNum % 10) * TILE_WIDTH, (_selectAlphaWallNum / 10) * WALL_HEIGHT,
            TILE_WIDTH, WALL_HEIGHT);
    }
}

void TileManager::alphaWallSelectInput(void)
{
    if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _alphaWallSelected)
    {
        if (_pSelected.x < _pWorldSize.x && _pSelected.y < _pWorldSize.y && _pSelected.x >= 0 && _pSelected.y >= 0)
        {
            InputAlphaWallImage(_selectAlphaWallNum, _pSelected.x % _pWorldSize.x + _pSelected.y * _pWorldSize.x);
        }
    }
}


void TileManager::loadAlphaWall2(HDC hdc)
{
    int temp = 0;

    for (int x = 0; x < 2; x++)
    {
        _alphaWallTexture->getAlphaWall()->render(hdc,
            _selectAlphaWallRect2[temp].left, _selectAlphaWallRect2[temp].top,
            ((temp + _tileIndexY) % 10) * TILE_WIDTH, (_tileIndexY / 10) * WALL_HEIGHT,
            TILE_WIDTH, WALL_HEIGHT);
        temp++;
    }
}

void TileManager::SelectAlphaWall2(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
    {
        for (int i = 0; i < 2; i++)
        {
            if (PtInRect(&_selectAlphaWallRect2[i], _ptMouse))
            {
                _alphaWallSelected2 = true;
                _selectAlphaWallNum2 = i + _tileIndexY;

                break;
            }
        }
    }
}

void TileManager::SelectAlphaWall2Render(HDC hdc)
{
    if (_alphaWallSelected2)
    {
        _mouseRect = RectMakeCenter(_ptMouse.x, _ptMouse.y - 160, TILE_WIDTH, WALL_HEIGHT);
        _alphaWallTexture->getAlphaWall()->render(hdc, _mouseRect.left, _mouseRect.top, (_selectAlphaWallNum2 % 10) * TILE_WIDTH, (_selectAlphaWallNum2 / 10) * WALL_HEIGHT,
            TILE_WIDTH, WALL_HEIGHT);
    }
}

void TileManager::alphaWall2SelectInput(void)
{
    if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _alphaWallSelected2)
    {
        if (_pSelected.x < _pWorldSize.x && _pSelected.y < _pWorldSize.y && _pSelected.x >= 0 && _pSelected.y >= 0)
        {
            InputAlphaWall2Image(_selectAlphaWallNum2, _pSelected.x % _pWorldSize.x + _pSelected.y * _pWorldSize.x);
        }
    }
}


void TileManager::loadFloor(HDC hdc)
{
    int temp = 0;
    switch (_setTileImage)
    {
    case TechTile:
        for (int x = 0; x < 2; x++)
        {
            _floorTexture->getFloor()->render(hdc,
                _selectFloorRect[temp].left, _selectFloorRect[temp].top,
                ((temp + _tileIndexY) % 10) * TILE_WIDTH, (_tileIndexY / 10) * FLOOR_HEIGHT,
                TILE_WIDTH, FLOOR_HEIGHT);
            temp++;
        }
        break;
    case BossTile:
        for (int y = 0; y < 9; y++)
        {
            for (int x = 0; x < 2; x++)
            {
                _floorTexture->getLavaSel()->render(hdc,
                    _selectFloorLavaRect[temp].left, _selectFloorLavaRect[temp].top,
                    (temp % 10) * TILE_WIDTH, 0,
                    TILE_WIDTH, TILE_HEIGHT);
                temp++;
            }
        }
        break;
    }


}

void TileManager::SelectFloor(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
    {
        switch (_setTileImage)
        {
        case TechTile:
            for (int i = 0; i < 2; i++)
            {
                if (PtInRect(&_selectFloorRect[i], _ptMouse))
                {
                    _floorSelected = true;
                    _selectFloorNum = i + _tileIndexY;

                    break;
                }
            }
            break;
        case BossTile:
            for (int i = 0; i < 18; i++)
            {
                if (PtInRect(&_selectFloorLavaRect[i], _ptMouse))
                {
                    _floorSelected = true;
                    _selectFloorNum = i;

                    break;
                }
            }
            break;
        }

    }

    if (KEYMANAGER->isOnceKeyDown(VK_F10))
    {
        _floorSelected = false;
    }
}

void TileManager::SelectFloorRender(HDC hdc)
{
    if (_floorSelected)
    {
        switch (_setTileImage)
        {
        case TechTile:
            _mouseRect = RectMakeCenter(_ptMouse.x, _ptMouse.y + 160, TILE_WIDTH, FLOOR_HEIGHT);
            _floorTexture->getFloor()->render(hdc, _mouseRect.left, _mouseRect.top, (_selectFloorNum % 10) * TILE_WIDTH, (_selectFloorNum / 10) * FLOOR_HEIGHT,
                TILE_WIDTH, FLOOR_HEIGHT);
            break;
        case BossTile:
            _mouseRect = RectMakeCenter(_ptMouse.x, _ptMouse.y, TILE_WIDTH, TILE_HEIGHT);
            _floorTexture->getLavaSel()->render(hdc, _mouseRect.left, _mouseRect.top, (_selectFloorNum % 10) * TILE_WIDTH, 0,
                TILE_WIDTH, TILE_HEIGHT);
            break;
        }

    }
}

void TileManager::floorSelectInput(void)
{
    if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _floorSelected)
    {
        if (_pSelected.x < _pWorldSize.x && _pSelected.y < _pWorldSize.y && _pSelected.x >= 0 && _pSelected.y >= 0)
        {
            InputFloorImage(_selectFloorNum, _pSelected.x % _pWorldSize.x + _pSelected.y * _pWorldSize.x);
        }
    }
}


void TileManager::MapToolUpdate(void)
{

    if (KEYMANAGER->isOnceKeyDown(VK_HOME))
    {
        VilliageMapOutput();
    }

    if (KEYMANAGER->isOnceKeyDown('E'))
    {
        page++;
    }
    if (KEYMANAGER->isOnceKeyDown('Q'))
    {
        page--;
        if (page <= 0) page = 0;
    }

    setTileY(page);

    if (KEYMANAGER->isStayKeyDown(VK_F1))
    {
        _setImageMode = TileEdit;
    }
    if (KEYMANAGER->isStayKeyDown(VK_F2))
    {
        _setImageMode = WallEdit;
    }
    if (KEYMANAGER->isStayKeyDown(VK_F3))
    {
        _setImageMode = AlphaWallEdit;
    }
    if (KEYMANAGER->isStayKeyDown(VK_F4))
    {
        _setImageMode = FloorEdit;
    }

    switch (_setImageMode)
    {
    case TileEdit:
        SelectTileMake();
        SelectTile();
        TileSelectInput();

        TileImageChange();

        break;
    case WallEdit:
        SelectWallMake();
        SelectWall();
        WallSelectInput();

        WallImageChange();
        break;
    case AlphaWallEdit:
        SelectAlphaWallMake();
        SelectAlphaWall();
        alphaWallSelectInput();

        break;
    case FloorEdit:
        SelectFloorMake();
        SelectFloor();
        floorSelectInput();

        break;
    case ObjectEdit:
        break;
    }
}

void TileManager::MapToolRender(HDC hdc)
{
    switch (_setImageMode)
    {
    case TileEdit:
        loadTile(hdc);
        SelectTileRender(hdc);
        break;
    case WallEdit:
        loadWall(hdc);
        SelectWallRender(hdc);
        break;
    case AlphaWallEdit:
        loadAlphaWall(hdc);
        SelectAlphaWallRender(hdc);
        break;
    case FloorEdit:
        loadFloor(hdc);
        SelectFloorRender(hdc);
        break;
    }

}





void TileManager::tileLocationCal(void)
{
    if (_vMapRenderLocation.size() < (_pWorldSize.x * _pWorldSize.y))
    {
        for (int wy = 0; wy < _pWorldSize.y; wy++)
        {
            for (int wx = 0; wx < _pWorldSize.x; wx++)
            {
                _pWorld = Point2D().screenLoca(_pOrigin, wx, wy);
                _vMapRenderLocation.push_back(_pWorld);
            }
        }
    }
}


//                                      DEBUG_LOG
void TileManager::DebugLoca(HDC hdc)
{
    char temp[100];
    wsprintf(temp, "T좌표 : %d, %d", _pSelected.x, _pSelected.y);
    TextOut(hdc, 10, 10, temp, strlen(temp));
    wsprintf(temp, "M좌표: %d, %d", _realCursor.x, _realCursor.y);
    TextOut(hdc, 10, 30, temp, strlen(temp));
    wsprintf(temp, "M좌표2: %d, %d", _pt2dMouse.x, _pt2dMouse.y);
    TextOut(hdc, 10, 50, temp, strlen(temp));
}


//                                      MAP FILE IN/OUT

void TileManager::MapTileOutput(const char* fileName, vector<int> mapVector)
{
    ofstream mapFile;

    mapFile.open(fileName, ios::out | ios::trunc | ios::binary);

    for (auto val : mapVector) {
        mapFile.write(reinterpret_cast<const char*>(&val), sizeof(int));
        if (mapFile.bad()) {
            throw std::runtime_error("Failed to write to Tile File \n");
        }
    }
    printf("Write Tile data to File Complete \n");
}

void TileManager::MapWallOutput(const char* fileName, vector<int> mapVector)
{
    ofstream mapFile;

    mapFile.open(fileName, ios::out | ios::trunc | ios::binary);

    for (auto val : mapVector) {
        mapFile.write(reinterpret_cast<const char*>(&val), sizeof(int));
        if (mapFile.bad()) {
            throw std::runtime_error("Failed to write to WallFile \n");
        }
    }
    printf("Write Wall data to File Complete \n");
}

void TileManager::MapAlphaWallOutput(const char* fileName, vector<int> mapVector)
{
    ofstream mapFile;

    mapFile.open(fileName, ios::out | ios::trunc | ios::binary);

    for (auto val : mapVector) {
        mapFile.write(reinterpret_cast<const char*>(&val), sizeof(int));
        if (mapFile.bad()) {
            throw std::runtime_error("Failed to write to AlphaWallFile \n");
        }
    }
    printf("Write Alpha Wall data to File Complete \n");
}

void TileManager::MapFloorOutput(const char* fileName, vector<int> mapVector)
{
    ofstream mapFile;

    mapFile.open(fileName, ios::out | ios::trunc | ios::binary);

    for (auto val : mapVector) {
        mapFile.write(reinterpret_cast<const char*>(&val), sizeof(int));
        if (mapFile.bad()) {
            throw std::runtime_error("Failed to write to FloorFile \n");
        }
    }
    printf("Write Floor data to File Complete \n");
}


void TileManager::MapTileInput(const char* fileName, vector<int>& mapVector)
{
    ifstream mapFile;
    mapFile.open(fileName, ios::in | ios::binary);

    while (mapFile) {
        int val;
        mapFile.read(reinterpret_cast<char*>(&val), sizeof(int));
        if (mapFile.bad()) {
            throw runtime_error("Failed to read from MapFile \n");
        }
        if (mapFile.eof()) break;
        mapVector.push_back(val);
    }

    printf("Read Tile data Complete \n");
}

void TileManager::MapWallInput(const char* fileName, vector<int>& mapVector)
{
    ifstream mapFile;
    mapFile.open(fileName, ios::in | ios::binary);

    while (mapFile) {
        int val;
        mapFile.read(reinterpret_cast<char*>(&val), sizeof(int));
        if (mapFile.bad()) {
            throw runtime_error("Failed to read from WallFile \n");
        }
        if (mapFile.eof()) break;
        mapVector.push_back(val);
    }

    printf("Read Wall data Complete \n");
}

void TileManager::MapAlphaWallInput(const char* fileName, vector<int>& mapVector)
{
    ifstream mapFile;
    mapFile.open(fileName, ios::in | ios::binary);

    while (mapFile) {
        int val;
        mapFile.read(reinterpret_cast<char*>(&val), sizeof(int));
        if (mapFile.bad()) {
            throw runtime_error("Failed to read from WallFile \n");
        }
        if (mapFile.eof()) break;
        mapVector.push_back(val);
    }

    printf("Read Alpha Wall data Complete \n");
}

void TileManager::MapFloorInput(const char* fileName, vector<int> &mapVector)
{
    ifstream mapFile;
    mapFile.open(fileName, ios::in | ios::binary);

    while (mapFile) {
        int val;
        mapFile.read(reinterpret_cast<char*>(&val), sizeof(int));
        if (mapFile.bad()) {
            throw runtime_error("Failed to read from FloorFile \n");
        }
        if (mapFile.eof()) break;
        mapVector.push_back(val);
    }

    printf("Read Floor data Complete \n");
}



void TileManager::VilliageMapInput(void)
{
    _vTileMap.clear();
    _vWallMap.clear();
    _vAlphaWallMap.clear();
    _vFloorMap.clear();
    _vTileTexture.clear();
    _vWallTexture.clear();
    _vAlphaWallTexture.clear();
    _vFloorTexture.clear();
    _vMapRenderLocation.clear();
    MapTileInput("Resources/Map/VillageTile.bin", _vTileMap);
    MapWallInput("Resources/Map/VillageWall.bin", _vWallMap);
    MapAlphaWallInput("Resources/Map/VillageAlphaWall.bin", _vAlphaWallMap);
    MapFloorInput("Resources/Map/VillageFloor.bin", _vFloorMap);
}

void TileManager::VilliageMapOutput(void)
{

    MapTileOutput("Resources/Map/VillageTile.bin", _vTileMap);
    MapWallOutput("Resources/Map/VillageWall.bin", _vWallMap);
    MapAlphaWallOutput("Resources/Map/VillageAlphaWall.bin", _vAlphaWallMap);
    MapFloorOutput("Resources/Map/VillageFloor.bin", _vFloorMap);
}


void TileManager::HellMapInput(void)
{

}

void TileManager::HellMapOutput(void)
{
}

void TileManager::DiaMapInput(void)
{
    _vTileMap.clear();
    _vWallMap.clear();
    _vAlphaWallMap.clear();
    _vFloorMap.clear();
    _vTileTexture.clear();
    _vWallTexture.clear();
    _vAlphaWallTexture.clear();
    _vFloorTexture.clear();
    _vMapRenderLocation.clear();
    MapTileInput("Resources/Map/DiabloTile.bin", _vTileMap);
    MapWallInput("Resources/Map/DiabloWall.bin", _vWallMap);
    MapAlphaWallInput("Resources/Map/DiabloAlphaWall.bin", _vAlphaWallMap);
    MapFloorInput("Resources/Map/DiabloFloor.bin", _vFloorMap);
}

void TileManager::DiaMapOutput(void)
{
    MapTileOutput("Resources/Map/DiabloTile.bin", _vTileMap);
    MapWallOutput("Resources/Map/DiabloWall.bin", _vWallMap);
    MapAlphaWallOutput("Resources/Map/DiabloAlphaWall.bin", _vAlphaWallMap);
    MapFloorOutput("Resources/Map/DiabloFloor.bin", _vFloorMap);
}

Point2D TileManager::CoordCheck(int x, int y)
{
    Point2D coord;
    Point2D _pCell = Point2D(x / TILE_WIDTH, y / TILE_HEIGHT);

    coord = Point2D(
        (_pCell.y - _pOrigin.y) + (_pCell.x - _pOrigin.x),
        (_pCell.y - _pOrigin.y) - (_pCell.x - _pOrigin.x));
    
    COLORREF color = GetPixel(_tileTexture->getImg()->getMemDC(), x % TILE_WIDTH, y % TILE_HEIGHT);

    int r = GetRValue(color);
    int g = GetGValue(color);
    int b = GetBValue(color);

    if (r == 255 && g == 0 && b == 0)
    {
        coord += Point2D(-1, 0);
    }
    else if (r == 0 && g == 0 && b == 255)
    {
        coord += Point2D(0, -1);
    }
    else if (r == 0 && g == 255 && b == 0)
    {
        coord += Point2D(0, 1);
    }
    else if (r == 255 && g == 255 && b == 0)
    {
        coord += Point2D(1, 0);
    }
    
    return coord;
}

vector<Node*> TileManager::GetNeighbours(Node* node)
{
    vector<Node*> neighbourNodes;
    int worldX = _pWorldSize.x;
    int worldY = _pWorldSize.y;
    int x = node->num % worldX;
    int y = node->num / worldX;
    Point2D center = Point2D(x, y);

    Point2D temp;
    for (int i = -1; i <= 1; ++i)
    {
        for (int k = -1; k <= 1; ++k)
        {
            if (i == 0 && k == 0)
                continue;

            temp = center + Point2D(i, k);

            if (temp.x >= 0 && temp.x < worldX && temp.y >= 0 && temp.y < worldY)
                neighbourNodes.push_back(&_vNode[temp.x + (temp.y * worldX)]);
        }
    }

    return neighbourNodes;
}

int TileManager::GetDistance(Node* a, Node* b)
{
    int ax = a->num % _pWorldSize.x;
    int ay = a->num / _pWorldSize.x;
              
    int bx = b->num % _pWorldSize.x;
    int by = b->num / _pWorldSize.x;

    int dstX = abs(ax - bx);
    int dstY = abs(ay - by);

    if (dstX > dstY)
        return 14 * dstY + 10 * (dstX - dstY);

    return 14 * dstX + 10 * (dstY - dstX);
    
}






          