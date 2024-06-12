#pragma once
#include "GameNode.h"
#include "World.h"
#include "DiabloMap.h"

class testScene : public GameNode
{
private:
	DiabloMap* _dia;
	World* w;

	Point2D _camera;
	Point2D _cameraCenter;
	RECT temp;
	Point2D playerCoord;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void cameraUpdate(void);
	void keyBind(void);
	
	testScene() {}
	~testScene() {}
};

