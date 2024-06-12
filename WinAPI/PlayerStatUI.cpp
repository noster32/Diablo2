#include "Stdafx.h"
#include "PlayerStatUI.h"
#include "Player.h"

HRESULT PlayerStatUI::init(void)
{
	IMAGEMANAGER->addImage("playerStatUI", "Resources/Images/Object/stat.bmp",
		400, 558, true, RGB(255, 0, 255));

	_isStatUI = false;

	return S_OK;
}

void PlayerStatUI::release(void)
{
}

void PlayerStatUI::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		_isStatUI = !_isStatUI;
	}
}

void PlayerStatUI::render(Player* p)
{
	if (_isStatUI)
	{
		IMAGEMANAGER->render("playerStatUI", getMemDC(), 0, 0);
		//���氡�� ����
		if(p->getPlayerStat().energe > 100) FONTMANAGER->drawText(getMemDC(), 162, 358, "kodia", 13, 10, p->getPlayerStat().energe, RGB(72, 72, 157));
		else								 FONTMANAGER->drawText(getMemDC(), 162, 358, "kodia", 13, 10, p->getPlayerStat().energe, RGB(255, 255, 255));
		if(p->getPlayerStat().maxHp > 1000)	 FONTMANAGER->drawText(getMemDC(), 348, 148, "kodia", 13, 10, p->getPlayerStat().maxHp,  RGB(72, 72, 157));
		else								 FONTMANAGER->drawText(getMemDC(), 348, 148, "kodia", 13, 10, p->getPlayerStat().maxHp, RGB(255, 255, 255));
		if(p->getPlayerStat().maxMp > 1000)	 FONTMANAGER->drawText(getMemDC(), 348, 173, "kodia", 13, 10, p->getPlayerStat().maxMp,  RGB(72, 72, 157));
		else								 FONTMANAGER->drawText(getMemDC(), 348, 173, "kodia", 13, 10, p->getPlayerStat().maxMp, RGB(255, 255, 255));
		if(p->getPlayerStat().atk > 100)	 FONTMANAGER->drawText(getMemDC(), 357, 210, "kodia", 13, 10, p->getPlayerStat().atk, RGB(72, 72, 157));
		else								 FONTMANAGER->drawText(getMemDC(), 357, 210, "kodia", 13, 10, p->getPlayerStat().atk, RGB(255, 255, 255));
		if(p->getPlayerStat().def > 300)	 FONTMANAGER->drawText(getMemDC(), 357, 236, "kodia", 13, 10, p->getPlayerStat().def, RGB(72, 72, 157));
		else								 FONTMANAGER->drawText(getMemDC(), 357, 236, "kodia", 13, 10, p->getPlayerStat().def, RGB(255, 255, 255));
		
		//����Ұ� ����
		FONTMANAGER->drawText(getMemDC(), 134, 75, "kodia", 14, 10,"���̻����屹",12, RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), 308, 75, "kodia", 14, 10,"�Ҽ�����",8, RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), 90, 100, "kodia", 14, 10,"����",4, RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), 94, 114, "kodia", 14, 10,"99",2, RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), 180, 100, "kodia", 14, 10,"����ġ",6, RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), 153, 114, "kodia", 14, 10,"3,520,485,254",13, RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), 304, 100, "kodia", 14, 10,"���� ����",9, RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), 327, 114, "kodia", 14, 10,"0",1, RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), 105, 148, "kodia", 12, 10,"��",2, RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), 97, 211, "kodia", 12, 10, "��ø��", 6, RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), 97, 299, "kodia", 12, 10, "�����", 6, RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), 162, 148, "kodia", 12, 10, "120", 3, RGB(72, 72, 157));
		FONTMANAGER->drawText(getMemDC(), 162, 211, "kodia", 12, 10, "140", 3, RGB(72, 72, 157));
		FONTMANAGER->drawText(getMemDC(), 162, 299, "kodia", 12, 10, "300", 3, RGB(72, 72, 157));
		FONTMANAGER->drawText(getMemDC(), 97, 360, "kodia", 12, 10, "������", 6, RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), 280, 148, "kodia", 12, 10,"ü��",4, RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), 280, 173, "kodia", 12, 10,"����",4, RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), 275, 211, "kodia", 12, 10, "���ݷ�", 6, RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), 275, 236, "kodia", 12, 10, "����", 6, RGB(255, 255, 255));		
	}
}
