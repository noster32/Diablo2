#include "Stdafx.h"
#include "Inventory.h"
#include "Player.h"

HRESULT Inventory::init(void)
{
	IMAGEMANAGER->addImage("Inventory", "Resources/Images/Object/inven.bmp",
		400, 558, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CancelButton", "Resources/Images/Object/cancel_button.bmp", 32, 64, 1, 2);

	IMAGEMANAGER->addImage("hpPotion", "Resources/Images/Object/hpPotion.bmp",
		28, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mpPotion", "Resources/Images/Object/mpPotion.bmp",
		28, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Wand", "Resources/Images/Object/Items/weapon.bmp", 19, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Armor2", "Resources/Images/Object/Items/Armor2.bmp", 90 * 0.6, 119 * 0.7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Boots", "Resources/Images/Object/Items/Boots.bmp", 81 * 0.7, 85 * 0.7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Gloves", "Resources/Images/Object/Items/Gloves.bmp", 96 * 0.7, 90 * 0.7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ring", "Resources/Images/Object/Items/Ring.bmp", 39 * 0.7, 42 * 0.7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Tiara", "Resources/Images/Object/Items/Tiara.bmp", 85 * 0.65, 62 * 0.6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Belt", "Resources/Images/Object/Items/Belt.bmp", 84 * 0.65, 56 * 0.6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MiniInventory", "Resources/Images/Object/invenMini.bmp",
		125, 98, true, RGB(255, 0, 255));

	SOUNDMANAGER->AddSound("potionBuy", "Resources/Sounds/PotionInven.wav")->SetVolume(50);
	SOUNDMANAGER->AddSound("potionUse", "Resources/Sounds/Potion.wav")->SetVolume(50);

	_invenCloseButton = RectMake(417, 447, 30, 30);
	_invenActivation = false;
	_miniInvenActivation = false;
	_count = 0;
	_gold = 1577;
	_shopGold = 10000;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			_invenSpace[i][j].rc = RectMake(418 + j * 29, 320 + i * 29, 25, 25);
		}
	}

	_equipSpace[0].rc = RectMake(493, 240, 25, 25);
	_equipSpace[1].rc = RectMake(607, 240, 25, 25);
	_equipSpace[2].rc = RectMake(650, 241, 50, 50);

	for (int j = 0; j < 4; j++)
	{
		_miniInvenSpace[j].rc = RectMake(424 + j * 31, 564, 25, 25);
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_hideInvenSpace[i][j].rc = RectMake(424 + j * 31, 498 + i * 33, 25, 25);
		}
	}

	_miniInvenRect = RectMake(421, 495, IMAGEMANAGER->findImage("MiniInventory")->getWidth(), IMAGEMANAGER->findImage("MiniInventory")->getHeight());

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			tagItem hpPotion;

			hpPotion.img = IMAGEMANAGER->findImage("hpPotion");
			hpPotion.name = "       Hp포션";
			hpPotion.info = "Hp회복을 위한 포션 ";
			hpPotion.price = 200;
			hpPotion.clicked = false;
			hpPotion.used = false;
			hpPotion.atInven = true;
			hpPotion.atMiniInven = false;
			hpPotion.atHideInven = false;
			hpPotion.count = 0;
			hpPotion.rc = RectMake(_invenSpace[i][j].rc.left, _invenSpace[i][j].rc.top, 30, 30);

			_vHpPotion.push_back(hpPotion);
		}
	}

	for (int i = 2; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			tagItem mpPotion;

			mpPotion.img = IMAGEMANAGER->findImage("mpPotion");
			mpPotion.name = "       Mp포션";
			mpPotion.info = "Mp회복을 위한 포션 ";
			mpPotion.price = 200;
			mpPotion.clicked = false;
			mpPotion.used = false;
			mpPotion.atInven = true;
			mpPotion.atMiniInven = false;
			mpPotion.atHideInven = false;
			mpPotion.rc = RectMake(_invenSpace[i][j].rc.left, _invenSpace[i][j].rc.top, 30, 30);

			_vMpPotion.push_back(mpPotion);
		}
	}

	_wand.clicked = false;
	_wand.img = IMAGEMANAGER->findImage("wand");
	_wand.name = "     이글 오브";
	_wand.info = "    +100체력\n    +100 마나";
	_wand.hpIncrease = 100;
	_wand.mpIncrease = 100;
	_wand.defendIncrease = 0;
	_wand.price = 500;
	_wand.rc = RectMake(435, 139, 50, 70);

	_armor2.clicked = false;
	_armor2.img = IMAGEMANAGER->findImage("Armor2");
	_armor2.name = "     가죽 갑옷";
	_armor2.info = "\n    방어: 100";
	_armor2.hpIncrease = 0;
	_armor2.mpIncrease = 0;
	_armor2.defendIncrease = 100;
	_armor2.price = 100;
	_armor2.rc = RectMake(536, 139, 70, 90);

	_boots.clicked = false;
	_boots.img = IMAGEMANAGER->findImage("Boots");
	_boots.name = "      부츠";
	_boots.info = "\n    방어: 500";
	_boots.hpIncrease = 0;
	_boots.mpIncrease = 0;
	_boots.defendIncrease = 500;
	_boots.price = 50;
	_boots.rc = RectMake(_invenSpace[0][8].rc.left, _invenSpace[0][8].rc.top, 50, 50);

	_ring1.clicked = false;
	_ring1.used = false;
	_ring1.img = IMAGEMANAGER->findImage("Ring");
	_ring1.name = "     반지";
	_ring1.info = "  +500 마나";
	_ring1.hpIncrease = 0;
	_ring1.mpIncrease = 500;
	_ring1.defendIncrease = 0;
	_ring1.price = 50;
	_ring1.rc = RectMake(_invenSpace[0][6].rc.left, _invenSpace[0][6].rc.top, 25, 25);

	_ring2.clicked = false;
	_ring2.used = false;
	_ring2.img = IMAGEMANAGER->findImage("Ring");
	_ring2.name = "     반지";
	_ring2.info = "  +300 체력";
	_ring2.hpIncrease = 300;
	_ring2.mpIncrease = 0;
	_ring2.defendIncrease = 0;
	_ring2.price = 50;
	_ring2.rc = RectMake(_invenSpace[0][5].rc.left, _invenSpace[0][5].rc.top, 25, 25);

	_tiara.clicked = false;
	_tiara.img = IMAGEMANAGER->findImage("Tiara");
	_tiara.name = "     티아라";
	_tiara.info = "   +200 마나";
	_tiara.hpIncrease = 0;
	_tiara.mpIncrease = 200;
	_tiara.defendIncrease = 0;
	_tiara.price = 150;
	_tiara.rc = RectMake(536, 76, 50, 50);

	_gloves.clicked = false;
	_gloves.img = IMAGEMANAGER->findImage("Gloves");
	_gloves.name = "     장갑";
	_gloves.info = "    방어: 50";
	_gloves.hpIncrease = 0;
	_gloves.mpIncrease = 0;
	_gloves.defendIncrease = 0;
	_gloves.price = 100;
	_gloves.rc = RectMake(414, 237, 50, 50);

	_belt.clicked = false;
	_belt.img = IMAGEMANAGER->findImage("Belt");
	_belt.name = "     벨트";
	_belt.info = "  포션을 넣고\n 다닐 수 있다.";
	_belt.hpIncrease = 0;
	_belt.mpIncrease = 0;
	_belt.defendIncrease = 0;
	_belt.price = 60;
	_belt.rc = RectMake(535, 238, 50, 25);

	return S_OK;
}

