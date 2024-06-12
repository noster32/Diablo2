#pragma once
#include "GameNode.h"
#include "PlayerSkill.h"
#include "PlayerImg.h"
#include "RouteFind.h"

#define MOVE_COUNT		70.0F
#define CAST_COUNT		20.0F
#define CASTING_COUNT	50.0F
#define SHADOW_COUNT	200.0F

class Boss;

enum PLAYERSKILLNAME
{
	NAMEHYDRA		= 0,
	NAMEFROZENORB,
	NAMEMETEOR,
	NAMETELEPORT
};

enum PLAYERMOVENAME
{
	PLAYERIDLE		= 0,
	PLAYERWALK,
	PLAYERCASTING
};

struct PlayerStat
{
	RECT rc;
	RECT hitRC;
	float x, y;
	float endX, endY;
	int shaDirection,direction;
	int hp, mp, atk, def;
	int maxHp, maxMp;
	int str, dex, life, energe; //힘. 민첩, 생명력, 에너지 // 생명력 -> 체력 + 스테미너 , 에너지 -> 마나
	int hpCnt, mpCnt;
	bool isDie;
	float speed;
	bool ismove, isskill, iscasting;
	int shadowIdx, moveIdx, skillIdx, castingIdx;
	int maxcastIdx;
	const char* castingName;
	Point2D coord;
	float angle;
};

class Player : public GameNode
{
private:
	Point2D lastXY;
	float lastX = 0;
	float lastY = 0;
	RouteFind* astar;
	//==============================
	Point2D _camera;
	int _cameraShake;
	int _shakeTime;
	int _currentShakeTime;
	bool _isShake;
	bool _isDiaSummon;
	//------------------------------
	bool _invenOpen;
	bool _statOpen;
	bool _WayOpen;
	bool _isClickMove;
	float _cameraMoveD;
	float _cameraMoveY;
	bool _isAllStop;
	//==============================
	PlayerStat _player;
	float _playerSkillAng;

	PlayerImg* playerImg;
	PLAYERMOVENAME _pmoveName;

	SKILLIMG* skillImg;
	PLAYERSKILLNAME _pskillName;

	float _playerMoveTick;
	float _playerShadTick;
	float _playerSkillTick;
	float _playerCastingTick;

	//==============================
	HYDRA* hydraskill;
	float hydraX;
	float hydraY;

	int hydraSortX[3];
	int hydraSortY[3];

	//==============================
	FROZENORB* frozenorbskill;

	//==============================
	METEOR* meteorskill;


public:
	HRESULT init(void);
	void release(void);
	void update(void);		//마을용
	void update(Boss* dia); //던전용
	void render(bool isVillage);
	//================================================
	PlayerStat getPlayerStat() { return _player; }
	void setPlayerMove(bool move) { _player.ismove = move; }
	void IncreaseHP(int hp) 
	{
		_player.hp += hp; 
		_player.maxHp += hp; 
	}
	void increaseMP(int mp) 
	{
		_player.mp += mp;
		_player.maxMp += mp; 
	}
	void increaseDef(int def) { _player.def += def; }
	//================================================
	void AngleSet6(int idx, float angle);
	void AngleSet16(int idx, float angle);
	void PlayerAngleSet(float angle);
	void PlayerShadowAngSet(float angle);
	//================================================
	inline void hitDamage(int damage)
	{
		_player.hp -= damage;
		if (_player.hp <= 0)
		{
			_player.hp = 0;
			_player.isDie = true;
			return;
		}
	}
	inline void useHpPotion(int potion)
	{
		_player.hp += potion;
		if (_player.hp >= _player.maxHp) _player.hp = _player.maxHp;
	}
	inline void useMpPotion(int potion)
	{
		_player.mp += potion;
		if (_player.mp >= _player.maxMp) _player.mp = _player.maxMp;
	}
	//================================================
	void CShake(void);
	bool getIsDiaSummon() { return _isDiaSummon; }
	//================================================
	Point2D getCamera() { return _camera; }
	void cameraUpdate(void);
	float getPlayerX(void) { return _player.x; }
	float getPlayerY(void) { return _player.y; }
	void setPlayerX(float x) { _player.x = x; }
	void setPlayerY(float y) { _player.y = y; }
	void setPlayerCoord(Point2D pt) { astar->setPlayerCoord(pt); }
	void setCamera(Point2D camera) { _camera = camera; }
	RECT getPlayerHitRc(void) { return _player.hitRC; }
	Point2D getPlayerCoord(void) { return Point2D(_player.x, _player.y); }
	void setPlayerRouteErase() { astar->destinationClear(); astar->MoveToPoint(Point2D(_player.x, _player.y)); }
	void setCameraMoveD(float x) { _cameraMoveD += x; }
	void CameraMoveUpdate(bool waypoint);
	void setIsAllStop(bool s) { _isAllStop = s; }
	//================================================
	void resetCamera();
	void resetRect();
	//================================================
	HYDRA* getHYDRASKILL() { return hydraskill; }
	FROZENORB* getFROZENORBSKILL() { return frozenorbskill; }
	METEOR* getMETEORSKILL() { return meteorskill; }
	//================================================

	Player() {}
	~Player() {}
};

