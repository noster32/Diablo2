#pragma once
#include "SingletonBase.h"
#include "allTexture.h"

#define TILE_WIDTH 160
#define TILE_HEIGHT 80
#define WALL_HEIGHT 459
#define FLOOR_HEIGHT 427

enum TileImage
{
	TechTile, EnemyTile, BossTile, TestTile, WallTile
};

enum ImageEditMode
{
	TileEdit, WallEdit, AlphaWallEdit, FloorEdit, ObjectEdit
};

class TileManager : public SingletonBase <TileManager>
{
private:

	int count, index;

	TileImage _setTileImage;
	ImageEditMode _setImageMode;

	GImage* _setTile;
	GImage* _setWall;

	//World Location
	Point2D _pOrigin;
	Point2D _pWorldSize;
	Point2D _pWorld;

	//Mouse
	Point2D _pt2dMouse;
	Point2D _realCursor;

	Point2D _pSelected;
	Point2D _pTestSelect;
	Point2D _camera;

	int _selectTileNum;
	int _selectWallNum;
	int _selectAlphaWallNum;
	int _selectAlphaWallNum2;
	int _selectFloorNum;
	int _tileIndexY;

	RECT _selectTileRect[18];
	RECT _selectWallRect[2];
	RECT _selectAlphaWallRect[2];
	RECT _selectAlphaWallRect2[2];
	RECT _selectFloorRect[2];
	RECT _selectFloorLavaRect[18];
	RECT _mouseRect;

	TileTexture* _tileTexture;
	WallTexture* _wallTexture;
	AlphaWallTexture* _alphaWallTexture;
	FloorTexture* _floorTexture;

	vector<int> _vTileMap;
	vector<TileTexture> _vTileTexture;

	vector<int> _vWallMap;
	vector<WallTexture> _vWallTexture;

	vector<int> _vAlphaWallMap;
	vector<AlphaWallTexture> _vAlphaWallTexture;

	vector<int> _vAlphaWallMap2;
	vector<AlphaWallTexture> _vAlphaWallTexture2;

	vector<int> _vFloorMap;
	vector<FloorTexture> _vFloorTexture;
	vector<Point2D> _vMapRenderLocation;

	vector<Node> _vNode;

	bool _tileSelected;
	bool _wallSelected;
	bool _alphaWallSelected;
	bool _alphaWallSelected2;
	bool _floorSelected; 

	// <--TILE MAP INFORMATION FUNCTION-->
	void TileImageChange(void);

	void InputTileImage(int texture, int mapPosition);
	void InsertTileInfo(int index);
	void PushBackTileImage(int index);
	void SelectTileMake(void);

	void InputWallImage(int texture, int mapPosition);
	void InsertWallInfo(int index);
	void PushBackWallImage(int index);
	void SelectWallMake(void);


	void InputAlphaWallImage(int texture, int mapPosition);
	void InsertAlphaWallInfo(int index);
	void PushBackAlphaWallImage(int index);
	void SelectAlphaWallMake(void);

	void InputAlphaWall2Image(int texture, int mapPosition);
	void InsertAlphaWall2Info(int index);
	void PushBackAlphaWall2Image(int index);
	void SelectAlphaWall2Make(void);

	void InputFloorImage(int texture, int mapPosition);
	void InsertFloorInfo(int index);
	void PushBackFloorImage(int index);
	void SelectFloorMake(void);

	

	// <-- TILE MAP RENDER FUNCTION -->
	
	void DrawTile(HDC hdc, int x, int y, int index);
	void DrawWall(HDC hdc, int x, int y, int index);
	void DrawAlphaWall(HDC hdc, int x, int y, int index, int playerX);
	void DrawAlphaWall2(HDC hdc, int x, int y, int index);
	void DrawFloor(HDC hdc, int x, int y, int index);
	
	void tileLocationCal(void);
	

	// <-- MAP TOOL FUNCTION -->

	void loadTile(HDC hdc);
	void SelectTile(void);
	void SelectTileRender(HDC hdc);
	void TileSelectInput(void);

	void loadWall(HDC hdc);
	void SelectWall(void);
	void SelectWallRender(HDC hdc);
	void WallSelectInput(void);
	void WallImageChange(void);

	void loadAlphaWall(HDC hdc);
	void SelectAlphaWall(void);
	void SelectAlphaWallRender(HDC hdc);
	void alphaWallSelectInput(void);

	void loadAlphaWall2(HDC hdc);
	void SelectAlphaWall2(void);
	void SelectAlphaWall2Render(HDC hdc);
	void alphaWall2SelectInput(void);

	void loadFloor(HDC hdc);
	void SelectFloor(void);
	void SelectFloorRender(HDC hdc);
	void floorSelectInput(void);


	// <-- MAP FILE I/O -->

	void MapTileOutput(const char* fileName, vector<int> mapVector);
	void MapWallOutput(const char* fileName, vector<int> mapVector);
	void MapAlphaWallOutput(const char* fileName, vector<int> mapVector);
	void MapFloorOutput(const char* fileName, vector<int> mapVector);

	void MapTileInput(const char* fileName, vector<int>& mapVector);
	void MapWallInput(const char* fileName, vector<int>& mapVector);
	void MapAlphaWallInput(const char* fileName, vector<int>& mapVector);
	void MapFloorInput(const char* fileName, vector<int>& mapVector);
	

public:
	HRESULT init(void);
	void release(void);
	void update(Point2D camera);

	void DefaultTile(int worldX, int worldY);
	void DefaultWall(int worldX, int worldY);
	void DefaultAlphaWall(int worldX, int worldY);
	void DefaultAlphaWall2(int worldX, int worldY);
	void DefaultFloor(int worldX, int worldY);

	void InsertWorldInfo(void);
	void SetOrigin(void);

	void setTileY(int index);

	Point2D ObjectCoordCal(Point2D location);

	Point2D ObjectCoordCal2(Point2D Location);

	void SetWorldSize(int worldX, int worldY);

	void MapSetting(enum TileImage tileImg);

	void DrawWorld(HDC hdc);
	void DrawAlphaWall(HDC hdc, int playerLocationX);

	void MapToolUpdate(void);
	void MapToolRender(HDC hdc);

	void DebugLoca(HDC hdc);

	void VilliageMapInput(void);
	void VilliageMapOutput(void);
	void HellMapInput(void);
	void HellMapOutput(void);
	void DiaMapInput(void);
	void DiaMapOutput(void); 

	Point2D CoordCheck(int x, int y);

	vector<Node*> GetNeighbours(Node* center);
	int GetDistance(Node* a, Node* b);

	// GET SET
	Point2D getSelectedTile(void) { return _pSelected; }
	Point2D getWorldSize(void) { return _pWorldSize; }
	Point2D getOrigin(void) { return _pOrigin; }
	Point2D getRealMousePt(void) { return _realCursor; }
	vector<int> getTile(void) { return _vTileMap; }
	vector<int> getWall(void) { return _vWallMap; }
	vector<Node>& getNode(void) { return _vNode; }


	TileManager() {}
	~TileManager() {}
};

