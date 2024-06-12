#pragma once
#include "GameNode.h"
#define HYDRA_COUNT		200.0f
#define FIREBALL_COUNT	130.0f
#define FROZENORB_COUNT 60.0f
#define ICEBOLT_COUNT	20.0f
#define MTARGET_COUNT	30.0F
#define METEOR_COUNT	50.0F
#define MTFIRE_COUNT    60.0F

struct HydraBullet
{
	RECT rc;
	int radius;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	float speedX;
	float speedY;
	bool fire;
	int hydrafirecnt;
	const char* bulletName;
	bool fireDirect;
	bool hit;
};
struct HydraInfo
{
	RECT _hydrarc;
	float _x;
	float _y;
	bool hydraSummon;
	int bulletNum;
	float hydraAngle;
	const char* hydraPos;
	vector<HydraBullet> bullet;
	float liveTime;
};

struct ICEBOLT
{
	RECT rc;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	float range;
	bool fire;
	const char* name;
	int index;
	bool hit;
};

struct ORB
{
	RECT rc;
	float x, y;
	float fireX, fireY;
	float angle;
	int iceboltFireIdx; //idx마다 아이스볼트 날려라
	int iceboltIdx; //idx 마다 아이스볼트 날리는 판정 상세히 정해줄 변수
	int orbIdx;
};

struct Meteor
{
	float x, y;
	float speedY;
	float speedX;
	float endY;
	bool explosion;
	int idx;
	float MeteorTick;
};

struct MeteorTarget
{
	float x, y;
	int summonMeteorIdx;
	float MeteorTargetTick;
	bool onceSummon;
	int idx;
};

struct MeteorExplosion
{
	RECT rc;
	float x, y;
	int hitTime;
	float FireTick;
	float ExplosionTick;
	bool isExplosion;
	bool isFire;
	bool isFireEnd;
	int idx;
	int fireidx;
};

//=======================================

class SKILLIMG : public GameNode
{
private:
public:
	HRESULT init();

	SKILLIMG() {}
	~SKILLIMG() {}
};

//=======================================
#pragma region 히드라
class HYDRA : public GameNode
{
private:
	vector<HydraInfo> hydra;
	
	float _hydraTick;
	float _hydraBulletTick;
	int hydraIdx;


public:
	HRESULT init();
	void release(void);
	void update(const char* imageName, int idx, Point2D camera);
	void render(const char* imageName, int idx, Point2D camera);

	int getHydraIdx() { return hydraIdx; }
	void setHydraIdx(int idx) { hydraIdx = idx; }

	void setHydraPosition(int idx, float x, float y);

	vector<HydraInfo> getHydraInfo() { return hydra; }
	void setHydraInfo() { hydra.push_back({}); }

	void setHydraAngle(int idx, float angle) { hydra[idx].hydraAngle = angle; }
	void setHydraPos(int idx, const char* imageName) { hydra[idx].hydraPos = imageName; }
	void setSummon(int idx, bool summon) { hydra[idx].hydraSummon = summon; }
	void setLiveTime(int idx, float worldTime) { hydra[idx].liveTime = worldTime; }

	void setHydraFireName(int idx, int bulletIdx, const char* name) { hydra[idx].bullet[bulletIdx].bulletName = name; }
	void setHydraFireDirect(int idx, int bulletIdx, bool dir) { hydra[idx].bullet[bulletIdx].fireDirect = dir; }
	void setHydraFireAngle(int idx, int bulletIdx, float angle) { hydra[idx].bullet[bulletIdx].angle = angle; }
	void setHydraBulletHit(int idx, int bulletIdx, bool hit) { hydra[idx].bullet[bulletIdx].hit = hit; }
	void removeHydra(int arrNum);

	void makebullet(int idx);
	void fire(int idx, float x, float y);
	void draw(int idx, Point2D camera);
	void move(int idx, Point2D camera);

	HYDRA() {}
	~HYDRA() {}
};
#pragma endregion
//=======================================
#pragma region 프로즌오브
class FROZENORB : public GameNode
{
private:
	vector<ORB> _vfrozenOrb;
	vector<ORB>::iterator _vifrozenOrb;

private:
	const char* _iceBoltName[16];

	vector<ICEBOLT> _iceBolt1;
	vector<ICEBOLT> _iceBolt5;
	float _iceboltAngle[16];

	float _frozenOrbTick;
	float _iceBoltTick;
	float _range;
	float _iceBoltRange[16];


public:
	HRESULT init();
	void release(void);
	void update(Point2D camera);
	void render(Point2D camera);

	void makeOrb(float x, float y, float angle);
	void draw(Point2D camera);
	void move(Point2D camera);
	void icebolt(Point2D camera);
	void iceboltrender(Point2D camera);

	vector<ORB> getFrozenOrbInfo() { return _vfrozenOrb; }
	vector<ICEBOLT> getIceBolt1() { return _iceBolt1; }
	vector<ICEBOLT> getIceBolt5() { return _iceBolt5; }
	void setIceBolt1Hit(int idx, bool hit) { _iceBolt1[idx].hit = hit; }
	void setIceBolt5Hit(int idx, bool hit) { _iceBolt5[idx].hit = hit; }

	FROZENORB() {}
	~FROZENORB() {}
};
#pragma endregion
//=======================================
#pragma region 메테오
class METEOR : public GameNode
{
private:
	vector<MeteorTarget> _vMtarget;
	vector<MeteorTarget>::iterator _viMtarget;
	vector<Meteor> _vMeteor;
	vector<Meteor>::iterator _viMeteor;
	vector<MeteorExplosion> _vExplosion;
	vector<MeteorExplosion>::iterator _viExplosion;

public:
	HRESULT init();
	void release(void);
	void update(Point2D camera);
	void render(Point2D camera);

	void summonMeteor(float x, float y, Point2D camera);
	void draw(Point2D camera);
	void move(Point2D camera);

	vector<MeteorExplosion> getExplosion() { return _vExplosion; }

	METEOR() {}
	~METEOR() {}
};
#pragma endregion