void Inventory::release(void)
{
}

void Inventory::update(void)
{
	if (PtInRect(&_invenCloseButton, _ptMouse))
	{
		if (_invenActivation && KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_invenActivation = false;
		}
	}
}

void Inventory::render(void)
{
	if (_invenActivation)
	{
		IMAGEMANAGER->render("Inventory", getMemDC(), 400, 0);
		FONTMANAGER->drawText(getMemDC(), 515, 456, "kodia", 17, 20, _gold, RGB(255, 255, 255));

		if (PtInRect(&_invenCloseButton, _ptMouse))
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				IMAGEMANAGER->frameRender("CancelButton", getMemDC(), _invenCloseButton.left + 1, _invenCloseButton.top + 1, 0, 1);
			}
		}

		IMAGEMANAGER->render("Wand", getMemDC(), _wand.rc.left, _wand.rc.top);
		IMAGEMANAGER->render("Armor2", getMemDC(), _armor2.rc.left, _armor2.rc.top);
		if(!_boots.clicked) IMAGEMANAGER->render("Boots", getMemDC(), _boots.rc.left, _boots.rc.top);
		else IMAGEMANAGER->render("Boots", getMemDC(), _ptMouse.x - 20, _ptMouse.y - 20);
		if (!_ring1.clicked) IMAGEMANAGER->render("Ring", getMemDC(), _ring1.rc.left, _ring1.rc.top);
		else  IMAGEMANAGER->render("Ring", getMemDC(), _ptMouse.x - 10, _ptMouse.y - 10);
		if (!_ring2.clicked) IMAGEMANAGER->render("Ring", getMemDC(), _ring2.rc.left, _ring2.rc.top);
		else  IMAGEMANAGER->render("Ring", getMemDC(), _ptMouse.x - 10, _ptMouse.y - 10);
		IMAGEMANAGER->render("Tiara", getMemDC(), _tiara.rc.left, _tiara.rc.top);
		IMAGEMANAGER->render("Gloves", getMemDC(), _gloves.rc.left, _gloves.rc.top);
		IMAGEMANAGER->render("Belt", getMemDC(), _belt.rc.left, _belt.rc.top);

		// 포션 설명창 출력
		for (_viHpPotion = _vHpPotion.begin(); _viHpPotion != _vHpPotion.end(); ++_viHpPotion)
		{
			if (_viHpPotion->atInven)
			{
				if (!_viHpPotion->clicked)		_viHpPotion->img->render(getMemDC(), _viHpPotion->rc.left, _viHpPotion->rc.top);
				if (PtInRect(&_viHpPotion->rc, _ptMouse) && !_viHpPotion->clicked)
				{
					drawFont(_viHpPotion->rc.right - 80, _viHpPotion->rc.top - 40, 130, 20, 15, _viHpPotion->name, 255, 255, 255);
					drawFont(_viHpPotion->rc.right - 80, _viHpPotion->rc.top - 20, 130, 20, 15, _viHpPotion->info, 255, 255, 255);
				}
			}
		}

		for (_viMpPotion = _vMpPotion.begin(); _viMpPotion != _vMpPotion.end(); ++_viMpPotion)
		{
			if (_viMpPotion->atInven)
			{
				if (!_viMpPotion->clicked)	_viMpPotion->img->render(getMemDC(), _viMpPotion->rc.left, _viMpPotion->rc.top);
				if (PtInRect(&_viMpPotion->rc, _ptMouse) && !_viMpPotion->clicked)
				{
					drawFont(_viMpPotion->rc.right - 80, _viMpPotion->rc.top - 40, 130, 20, 15, _viMpPotion->name, 255, 255, 255);
					drawFont(_viMpPotion->rc.right - 80, _viMpPotion->rc.top - 20, 130, 20, 15, _viMpPotion->info, 255, 255, 255);
				}
			}
		}

		// 아이템 설명창 출력
		if (PtInRect(&_wand.rc, _ptMouse) && !_wand.clicked)
		{
			drawFont(_wand.rc.right - 100, _wand.rc.bottom + 16, 120, 20, 15, _wand.name, 255, 255, 255);
			drawFont(_wand.rc.right - 100, _wand.rc.bottom + 36, 120, 40, 15, _wand.info, 255, 255, 255);
		}
		if (PtInRect(&_armor2.rc, _ptMouse) && !_armor2.clicked)
		{
			drawFont(_armor2.rc.left - 32, _armor2.rc.bottom, 120, 20, 15, _armor2.name, 255, 255, 255);
			drawFont(_armor2.rc.left - 32, _armor2.rc.bottom + 20, 120, 40, 15, _armor2.info, 255, 255, 255);
		}
		if (PtInRect(&_boots.rc, _ptMouse) && !_boots.clicked)
		{
			drawFont(_boots.rc.left - 22, _boots.rc.bottom, 105, 20, 15, _boots.name, 255, 255, 255);
			drawFont(_boots.rc.left - 22, _boots.rc.bottom + 20, 105, 40, 15, _boots.info, 255, 255, 255);
		}
		if (PtInRect(&_ring1.rc, _ptMouse) && !_ring1.clicked)
		{
			drawFont(_ring1.rc.left - 32, _ring1.rc.bottom, 90, 20, 15, _ring1.name, 255, 255, 255);
			drawFont(_ring1.rc.left - 32, _ring1.rc.bottom + 20, 90, 20, 15, _ring1.info, 255, 255, 255);
		}
		if (PtInRect(&_ring2.rc, _ptMouse) && !_ring2.clicked)
		{
			drawFont(_ring2.rc.left - 32, _ring2.rc.bottom, 90, 20, 15, _ring2.name, 255, 255, 255);
			drawFont(_ring2.rc.left - 32, _ring2.rc.bottom + 20, 90, 20, 15, _ring2.info, 255, 255, 255);
		}
		if (PtInRect(&_tiara.rc, _ptMouse) && !_tiara.clicked)
		{
			drawFont(_tiara.rc.left - 22, _tiara.rc.bottom, 105, 20, 15, _tiara.name, 255, 255, 255);
			drawFont(_tiara.rc.left - 22, _tiara.rc.bottom + 20, 105, 20, 15, _tiara.info, 255, 255, 255);
		}
		if (PtInRect(&_gloves.rc, _ptMouse) && !_gloves.clicked)
		{
			drawFont(_gloves.rc.left - 22, _gloves.rc.bottom + 5, 105, 20, 15, _gloves.name, 255, 255, 255);
			drawFont(_gloves.rc.left - 22, _gloves.rc.bottom + 25, 105, 20, 15, _gloves.info, 255, 255, 255);
		}
		if (PtInRect(&_belt.rc, _ptMouse) && !_belt.clicked)
		{
			drawFont(_belt.rc.left - 22, _belt.rc.bottom + 5, 100, 20, 15, _belt.name, 255, 255, 255);
			drawFont(_belt.rc.left - 22, _belt.rc.bottom + 25, 100, 40, 15, _belt.info, 255, 255, 255);
		}
	}
}

