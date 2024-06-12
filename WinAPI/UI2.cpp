#include "Stdafx.h"
#include "UI2.h"
#include "Player.h"

HRESULT UI2::init(void)
{
	IMAGEMANAGER->addImage("UI", "Resources/Images/Object/interFace.bmp",
		800, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Cursor", "Resources/Images/Object/Cursor.bmp",
		248, 27, 8, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("�÷��̾�ü��UI", "Resources/Images/Object/hpImage.bmp",
		0.0f, 0.0f, 128, 2688, 1, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��UI", "Resources/Images/Object/mpImage.bmp",
		0.0f, 0.0f, 128, 2688, 1, 21, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("��ų ��ư", "Resources/Images/Object/skillButton.bmp",
		48, 192, 1, 4);

	_inventory = new Inventory;
	_inventory->init();
	SCENEMANAGER->setInven(_inventory);
	_pStatUI = new PlayerStatUI;
	_pStatUI->init();
	_shop = new Shop;
	_shop->init();

	// ��ų ��ȣ _skillFrame �� ǥ��
	_count, _cursorFrame, _skillFrame = 0;
	// ��ų ��Ʈ �ʱ�ȭ
	_skillR[0] = RectMake(117, 552, 48, 48);
	for (int i = 1; i < 4; i++)
	{
		_skillR[i] = RectMake(69 + i * 48, 452, 48, 48);
	}
	// ��ų Ŭ�� �ʱ�ȭ(bool)
	_skillClick = false;

	// ���콺 Ŀ��
	ShowCursor(false);

	return S_OK;
}

void UI2::release(void)
{
	_inventory->release();
	SAFE_DELETE(_inventory);
	_pStatUI->release();
	SAFE_DELETE(_pStatUI);
	_shop->release();
	SAFE_DELETE(_shop);
}

void UI2::update(void)
{
	_count++;
	if (_count % 20 == 0)
	{
		_cursorFrame++;
		if (_cursorFrame > 7) _cursorFrame = 0;
	}

	_shop->update(_inventory);

	if (SCENEMANAGER->getDisplayUI())
	{
		_pStatUI->update();
		if (_inventory->getInvenActive())
		{
			_inventory->update();
			_inventory->itemOrganize();
			_inventory->itemEquip(SCENEMANAGER->getPLAYER());
		}
		_inventory->miniInvenOrganize();
		if (_inventory->getMiniInvActive())		_inventory->hideInvenOrganize();

		if (!_inventory->getInvenActive() && KEYMANAGER->isOnceKeyDown('I')) _inventory->getInvenActive() = true;
		else if (_inventory->getInvenActive() && KEYMANAGER->isOnceKeyDown('I'))  _inventory->getInvenActive() = false;

		_inventory->miniInvenUseItem();
	}
	// ��ų UI
	if (PtInRect(&_skillR[0], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_skillClick = true;
		}
	}
	if (_skillClick)
	{
		if (PtInRect(&_skillR[1], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_skillFrame = 0;
				_skillClick = false;
			}
		}
		if (PtInRect(&_skillR[2], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_skillFrame = 1;
				_skillClick = false;
			}
		}
		if (PtInRect(&_skillR[3], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_skillFrame = 2;
				_skillClick = false;
			}
		}
	}
}

void UI2::render(Player* p)
{
	if (SCENEMANAGER->getDisplayUI())
	{

		if (_inventory->getInvenActive())	_inventory->render();

		//��ų �̹��� ���
		if (_skillClick)
		{
			for (int i = 0; i < 3; i++)
			{
				IMAGEMANAGER->frameRender("��ų ��ư", getMemDC(), 117 + i * 48, 452, 0, i);
			}
		}
		IMAGEMANAGER->frameRender("��ų ��ư", getMemDC(), 117, 552, 0, _skillFrame);
		//���� �̹��� ���
		IMAGEMANAGER->frameRender("��ų ��ư", getMemDC(), 635, 552, 0, 4);
		_shop->render();
		_pStatUI->render(p);
		IMAGEMANAGER->render("UI", getMemDC(), 0, 500);
		IMAGEMANAGER->frameRender("�÷��̾�ü��UI", getMemDC(), 0, 470, 0, p->getPlayerStat().hpCnt);
		IMAGEMANAGER->frameRender("�÷��̾��UI", getMemDC(), 670, 470, 0, p->getPlayerStat().mpCnt);

		_inventory->miniInvenRender();
		if (_inventory->getMiniInvActive())	_inventory->hideInvenRender();
	}
	IMAGEMANAGER->frameRender("Cursor", getMemDC(), _ptMouse.x, _ptMouse.y, _cursorFrame, 0);
}
