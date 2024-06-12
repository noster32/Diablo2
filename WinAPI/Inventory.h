#pragma once
#include "GameNode.h"

class Player;

struct tagItem
{
	GImage* img;
	char* name;
	char* info;
	float x, y;
	RECT rc;
	int price;
	int	count;

	int hpIncrease;
	int mpIncrease;
	int defendIncrease;

	bool clicked;
	bool used;
	bool atInven;		// ��� ��ġ���ִ��� ���п�
	bool atMiniInven;
	bool atHideInven;
};

struct tagInven
{
	bool occupied;
	RECT rc;
};

class Inventory: public GameNode
{
private:
	RECT _invenCloseButton;
	tagInven _invenSpace[4][10];	// �κ��丮 ������ ��Ʈ
	tagInven _equipSpace[3];		// ��� ������ ��Ʈ
	tagInven _miniInvenSpace[4];
	tagInven _hideInvenSpace[2][4];
	RECT _miniInvenRect;		// ��Ʈ �κ� Ȱ��ȭ üũ��
	vector <tagItem> _vHpPotion;
	vector <tagItem>::iterator _viHpPotion;
	vector <tagItem> _vMpPotion;
	vector <tagItem>::iterator _viMpPotion;
	bool _invenActivation;		// �κ��丮 Ȱ��ȭ ����
	bool _miniInvenActivation;	// ��Ʈ �κ��丮 Ȱ��ȭ ����

	tagItem _wand;
	tagItem _armor1;
	tagItem _armor2;
	tagItem _boots;
	tagItem _gloves;
	tagItem _ring1;
	tagItem _ring2;
	tagItem _tiara;
	tagItem _belt;

	int _gold;
	int _shopGold;
	int _count;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void itemOrganize(void);
	void itemEquip(Player* pl);

	void miniInvenUseItem(void);
	void miniInvenOrganize(void);
	void miniInvenRender(void);

	void hideInvenOrganize(void);
	void hideInvenRender(void);

	bool& getInvenActive(void) { return _invenActivation; }
	bool& getMiniInvActive(void) { return _miniInvenActivation; }
	
	int& getGold() { return _gold; }

	vector <tagItem>::iterator getVHpPotion(void) { return _viHpPotion; }
	vector <tagItem>::iterator getVMpPotion(void) { return _viMpPotion; }

	void getPotion(int i);

	void drawFont(int x, int y, int width, int height, int fontSize, char* str, int r, int g, int b);


	Inventory(){}
	~Inventory() {}
};

