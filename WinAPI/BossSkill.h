#pragma once
#include "GameNode.h"

struct tagProjectile
{
	GImage* img;
	
	RECT rc;
	int radius;
	int count = 0;
	int frameX = 0;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	float fire;
	float bulletDistance;
};

class FlameCircle: public GameNode
{
private:
	vector <tagProjectile> _vProjectile;
	vector <tagProjectile>::iterator _viProjectile;

	const char* _imageName;

	float _range;
	int _amountMax;

	int _count;
	int _frame;
	
public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);

	void initFrame(void) { _frame = 0; }

	void removeBullet(int arrNum);

	vector<tagProjectile> getProjectile(void) { return _vProjectile; }

	FlameCircle(){}
	~FlameCircle() {}
};

class RedHose: public GameNode
{
private:
	vector <tagProjectile> _vProjectile;
	vector <tagProjectile>::iterator _viProjectile;

	const char* _imageName;

	float _range;
	int _amountMax;
public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);

	void removeBullet(int arrNum);
	void setImageName(char* name) { _imageName = name; }

	float _angle;
	vector<tagProjectile> getProjectile(void) { return _vProjectile; }

	RedHose(){}
	~RedHose(){}
};

class FireStorm : public GameNode
{
private:
	vector <tagProjectile> _vProjectile;
	vector <tagProjectile>::iterator _viProjectile;

	const char* _imageName;

	float _range;
	int _amountMax;
	int _count;

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);

	void removeBullet(int arrNum);
	void setImageName(char* name) { _imageName = name; }
	int getMax(void) { return _amountMax; }

	float _x, _y; // fireStorm 초기 시작 위치 저장용 변수
	float _angle; // 각 불줄기마다 각도 부여용
	float _angle2;	
	float _angle3;
	float _angle4;

	vector<tagProjectile> getProjectile(void) { return _vProjectile; }

	FireStorm() {}
	~FireStorm() {}
};

