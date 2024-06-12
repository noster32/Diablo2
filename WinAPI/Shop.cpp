#include "Stdafx.h"
#include "Shop.h"
#include "Player.h"
#include "Inventory.h"

HRESULT Shop::init(void)
{
	SOUNDMANAGER->AddSound("GoodDay", "Resources/Sounds/good-day.wav")->SetVolume(100);
	IMAGEMANAGER->addImage("shop", "Resources/Images/Object/shop.bmp",
		399, 555, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CancelButton", "Resources/Images/Object/cancel_button.bmp", 32, 64, 1, 2);
	IMAGEMANAGER->addImage("hpPotion", "Resources/Images/Object/hpPotion.bmp",
		28, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mpPotion", "Resources/Images/Object/mpPotion.bmp",
		28, 28, true, RGB(255, 0, 255));
	// ������ Ŭ���� ������ ������
	IMAGEMANAGER->addImage("buyWindow", "Resources/Images/Object/buyWindow.bmp",
		128, 112, true, RGB(255, 0, 255));
	// ���� Ŭ���� ������ ������
	IMAGEMANAGER->addImage("shopWindow", "Resources/Images/Object/shopWindow.bmp",
		59, 82, true, RGB(255, 0, 255));
	// ���� ������
	IMAGEMANAGER->addFrameImage("npcCain", "Resources/Images/Object/npcCain.bmp",
		285, 86, 5, 1, true, RGB(255, 0, 255));
	// ���� �׸���
	IMAGEMANAGER->addImage("cainShadow", "Resources/Images/Object/cainShadow.bmp",
		63, 28, true, RGB(255, 0, 255));
	// �Ұ� �ʱ�ȭ
	_openShop, _hpBuy, _mpBuy, _noBuy, _hpPotionC, _mpPotionC, _closeButton, _shopClick = false;

	// ���� ������ ī��Ʈ
	_count, _countFrame = 0;
	// ���� ��Ʈ
	_cainX = 1360;
	_cainY = 1020;
	
	// ���� �ݱ� ��ư
	_shopCloseButton = RectMake(352, 449, 30, 30);
	// Ŭ���� ������ ��Ʈ
	for (int i = 0; i < 6; i++)
	{
		_itemClickR[i] = {};
	}
	for (int i = 0; i < 2; i++)
	{
		_shopSpace[i] = RectMake(356, 128 + i * 28, 25, 25);
	}
	
	_item = new Item;
	_item->init();

	for (int i = 0; i < 2; i++)
	{
		setInvenItem(_item->getItem()[i].img, _item->getItem()[i].iName,
			_item->getItem()[i].iType, _item->getItem()[i].info,
			_item->getItem()[i].x, _item->getItem()[i].y, _item->getItem()[i].rc,
			_item->getItem()[i].invenNum, _item->getItem()[i].gold, _item->getItem()[i].click);
	}

	return S_OK;
}

void Shop::release(void)
{
}

void Shop::update(Inventory* inventory)
{
	// ���� ��Ʈ ī�޶� �̵�
	_npcCain = RectMakeCenter(_cainX - SCENEMANAGER->getPLAYER()->getCamera().x, _cainY - SCENEMANAGER->getPLAYER()->getCamera().y, 57, 86);
	// ���� Ŭ�� ��Ʈ
	_sClickR[0] = RectMakeCenter(_cainX - SCENEMANAGER->getPLAYER()->getCamera().x, _cainY - SCENEMANAGER->getPLAYER()->getCamera().y-90, 59, 82);
	_sClickR[1] = RectMakeCenter(_cainX - SCENEMANAGER->getPLAYER()->getCamera().x, _cainY - SCENEMANAGER->getPLAYER()->getCamera().y - 90, 50, 20);
	_sClickR[2] = RectMakeCenter(_cainX - SCENEMANAGER->getPLAYER()->getCamera().x, _cainY - SCENEMANAGER->getPLAYER()->getCamera().y - 70, 50, 20);
	// �ݱ� ��ư ����
	if (PtInRect(&_shopCloseButton, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _openShop)
		{
			_openShop = false;
			inventory->getInvenActive() = false;
			SCENEMANAGER->getPLAYER()->setIsAllStop(false);
		}
	}

	// ���� ������ ī��Ʈ
	_count++;
	if (_count % 30 == 0)
	{
		_countFrame++;
		if (_countFrame >= 5)
		{
			_countFrame = 0;
		}
	}
	// ���� Ŭ���� �� ���� 
	if (PtInRect(&_npcCain, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_shopClick = true;
			SOUNDMANAGER->FindSound("GoodDay")->Play(0);
		}
	}
	// ���� Ŭ�� �ŷ���ư Ŭ��
	if (_shopClick && PtInRect(&_sClickR[1], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_openShop = true;
			inventory->getInvenActive() = true;
			_shopClick = false;
			SCENEMANAGER->getPLAYER()->setIsAllStop(true);
		}
	}
	// ���� �ŷ� ��� ��ư Ŭ��
	if (_shopClick && PtInRect(&_sClickR[2], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_shopClick = false;
		}
	}
	// �ƹ��� Ŭ���� ��� ��ư ����
	if (_shopClick && !PtInRect(&_sClickR[0], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_shopClick = false;
		}
	}
	// HP���� Ŭ��
	if (PtInRect(&_shopSpace[0], _ptMouse) && !_hpPotionC && !_mpPotionC)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_hpPotionC = true;
			_itemClickR[0] = RectMakeCenter(_ptMouse.x, _ptMouse.y-30,128,112);
			_itemClickR[1] = RectMakeCenter(_itemClickR[0].left+(_itemClickR[0].right -_itemClickR[0].left)/2, _itemClickR[0].top+175 / 2, 50, 15);
			_itemClickR[2] = RectMakeCenter(_itemClickR[0].left+(_itemClickR[0].right - _itemClickR[0].left)/2, _itemClickR[0].top+205 / 2, 50, 15);
		}
	}
	if (_hpPotionC && !PtInRect(&_itemClickR[0],_ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_hpPotionC = false;
		}
	}
	// HP���� ����
	if (PtInRect(&_itemClickR[1], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_hpBuy = true;
			SOUNDMANAGER->FindSound("potionBuy")->Play(0);
		}
	}
	// HP���� ���Ž� ��� �Ҹ�
	if (_hpBuy)
	{
		if (inventory->getGold() >= 200)
		{
			inventory->getGold() -= _item->getItem()[0].gold;
			inventory->getPotion(1);
		}
		if (inventory->getGold() <= 0)
		{
			inventory->getGold() = 0;
		}
		_hpBuy = false;
	}
	// HP���� �ƴϿ� ��ư
	if (PtInRect(&_itemClickR[2],_ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_hpPotionC = false;
		}
	}
	// MP���� Ŭ��
	if (PtInRect(&_shopSpace[1], _ptMouse) && !_mpPotionC && !_hpPotionC)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_mpPotionC = true;
			_itemClickR[3] = RectMakeCenter(_ptMouse.x, _ptMouse.y - 20, 128, 112);
			_itemClickR[4] = RectMakeCenter(_itemClickR[3].left + (_itemClickR[3].right - _itemClickR[3].left) / 2, _itemClickR[3].top + 175 / 2, 50, 15);
			_itemClickR[5] = RectMakeCenter(_itemClickR[3].left + (_itemClickR[3].right - _itemClickR[3].left) / 2, _itemClickR[3].top + 205 / 2, 50, 15);
		}
	}
	if (_mpPotionC && !PtInRect(&_itemClickR[3], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_mpPotionC = false;
		}
	}
	// MP���� ����
	if (PtInRect(&_itemClickR[4], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_mpBuy = true;
			SOUNDMANAGER->FindSound("potionBuy")->Play(0);
		}
	}
	// MP���� ���Ž� ��� �Ҹ�
	if (_mpBuy)
	{
		if (inventory->getGold() >= 200)
		{
			inventory->getGold() -= _item->getItem()[1].gold;
			inventory->getPotion(2);
		}
		if (inventory->getGold() <= 0)
		{
			inventory->getGold() = 0;
		}
		_mpBuy = false;
	}
	// MP���� �ƴϿ� ��ư
	if (PtInRect(&_itemClickR[5], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_mpPotionC = false;
		}
	}
}

