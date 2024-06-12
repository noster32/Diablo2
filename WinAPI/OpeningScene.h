#pragma once
#include "GameNode.h"
class OpeningScene : public GameNode
{
private:
	HWND hWndVideo;
	bool openingSkipAnyKey;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	OpeningScene() {}
	~OpeningScene() {}
};

