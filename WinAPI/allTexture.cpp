#include "Stdafx.h"
#include "allTexture.h"

HRESULT TileTexture::init(void)
{
	src = IMAGEMANAGER->addImage("TestTile", "Resources/Images/Tile/testTile.bmp", 800, 1440, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TechTile", "Resources/Images/Tile/techTile.bmp", 1440, 2960, true, RGB(255, 0, 255));
	techTile = IMAGEMANAGER->findImage("TechTile");
	IMAGEMANAGER->addImage("DiaTile", "Resources/Images/Tile/DiabloTile.bmp", 1440, 8320, true, RGB(255, 0, 255));
	bossTile = IMAGEMANAGER->findImage("DiaTile");
	return S_OK;
}

void TileTexture::release(void)
{
}

void TileTexture::DrawTile(HDC hdc, int x, int y, int index)
{
	switch (index)
	{
	case 0:
		IMAGEMANAGER->render("TechTile", hdc, x, y, sourX * 160, sourY * 80, 160, 80);
		break;
	case 1:
		IMAGEMANAGER->render("TestTile", hdc, x, y, sourX * 160, sourY * 80, 160, 80);
		break;
	case 2:
		IMAGEMANAGER->render("DiaTile", hdc, x, y, sourX * 160, sourY * 80, 160, 80);
		break;
	case 3:
		IMAGEMANAGER->render("TestTile", hdc, x, y, sourX * 160, sourY * 80, 160, 80);
		break;
	}
}



HRESULT WallTexture::init(void)
{
	IMAGEMANAGER->addImage("WallTile1", "Resources/Images/Tile/wallTest.bmp", 1600, 3213, true, RGB(255, 0, 255));
	wallTile = IMAGEMANAGER->findImage("WallTile1");
	IMAGEMANAGER->addImage("DiaWall", "Resources/Images/Tile/DiabloWall.bmp", 1600, 2880, true, RGB(255, 0, 255));
	diaWallTile = IMAGEMANAGER->findImage("DiaWall");
	return S_OK;
}

void WallTexture::release(void)
{
}

void WallTexture::DrawWall(HDC hdc, int x, int y, int index)
{
	switch (index)
	{
	case 0:
		IMAGEMANAGER->render("WallTile1", hdc, x, y - 379, sourX * 160, sourY * 459, 160, 459);
		break;
	case 1:
		IMAGEMANAGER->render("TestTile", hdc, x, y, sourX * 160, sourY * 80, 160, 80);
		break;
	case 2:
		IMAGEMANAGER->render("DiaWall", hdc, x, y - 400, sourX * 160, sourY * 480, 160, 480);
		break;
	case 3:
		IMAGEMANAGER->render("TestTile", hdc, x, y, sourX * 160, sourY * 80, 160, 80);
		break;
	}
	
}



HRESULT AlphaWallTexture::init(void)
{
	IMAGEMANAGER->addImage("WallTile2", "Resources/Images/Tile/wallTest2.bmp", 1600, 1377, true, RGB(255, 0, 255));

	alphaWallTile = IMAGEMANAGER->findImage("WallTile2");

	IMAGEMANAGER->addImage("WallTile3", "Resources/Images/Tile/wallTest2.bmp", 1600, 1377, true, RGB(255, 0, 255));

	alphaWallTile2 = IMAGEMANAGER->findImage("WallTile3");

	return S_OK;
}

void AlphaWallTexture::release(void)
{
}

void AlphaWallTexture::DrawAlphaWall(HDC hdc, int x, int y, float alpha)
{
	IMAGEMANAGER->alphaRender("WallTile2", hdc, x, y - 379, sourX * 160, sourY * 459, 160, 459, alpha);
}



HRESULT FloorTexture::init(void)
{
	IMAGEMANAGER->addImage("FloorTile", "Resources/Images/Tile/floorTile.bmp", 1600, 854, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("LavaSel", "Resources/Images/Tile/LavaSelect.bmp", 1600, 80, true, RGB(255, 0, 255));
	floorTile = IMAGEMANAGER->findImage("FloorTile");
	lavaSel = IMAGEMANAGER->findImage("LavaSel");

	IMAGEMANAGER->addFrameImage("Lava", "Resources/Images/Tile/DiabloLava.bmp", 3200, 400, 20, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Lava2", "Resources/Images/Tile/DiabloLava.bmp", 3200, 400, 20, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Lava3", "Resources/Images/Tile/DiabloLava.bmp", 3200, 400, 20, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Lava4", "Resources/Images/Tile/DiabloLava.bmp", 3200, 400, 20, 5, true, RGB(255, 0, 255));
	lavaTile = IMAGEMANAGER->findImage("Lava");

	return S_OK;
}

void FloorTexture::release(void)
{
}

void FloorTexture::update(int index)
{
	if (tileNum == 2)
	{
		IMAGEMANAGER->findImage("Lava")->setFrameY(3);
		IMAGEMANAGER->findImage("Lava")->setFrameX(index);
	}
	else if (tileNum == 3)
	{
		IMAGEMANAGER->findImage("Lava2")->setFrameY(2);
		IMAGEMANAGER->findImage("Lava2")->setFrameX(index);
	}
	else if (tileNum == 4)
	{
		IMAGEMANAGER->findImage("Lava3")->setFrameY(1);
		IMAGEMANAGER->findImage("Lava3")->setFrameX(index);
	}
	else if (tileNum == 5)
	{
		IMAGEMANAGER->findImage("Lava4")->setFrameY(4);
		IMAGEMANAGER->findImage("Lava4")->setFrameX(index);
	}
}

void FloorTexture::DrawFloor(HDC hdc, int x, int y)
{
	IMAGEMANAGER->render("FloorTile", hdc, x, y, sourX * 160, sourY * 427, 160, 427);
}

void FloorTexture::DrawLava(HDC hdc, int x, int y)
{

	IMAGEMANAGER->frameRender("Lava", hdc, x, y);
}

void FloorTexture::DrawLava2(HDC hdc, int x, int y)
{

	IMAGEMANAGER->frameRender("Lava2", hdc, x, y);
}

void FloorTexture::DrawLava3(HDC hdc, int x, int y)
{


	IMAGEMANAGER->frameRender("Lava3", hdc, x, y);
}

void FloorTexture::DrawLava4(HDC hdc, int x, int y)
{


	IMAGEMANAGER->frameRender("Lava4", hdc, x, y);
}


void FloorTexture::DrawTempLava(HDC hdc, int x, int y)
{
	IMAGEMANAGER->render("LavaSel", hdc, x, y, sourX * 160, sourY * 80, 160, 80);
}