void Inventory::itemOrganize(void)
{
	for (_viHpPotion = _vHpPotion.begin(); _viHpPotion != _vHpPotion.end(); ++_viHpPotion)
	{
		if (PtInRect(&_viHpPotion->rc, _ptMouse) && !_viHpPotion->clicked && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_viHpPotion->clicked = true;
			SOUNDMANAGER->FindSound("potionBuy")->Play(0);
		}
		else if (_viHpPotion->clicked)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (PtInRect(&_invenSpace[i][j].rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_viHpPotion->clicked = false;
						_viHpPotion->atInven = true;
						_viHpPotion->atMiniInven = false;
						_viHpPotion->atHideInven = false;
						_viHpPotion->rc = RectMake(_invenSpace[i][j].rc.left, _invenSpace[i][j].rc.top, 30, 30);
						SOUNDMANAGER->FindSound("potionBuy")->Play(0);
					}
				}
			}
		}
	}

	for (_viMpPotion = _vMpPotion.begin(); _viMpPotion != _vMpPotion.end(); ++_viMpPotion)
	{
		for (_viHpPotion = _vHpPotion.begin(); _viHpPotion != _vHpPotion.end(); ++_viHpPotion)
		{
			if (_viHpPotion->rc.left == _viMpPotion->rc.left && _viHpPotion->rc.top == _viMpPotion->rc.top)
			{
				if (!_viMpPotion->clicked && !_viHpPotion->clicked)	_viMpPotion->clicked = true;
			}
		}
	}

	for (_viHpPotion = _vHpPotion.begin(); _viHpPotion != _vHpPotion.end(); ++_viHpPotion)
	{
		for (_viMpPotion = _vMpPotion.begin(); _viMpPotion != _vMpPotion.end(); ++_viMpPotion)
		{
			if (_viHpPotion->rc.left == _viMpPotion->rc.left && _viHpPotion->rc.top == _viMpPotion->rc.top)
			{
				if (!_viMpPotion->clicked && !_viHpPotion->clicked)  _viHpPotion->clicked = true;
			}
		}
	}

	for (_viMpPotion = _vMpPotion.begin(); _viMpPotion != _vMpPotion.end(); ++_viMpPotion)
	{
		if (PtInRect(&_viMpPotion->rc, _ptMouse) && !_viMpPotion->clicked && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_viMpPotion->clicked = true;
			SOUNDMANAGER->FindSound("potionBuy")->Play(0);
		}
		if (_viMpPotion->clicked)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (PtInRect(&_invenSpace[i][j].rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_viMpPotion->clicked = false;
						_viMpPotion->atInven = true;
						_viMpPotion->atMiniInven = false;
						_viMpPotion->atHideInven = false;
						_viMpPotion->rc = RectMake(_invenSpace[i][j].rc.left, _invenSpace[i][j].rc.top, 30, 30);
						SOUNDMANAGER->FindSound("potionBuy")->Play(0);
						
					}
				}
			}
		}
	}

	// 공간 점유 여부 체크
	for (_viHpPotion = _vHpPotion.begin(); _viHpPotion != _vHpPotion.end(); ++_viHpPotion)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (_viHpPotion->rc.left == _invenSpace[i][j].rc.left && _viHpPotion->rc.top == _invenSpace[i][j].rc.top)
				{
					_invenSpace[i][j].occupied = true;
				}
			}
		}
	}

	for (_viMpPotion = _vMpPotion.begin(); _viMpPotion != _vMpPotion.end(); ++_viMpPotion)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (_viMpPotion->rc.left == _invenSpace[i][j].rc.left && _viMpPotion->rc.top == _invenSpace[i][j].rc.top)
				{
					_invenSpace[i][j].occupied = true;
				}
			}
		}
	}

	// 아이템 이동
	if (PtInRect(&_boots.rc, _ptMouse) && !_boots.clicked && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_boots.clicked = true;
	}
	if (_boots.clicked && PtInRect(&_equipSpace[2].rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_boots.clicked = false;
		_boots.used = true;
		_boots.rc = RectMake(_equipSpace[2].rc.left, _equipSpace[2].rc.top, 50, 50);
	}


	if (PtInRect(&_ring1.rc, _ptMouse) && !_ring1.clicked && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_ring1.clicked = true;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (_ring1.clicked && PtInRect(&_invenSpace[i][j].rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_ring1.clicked = false;
				_ring1.rc = RectMake(_invenSpace[i][j].rc.left, _invenSpace[i][j].rc.top, 25, 25);
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (_ring1.clicked && PtInRect(&_equipSpace[i].rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_ring1.clicked = false;
			_ring1.used = true;
			_ring1.rc = RectMake(_equipSpace[i].rc.left, _equipSpace[i].rc.top, 25, 25);
		}
	}

	if (PtInRect(&_ring2.rc, _ptMouse) && !_ring2.clicked && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_ring2.clicked = true;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (_ring2.clicked && PtInRect(&_invenSpace[i][j].rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_ring2.clicked = false;				
				_ring2.rc = RectMake(_invenSpace[i][j].rc.left, _invenSpace[i][j].rc.top, 25, 25);
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (_ring2.clicked && PtInRect(&_equipSpace[i].rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_ring2.clicked = false;
			_ring2.used = true;
			_ring2.rc = RectMake(_equipSpace[i].rc.left, _equipSpace[i].rc.top, 25, 25);
		}
	}
}

void Inventory::itemEquip(Player* pl)
{
	if (_boots.used)
	{
		// 스탯 가져와서 증가시킨다
		pl->increaseDef(500);
		_boots.used = false;
	}

	if (_ring1.used)
	{
		pl->increaseMP(500);
		_ring1.used = false;
	}

	if (_ring2.used)
	{
		pl->IncreaseHP(300);
		_ring2.used = false;
	}
}

void Inventory::miniInvenUseItem(void)
{
	_count++;

	//Hp포션 사용
	for (_viHpPotion = _vHpPotion.begin(); _viHpPotion != _vHpPotion.end(); ++_viHpPotion)
	{
		if (_viHpPotion->atMiniInven && _viHpPotion->rc.left == _miniInvenSpace[0].rc.left && !_viHpPotion->used && KEYMANAGER->isOnceKeyDown('1'))
		{
			_viHpPotion->used = true;
			SOUNDMANAGER->FindSound("potionUse")->Play(0);
		}
		else if (_viHpPotion->atMiniInven && _viHpPotion->rc.left == _miniInvenSpace[1].rc.left && !_viHpPotion->used && KEYMANAGER->isOnceKeyDown('2'))
		{
			_viHpPotion->used = true;
			SOUNDMANAGER->FindSound("potionUse")->Play(0);
		}
		else if (_viHpPotion->atMiniInven && _viHpPotion->rc.left == _miniInvenSpace[2].rc.left && !_viHpPotion->used && KEYMANAGER->isOnceKeyDown('3'))
		{
			_viHpPotion->used = true;
			SOUNDMANAGER->FindSound("potionUse")->Play(0);
		}
		else if (_viHpPotion->atMiniInven && _viHpPotion->rc.left == _miniInvenSpace[3].rc.left && !_viHpPotion->used && KEYMANAGER->isOnceKeyDown('4'))
		{
			_viHpPotion->used = true;
			SOUNDMANAGER->FindSound("potionUse")->Play(0);
		}

		if (_viHpPotion->used)
		{
			if (_count % 10 == 0)
			{
				SCENEMANAGER->getPLAYER()->useHpPotion(10);
				_viHpPotion->count++;
				if (_viHpPotion->count > 30)
				{
					_viHpPotion = _vHpPotion.erase(_viHpPotion);
				}
			}
		}
	}

	//Mp포션 사용
	for (_viMpPotion = _vMpPotion.begin(); _viMpPotion != _vMpPotion.end(); ++_viMpPotion)
	{
		if (_viMpPotion->atMiniInven && _viMpPotion->rc.left == _miniInvenSpace[0].rc.left && !_viMpPotion->used && KEYMANAGER->isOnceKeyDown('1'))
		{
			_viMpPotion->used = true;
			SOUNDMANAGER->FindSound("potionUse")->Play(0);
		}
		else if (_viMpPotion->atMiniInven && _viMpPotion->rc.left == _miniInvenSpace[1].rc.left && !_viMpPotion->used && KEYMANAGER->isOnceKeyDown('2'))
		{
			_viMpPotion->used = true;
			SOUNDMANAGER->FindSound("potionUse")->Play(0);
		}
		else if (_viMpPotion->atMiniInven && _viMpPotion->rc.left == _miniInvenSpace[2].rc.left && !_viMpPotion->used && KEYMANAGER->isOnceKeyDown('3'))
		{
			_viMpPotion->used = true;
			SOUNDMANAGER->FindSound("potionUse")->Play(0);
		}
		else if (_viMpPotion->atMiniInven && _viMpPotion->rc.left == _miniInvenSpace[3].rc.left && !_viMpPotion->used && KEYMANAGER->isOnceKeyDown('4'))
		{
			_viMpPotion->used = true;
			SOUNDMANAGER->FindSound("potionUse")->Play(0);
		}

		if (_viMpPotion->used)
		{
			if (_count % 10 == 0)
			{
				SCENEMANAGER->getPLAYER()->useMpPotion(10);
				_viMpPotion->count++;
				if (_viMpPotion->count > 30)
				{
					_viMpPotion = _vMpPotion.erase(_viMpPotion);
				}
			}
		}
	}

}

void Inventory::miniInvenOrganize(void)
{
	if (PtInRect(&_miniInvenRect, _ptMouse))
	{
		_miniInvenActivation = true;
	}
	else _miniInvenActivation = false;


	for (_viHpPotion = _vHpPotion.begin(); _viHpPotion != _vHpPotion.end(); ++_viHpPotion)
	{
		if (PtInRect(&_viHpPotion->rc, _ptMouse) && !_viHpPotion->clicked && _viHpPotion->atMiniInven && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_viHpPotion->clicked = true;
			SOUNDMANAGER->FindSound("potionBuy")->Play(0);
		}

		if (_viHpPotion->clicked)
		{
			for (int j = 0; j < 4; j++)
			{
				if (PtInRect(&_miniInvenSpace[j].rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_viHpPotion->clicked = false;
					_viHpPotion->atInven = false;
					_viHpPotion->atMiniInven = true;
					_viHpPotion->atHideInven = false;
					_viHpPotion->rc = RectMake(_miniInvenSpace[j].rc.left, _miniInvenSpace[j].rc.top, 30, 30);
					SOUNDMANAGER->FindSound("potionBuy")->Play(0);
				}
			}
		}
	}

	for (_viMpPotion = _vMpPotion.begin(); _viMpPotion != _vMpPotion.end(); ++_viMpPotion)
	{
		for (_viHpPotion = _vHpPotion.begin(); _viHpPotion != _vHpPotion.end(); ++_viHpPotion)
		{
			if (_viHpPotion->rc.left == _viMpPotion->rc.left && _viHpPotion->rc.top == _viMpPotion->rc.top)
			{
				if (!_viMpPotion->clicked && !_viHpPotion->clicked)	_viMpPotion->clicked = true;
			}
		}
	}

	for (_viMpPotion = _vMpPotion.begin(); _viMpPotion != _vMpPotion.end(); ++_viMpPotion)
	{
		if (PtInRect(&_viMpPotion->rc, _ptMouse) && _viMpPotion->atMiniInven && KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !_viMpPotion->clicked)
		{
			_viMpPotion->clicked = true;
			SOUNDMANAGER->FindSound("potionBuy")->Play(0);
		}

		if (_viMpPotion->clicked)
		{
			for (int j = 0; j < 4; j++)
			{
				if (PtInRect(&_miniInvenSpace[j].rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_viMpPotion->clicked = false;
					_viMpPotion->atInven = false;
					_viMpPotion->atMiniInven = true;
					_viMpPotion->atHideInven = false;
					_viMpPotion->rc = RectMake(_miniInvenSpace[j].rc.left, _miniInvenSpace[j].rc.top, 30, 30);		
					SOUNDMANAGER->FindSound("potionBuy")->Play(0);
				}
			}
		}
	}

	for (_viHpPotion = _vHpPotion.begin(); _viHpPotion != _vHpPotion.end(); ++_viHpPotion)
	{
		for (_viMpPotion = _vMpPotion.begin(); _viMpPotion != _vMpPotion.end(); ++_viMpPotion)
		{
			if (_viHpPotion->rc.left == _viMpPotion->rc.left && _viHpPotion->rc.top == _viMpPotion->rc.top)
			{
				if (!_viMpPotion->clicked && !_viHpPotion->clicked)  _viHpPotion->clicked = true;
			}
		}
	}
}

void Inventory::miniInvenRender(void)
{
	if (_miniInvenActivation)
	{
		IMAGEMANAGER->render("MiniInventory", getMemDC(), _miniInvenRect.left, _miniInvenRect.top);
	}

	for (_viHpPotion = _vHpPotion.begin(); _viHpPotion != _vHpPotion.end(); ++_viHpPotion)
	{
		if (_viHpPotion->atMiniInven && !_viHpPotion->used)
		{
			if (!_viHpPotion->clicked)		_viHpPotion->img->render(getMemDC(), _viHpPotion->rc.left, _viHpPotion->rc.top);
		}
		if (_viHpPotion->clicked)	_viHpPotion->img->render(getMemDC(), _ptMouse.x - 15, _ptMouse.y - 10);
	}

	for (_viMpPotion = _vMpPotion.begin(); _viMpPotion != _vMpPotion.end(); ++_viMpPotion)
	{
		if (_viMpPotion->atMiniInven && !_viMpPotion->used)
		{
			if (!_viMpPotion->clicked)	_viMpPotion->img->render(getMemDC(), _viMpPotion->rc.left, _viMpPotion->rc.top);
		}
		if (_viMpPotion->clicked)	_viMpPotion->img->render(getMemDC(), _ptMouse.x - 15, _ptMouse.y - 10);
	}

}

void Inventory::hideInvenOrganize(void)
{
	for (_viHpPotion = _vHpPotion.begin(); _viHpPotion != _vHpPotion.end(); ++_viHpPotion)
	{
		if (_viHpPotion->atHideInven && PtInRect(&_viHpPotion->rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_viHpPotion->clicked = true;
			SOUNDMANAGER->FindSound("potionBuy")->Play(0);
		}

		if (_viHpPotion->clicked)
		{
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (PtInRect(&_hideInvenSpace[i][j].rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_viHpPotion->clicked = false;
						_viHpPotion->atInven = false;
						_viHpPotion->atMiniInven = false;
						_viHpPotion->atHideInven = true;
						_viHpPotion->rc = RectMake(_hideInvenSpace[i][j].rc.left, _hideInvenSpace[i][j].rc.top, 30, 30);		
						SOUNDMANAGER->FindSound("potionBuy")->Play(0);
					}
				}
			}
		}
	}

	for (_viMpPotion = _vMpPotion.begin(); _viMpPotion != _vMpPotion.end(); ++_viMpPotion)
	{
		for (_viHpPotion = _vHpPotion.begin(); _viHpPotion != _vHpPotion.end(); ++_viHpPotion)
		{
			if (_viHpPotion->rc.left == _viMpPotion->rc.left && _viHpPotion->rc.top == _viMpPotion->rc.top)
			{
				if (!_viMpPotion->clicked && !_viHpPotion->clicked)	_viMpPotion->clicked = true;
			}
		}
	}

	for (_viMpPotion = _vMpPotion.begin(); _viMpPotion != _vMpPotion.end(); ++_viMpPotion)
	{
		if (_viMpPotion->atHideInven && PtInRect(&_viMpPotion->rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_viMpPotion->clicked = true;
			SOUNDMANAGER->FindSound("potionBuy")->Play(0);
		}
		if (_viMpPotion->clicked)
		{
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (PtInRect(&_hideInvenSpace[i][j].rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_viMpPotion->clicked = false;
						_viMpPotion->atInven = false;
						_viMpPotion->atMiniInven = false;
						_viMpPotion->atHideInven = true;
						_viMpPotion->rc = RectMake(_hideInvenSpace[i][j].rc.left, _hideInvenSpace[i][j].rc.top, 30, 30);
						SOUNDMANAGER->FindSound("potionBuy")->Play(0);
					}
				}
			}
		}
	}

	for (_viHpPotion = _vHpPotion.begin(); _viHpPotion != _vHpPotion.end(); ++_viHpPotion)
	{
		for (_viMpPotion = _vMpPotion.begin(); _viMpPotion != _vMpPotion.end(); ++_viMpPotion)
		{
			if (_viHpPotion->rc.left == _viMpPotion->rc.left && _viHpPotion->rc.top == _viMpPotion->rc.top)
			{
				if (!_viMpPotion->clicked && !_viHpPotion->clicked)  _viHpPotion->clicked = true;
			}
		}
	}
}

void Inventory::hideInvenRender(void)
{
	for (_viHpPotion = _vHpPotion.begin(); _viHpPotion != _vHpPotion.end(); ++_viHpPotion)
	{
		if (_viHpPotion->atHideInven)
		{
			if (_viHpPotion->clicked)	_viHpPotion->img->render(getMemDC(), _ptMouse.x - 15, _ptMouse.y - 10);
			if (!_viHpPotion->clicked)	_viHpPotion->img->render(getMemDC(), _viHpPotion->rc.left, _viHpPotion->rc.top);
		}
	}

	for (_viMpPotion = _vMpPotion.begin(); _viMpPotion != _vMpPotion.end(); ++_viMpPotion)
	{
		if (_viMpPotion->atHideInven)
		{
			if (_viMpPotion->clicked)	_viMpPotion->img->render(getMemDC(), _ptMouse.x - 15, _ptMouse.y - 10);
			if (!_viMpPotion->clicked)	_viMpPotion->img->render(getMemDC(), _viMpPotion->rc.left, _viMpPotion->rc.top);
		}
	}

}

void Inventory::getPotion(int i)
{
	if (i == 1)
	{
		tagItem Potion;

		Potion.img = IMAGEMANAGER->findImage("hpPotion");
		Potion.name = "       Hp포션";
		Potion.info = "Hp회복을 위한 포션 ";
		Potion.price = 200;
		Potion.clicked = false;
		Potion.used = false;
		Potion.atInven = true;
		Potion.atMiniInven = false;
		Potion.atHideInven = false;
		Potion.count = 0;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if(!_invenSpace[i][j].occupied)		Potion.rc = RectMake(_invenSpace[i][j].rc.left, _invenSpace[i][j].rc.top, 30, 30);
			}
		}

		_vHpPotion.push_back(Potion);
	}
	else
	{
		tagItem Potion;

		Potion.img = IMAGEMANAGER->findImage("mpPotion");
		Potion.name = "       Mp포션";
		Potion.info = "Mp회복을 위한 포션 ";
		Potion.price = 200;
		Potion.clicked = false;
		Potion.used = false;
		Potion.atInven = true;
		Potion.atMiniInven = false;
		Potion.atHideInven = false;
		Potion.count = 0;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (!_invenSpace[i][j].occupied)		Potion.rc = RectMake(_invenSpace[i][j].rc.left, _invenSpace[i][j].rc.top, 30, 30);
			}
		}

		_vMpPotion.push_back(Potion);
	}
}

void Inventory::drawFont(int x, int y, int width, int height, int fontSize, char* str, int r, int g, int b)
{
	RECT rc = RectMake(x, y, width, height);
	FillRect(getMemDC(), &rc, CreateSolidBrush(RGB(0, 0, 0)));
	SetBkMode(getMemDC(), 1);
	HFONT _currentFont = CreateFont(fontSize, 0, 0, 0, 0, 0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("kodia"));
	HFONT _oldFont = (HFONT)SelectObject(getMemDC(), _currentFont);
	SetTextColor(getMemDC(), RGB(r, g, b));
	DrawText(getMemDC(), str, -1, &rc, DT_LEFT | DT_WORDBREAK);
	SelectObject(getMemDC(), _oldFont);
	DeleteObject(_currentFont);
}