void Shop::render(void)
{
	if (_openShop)
	{
		IMAGEMANAGER->render("shop", getMemDC(), 0, 2);
		
		// �� ������ ��ư
		if (PtInRect(&_shopCloseButton, _ptMouse))
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)&&_openShop)
			{
				IMAGEMANAGER->frameRender("CancelButton",getMemDC(),_shopCloseButton.left-1, _shopCloseButton.top-2, 0, 1);
			}
		}
		
		IMAGEMANAGER->render("hpPotion", getMemDC(), _shopSpace[0].left-2, _shopSpace[0].top-3);
		IMAGEMANAGER->render("mpPotion", getMemDC(), _shopSpace[1].left-2, _shopSpace[1].top-3);
		// HP���� �̸�, ����
		if (PtInRect(&_shopSpace[0], _ptMouse) && !_mpPotionC)
		{
			drawFont(_shopSpace[0].right - 40, _shopSpace[0].top - 45, 65, 15, 15, _vShop[0].iName, 255, 255, 255);
			drawFont(_shopSpace[0].right - 40, _shopSpace[0].top - 30, 65, 30, 15, _vShop[0].info, 255, 255, 255);
		}
		// HP���� Ŭ��
		if (_hpPotionC)
		{
			FillRect(getMemDC(), &_itemClickR[0], CreateSolidBrush(RGB(0, 0, 0)));
			IMAGEMANAGER->render("buyWindow", getMemDC(),_itemClickR[0].left,_itemClickR[0].top);
			_TCHAR str[] = TEXT("\n ���� \n �ҷ��� �������� \n ���: \n 200 \n �� \n �ƴϿ�");
			HFONT _currentFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
				HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("kodia"));
			HFONT _oldFont = (HFONT)SelectObject(getMemDC(), _currentFont);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			DrawText(getMemDC(), str, -1, &_itemClickR[0], DT_CENTER | DT_WORDBREAK);
		}
		// MP���� �̸�, ����
		if (PtInRect(&_shopSpace[1], _ptMouse) && !_hpPotionC)
		{
			drawFont(_shopSpace[1].right - 40, _shopSpace[1].top - 45, 65, 15, 15, _vShop[1].iName, 255, 255, 255);
			drawFont(_shopSpace[1].right - 40, _shopSpace[1].top - 30, 65, 30, 15, _vShop[1].info, 255, 255, 255);
		}
		// MP���� Ŭ��
		if (_mpPotionC)
		{
			FillRect(getMemDC(), &_itemClickR[3], CreateSolidBrush(RGB(0, 0, 0)));
			IMAGEMANAGER->render("buyWindow", getMemDC(), _itemClickR[3].left, _itemClickR[3].top);
			_TCHAR str[] = TEXT("\n ���� \n �ҷ��� �������� \n ���: \n 200 \n �� \n �ƴϿ�");
			HFONT _currentFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
				HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("kodia"));
			HFONT _oldFont = (HFONT)SelectObject(getMemDC(), _currentFont);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			DrawText(getMemDC(), str, -1, &_itemClickR[3], DT_CENTER | DT_WORDBREAK);
		}
	}
	if (!_openShop)
	{
		IMAGEMANAGER->render("cainShadow", getMemDC(), _npcCain.left-20, _npcCain.bottom-35);
		IMAGEMANAGER->frameRender("npcCain", getMemDC(), _npcCain.left, _npcCain.top, _countFrame, 0);
	}
	if (_shopClick)
	{
		FillRect(getMemDC(), &_sClickR[0], CreateSolidBrush(RGB(0, 0, 0)));
		_TCHAR str[] = TEXT("\n ���� \n �ŷ� \n ���");
		HFONT _currentFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
			HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("kodia"));
		HFONT _oldFont = (HFONT)SelectObject(getMemDC(), _currentFont);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		DrawText(getMemDC(), str, -1, &_sClickR[0], DT_CENTER | DT_WORDBREAK);
		IMAGEMANAGER->render("shopWindow", getMemDC(), _npcCain.left, _npcCain.top-90);
	}
}

void Shop::drawFont(int x, int y, int width, int height, int fontSize, char* str, int r, int g, int b)
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

