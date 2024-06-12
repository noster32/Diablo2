#pragma once
#include "GameNode.h"
#include "Item.h"

class Inventory;

struct tagShop
{
	GImage* img;
	char* iName;
	char* iType;
	char* info;
	float x, y;
	RECT rc;
	int invenNum;
	int gold;
	bool click;
};

class Shop : public GameNode
{
private:
	RECT _shopCloseButton;
	RECT _shopSpace[2];
	vector<tagShop> _vShop;
	RECT _itemClickR[6];
	bool _openShop; // ÀÎº¥ ¿ÀÇÂ
	bool _hpPotionC;
	bool _mpPotionC;
	bool _hpBuy;
	bool _mpBuy;
	bool _noBuy;
	bool _closeButton;
	bool _shopClick;
	int _count;
	int _countFrame;
	RECT _npcCain;
	int _cainX;
	int _cainY;
	RECT _sClickR[3];
	Item* _item;

public:
	HRESULT init(void);
	void release(void);
	void update(Inventory* inventory);
	void render(void);
	void drawFont(int x, int y, int width, int height, int fontSize, char* str, int r, int g, int b);

	bool getOpenShop() { return _openShop; }
	void setOpenShop(bool openShop) { _openShop = openShop; }
	bool& getHpBuy() { return _hpBuy; }
	void setHpBuy(bool buy) { _hpBuy = buy; }
	bool getMpBuy() { return _mpBuy; }
	void setMpBuy(bool buy) { _mpBuy = buy; }
	bool getSell() { return _noBuy; }
	void setSell(bool noBuy) { _noBuy = noBuy; }

	auto setInvenItem(GImage* img, char* iName, char* iType, char* info,
		float x, float y, RECT rc, int invenNum, int gold, bool click)
	{
		_vShop.push_back({ img, iName, iType, info, x, y, rc, invenNum, gold, click });
	}

	RECT getShopCloseButton() { return _shopCloseButton; }

	Shop() {}
	~Shop() {}
};

