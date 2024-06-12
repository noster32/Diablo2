#include "Stdafx.h"
#include "WAYPOINT.h"
#include "Player.h"

HRESULT WAYPOINT::init(void)
{
	_wayPoint = RectMakeCenter(1440, 450, 100, 80);

	_isWayPoint = _isWayPointClick = false;

	SOUNDMANAGER->AddSound("Waypoint", "Resources/Sounds/PortalEnter.wav")->SetVolume(100);
	return S_OK;
}

void WAYPOINT::release(void)
{
}

void WAYPOINT::update(Player* p)
{
	_wayPoint = RectMakeCenter(1440 - p->getCamera().x, 450 - p->getCamera().y, 100, 80);

	if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON) && PtInRect(&_wayPoint, _ptMouse))
	{
		_isWayPointClick = true;
	}

	RECT tempRC;
	newPlayerRC = RectMakeCenter(p->getPlayerStat().x - p->getCamera().x + 10, p->getPlayerStat().y + 30 - p->getCamera().y, 20, 20);
	if(IntersectRect(&tempRC, &newPlayerRC, &_wayPoint) && !_isWayPoint && _isWayPointClick)
	{
		SOUNDMANAGER->FindSound("Waypoint")->Play(0);
		_isWayPoint = true;
		_isWayPointClick = false;
		p->setPlayerMove(false);

		if (_vway.size() != 0) _vway.clear();

		WayPOINT wayp;
		ZeroMemory(&wayp, sizeof(WayPOINT));

		wayp.img = IMAGEMANAGER->addImage("웨이포인트", "Resources/Images/Object/waypoint.bmp",
				400, 588, true, RGB(255, 0, 255));
		wayp.movePoint = RectMakeCenter(250, 145, 250, 30);
		wayp.cancelRC = RectMakeCenter(370, 490, 30, 30);
		_vway.push_back(wayp);
	}

	if (_isWayPoint)
	{
		for (_viway = _vway.begin(); _viway != _vway.end();)
		{
			if ((PtInRect(&_viway->cancelRC, _ptMouse) && KEYMANAGER->isOnceKeyUp(MK_LBUTTON)) 
				|| (WINSIZE_X/2<_ptMouse.x && _ptMouse.x < WINSIZE_X && 0<_ptMouse.y && _ptMouse.y <WINSIZE_Y && KEYMANAGER->isOnceKeyUp(MK_LBUTTON)))
			{
				_isWayPoint = false;
				_viway = _vway.erase(_viway);
				p->setPlayerMove(true);
			}
			else
			{
				if (PtInRect(&_viway->movePoint, _ptMouse) && KEYMANAGER->isOnceKeyUp(MK_LBUTTON))
				{
					_isWayPoint = false;
					_viway = _vway.erase(_viway);
					p->setCameraMoveD(200);
					SCENEMANAGER->setIsLoadingImg(true);
					SCENEMANAGER->changeScene("던전");
					SOUNDMANAGER->FindSound("TownBGM")->Stop(1);
				}
				else ++_viway;
				p->setPlayerMove(false);
			}
		}
	}




}

void WAYPOINT::render(void)
{
	for (_viway = _vway.begin(); _viway != _vway.end();++_viway)
	{
		_viway->img->render(getMemDC());
		FONTMANAGER->drawText(getMemDC(), 130, 132, "kodia", 20, 10, "카오스 생츄어리", 15, RGB(255, 255, 255));
	}
}
