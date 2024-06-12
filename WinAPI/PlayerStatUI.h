#pragma once
#include "GameNode.h"

class Player;

class PlayerStatUI : public GameNode
{
private:
	bool _isStatUI;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(Player* p);


	PlayerStatUI() {}
	~PlayerStatUI() {}
};

