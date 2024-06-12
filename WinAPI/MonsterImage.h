#pragma once
#include "Animation.h"

class MonsterImage
{
private:
	Animation* _orgeAnim;
	Animation* _ogreMoveAnim;
	Animation* _ogreAttackAnim;
	Animation* _ogreDiedAnim;
	Animation* _ogreGetHitAnim;
	Animation* _orgeAnimShadow;
	Animation* _ogreMoveAnimShadow;
	Animation* _ogreAttackAnimShadow;
	Animation* _ogreDiedAnimShadow;
	Animation* _ogreGetHitAnimShadow;

	GImage* _orge;
	GImage* _orgeMove;
	GImage* _orgeAttack;
	GImage* _orgeDied;
	GImage* _orgeGetHit;
	GImage* _orgeShadow;
	GImage* _orgeMoveShadow;
	GImage* _orgeAttackShadow;
	GImage* _orgeDiedShadow;
	GImage* _orgeGetHitShadow;

	Animation* _balogIdleAnim;
	Animation* _balogMoveAnim;
	Animation* _balogAttackAnim;
	Animation* _balogDiedAnim;
	Animation* _balogGetHitAnim;
	Animation* _balogIdleAnimShadow;
	Animation* _balogMoveAnimShadow;
	Animation* _balogAttackAnimShadow;
	Animation* _balogDiedAnimShadow;
	Animation* _balogGetHitAnimShadow;


	GImage* _balogIdle;
	GImage* _balogMove;
	GImage* _balogAttack;
	GImage* _balogDied;
	GImage* _balogGetHit;
	GImage* _balogIdleShadow;
	GImage* _balogMoveShadow;
	GImage* _balogAttackShadow;
	GImage* _balogDiedShadow;
	GImage* _balogGetHitShadow;

public:
	HRESULT balogInit(void);
	void balogRelease(void);
	void balogUpdate(int animAngle, int state);

	void balogAnim(HDC hdc, int LocationX, int LocationY, int sta);
	void balogIdle(HDC hdc, int LocationX, int LocationY);
	void balogMove(HDC hdc, int LocationX, int LocationY);
	void balogAttack(HDC hdc, int LocationX, int LocationY);
	void balogDied(HDC hdc, int LocationX, int LocationY);
	void balogGetHit(HDC hdc, int LocationX, int LocationY);


	HRESULT orgeInit(void);
	void ogreRelease(void);
	void orgeUpdate(int animAngle, int state);
	
	void orgeAnim(HDC hdc, int LocationX, int LocationY, int sta);
	void orgeIdle(HDC hdc, int LocationX, int LocationY);
	void orgeMove(HDC hdc, int LocationX, int LocationY);
	void orgeAttack(HDC hdc, int LocationX, int LocationY);
	void orgeDied(HDC hdc, int LocationX, int LocationY);
	void orgeGetHit(HDC hdc, int LocationX, int LocationY);

	

	MonsterImage() {}
	~MonsterImage() {}
};

