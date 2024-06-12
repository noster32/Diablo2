#pragma once
#include "GameNode.h"

class Enemy: public GameNode
{
protected:
	int _maxHp;
	int _hp;
	int _atk;
	float _speed;
	bool _isDead;
	RECT _rc;
	RECT _hitBox;
	int _direction;	// 방향 구분용
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Enemy() {};
	~Enemy() {};
};

