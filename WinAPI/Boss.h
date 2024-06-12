#pragma once
#include "Enemy.h"
#include "BossSkill.h"

class Player;

enum Action
{
	IDLE, WALK, RUSH, REDHOSE, FLAMECIRCLE, FIRESTORM, DEAD
};

enum Direction
{
	D, LD, L, LU, U, RU, R, RD
};

class Boss :public Enemy
{
private:
	GImage* _idle[9];
	GImage* _walk[9];
	GImage* _shout;
	GImage* _rush[9];
	GImage* _redHose[9];
	GImage* _flameCircle[9];
	GImage* _fireStorm[9];
	GImage* _dead;

	FlameCircle* _FlameCircle;
	RedHose* _redLightningPJ;
	FireStorm* _FireStorm; // ��ü

	// �׽�Ʈ�� ��Ʈ
	RECT _testRc;

	int _actionNum;
	int _count;
	int _frame;
	int _shoutFrame;
	int _rushFrame;
	int _redhoseFrame;
	int _circleFrame;
	int _dieFrame;
	int _fireStormFrame;
	int _actCount;
	int temp;			// ���� ���� �ߺ� ������
	float _hpPercentage;
	float _x, _y;
	float _angle;
	float _angleForSave;
	float _fireStormDistance;

	int _redHoseCount;
	int _fireStormCount;
	bool _redHoseOn;
	bool _fireCircleOn;
	bool _fireStormOn;
	bool _finishAction;
public:
	HRESULT init(void);
	void release(void);
	void update(Player* pl);
	void render(void);

	void move(Player* pl);

	void flameCircle(Player* pl);			// ���� �Ҳ� �߻�
	void redHoseLightning(Player* pl);	// ����ȣ�� �߻�
	void fireStorm(Player* pl);			// ȭ�� ��ǳ �߻�

	RECT getRc(void) { return this->_rc; }
	RECT getHitBox(void) { return this->_hitBox; }

	FlameCircle* getFlameC() { return _FlameCircle; }
	RedHose*  getRedH() { return _redLightningPJ; }
	FireStorm* getFireS() { return _FireStorm; }

	float getX() { return _x; }
	float getY() { return _y; }

	inline void hitDamage(int damage)
	{
		if (_hp <= 0)
		{
			_hp = 0;
			return;
		}
		_hp -= damage;
	}

	int getHp() { return this->_hp; }
	bool getIsDead() { return _isDead; }

	Boss() {}
	~Boss() {}
};
