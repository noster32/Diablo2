#include "Stdafx.h"
#include "Item.h"

HRESULT Item::init(void)
{
	// 아이템 목록
	_vItem.push_back({ IMAGEMANAGER->addImage("hp포션","Resources/Images/Object/hpPotion.bmp",
		28,28,true,RGB(255,0,255)) ,"Hp포션","posion","HP회복을 위한 포션",0.0f,0.0f,{},0,200,false });
	_vItem.push_back({ IMAGEMANAGER->addImage("mp포션","Resources/Images/Object/mpPotion.bmp",
		28,28,true,RGB(255,0,255)) ,"Mp포션","posion","MP회복을 위한 포션",0.0f,0.0f,{},0,200,false });

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

