#pragma once
#include "GameNode.h"
#include "MasterScene.h"

// Resources/Font/kodia.ttf ��Ʈ ���� ���� ��Ź�帳�ϴ�!

class MainGame : public GameNode
{
private:
	MasterScene* _master;

	GameNode* _currentScene;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() : _currentScene(nullptr) {}
	~MainGame() {}
};
