#pragma once
#include "GameNode.h"

class MenuScene : public GameNode
{
private:
	RECT _gameStart;
	RECT _gameQuit;
	RECT _gameMapTool;
	int _logoCnt;
	bool _buttonClick;

	int _StartIdx;
	int _QuitIdx;
	int _MapToolIdx;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MenuScene() {}
	~MenuScene() {}
};

