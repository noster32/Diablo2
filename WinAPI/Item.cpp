#include "Stdafx.h"
#include "Item.h"

HRESULT Item::init(void)
{
	// ������ ���
	_vItem.push_back({ IMAGEMANAGER->addImage("hp����","Resources/Images/Object/hpPotion.bmp",
		28,28,true,RGB(255,0,255)) ,"Hp����","posion","HPȸ���� ���� ����",0.0f,0.0f,{},0,200,false });
	_vItem.push_back({ IMAGEMANAGER->addImage("mp����","Resources/Images/Object/mpPotion.bmp",
		28,28,true,RGB(255,0,255)) ,"Mp����","posion","MPȸ���� ���� ����",0.0f,0.0f,{},0,200,false });

	return S_OK;
}

void Item::release(void)
{
}

void Item::update(void)
{
}

void Item::render(void)
{
}

