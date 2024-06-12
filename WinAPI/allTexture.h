#pragma once

class TileTexture
{
private:
    GImage* src;
    GImage* techTile;
    GImage* bossTile;
    int sourX, sourY;
    int depth;
public:
    HRESULT init(void);
    void release(void);


    void DrawTile(HDC hdc, int x, int y, int index);

    GImage* getImg() { return src; }
    GImage* getImg2() { return techTile; }
    GImage* getBossTile() { return bossTile; }

    int getSourX() { return sourX; }
    int getSourY() { return sourY; }

    TileTexture() {}
    TileTexture(int index) : sourX(index % 9), sourY(index / 9) {}
};

class WallTexture
{
private:
    GImage* wallTile;
    GImage* diaWallTile;
    int sourX, sourY;
    int depth;
public:
    HRESULT init(void);
    void release(void);

    void DrawWall(HDC hdc, int x, int y, int index);

    GImage* getWall1() { return wallTile; }
    GImage* getDiaWall() { return diaWallTile; }
    int getSourX() { return sourX; }
    int getSourY() { return sourY; }

    WallTexture() {}
    WallTexture(int index) : sourX(index % 10), sourY(index / 10) {}

};

class AlphaWallTexture
{
private:
    GImage* alphaWallTile;
    GImage* alphaWallTile2;
    int sourX, sourY;
public:
    HRESULT init(void);
    void release(void);

    void DrawAlphaWall(HDC hdc, int x, int y, float alpha);
    void DrawAlphaWall2(HDC hdc, int x, int y, float alpha);

    GImage* getAlphaWall() { return alphaWallTile; }
    GImage* getAlphaWall2() { return alphaWallTile2; }
    int getSourX() { return sourX; }
    int getSourY() { return sourY; }

    AlphaWallTexture() {}
    AlphaWallTexture(int index) : sourX(index % 10), sourY(index / 10) {}

};

class FloorTexture
{
private:
    GImage* floorTile;
    GImage* lavaTile;
    GImage* lavaSel;

    int sourX, sourY;
    int tileNum;
public:
    HRESULT init(void);
    void release(void);
    void update(int index);

    void DrawFloor(HDC hdc, int x, int y);
    void DrawLava(HDC hdc, int x, int y);
    void DrawLava2(HDC hdc, int x, int y);
    void DrawLava3(HDC hdc, int x, int y);
    void DrawLava4(HDC hdc, int x, int y);

    void DrawTempLava(HDC hdc, int x, int y);
    GImage* getFloor() { return floorTile; }
    GImage* getLavaSel() { return lavaSel; }
    int getSourX() { return sourX; }
    int getSourY() { return sourY; }

    FloorTexture() {}
    FloorTexture(int index) : sourX(index % 10), sourY(index / 10), tileNum(index) {}
};
