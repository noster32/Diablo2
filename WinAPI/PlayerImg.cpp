#include "Stdafx.h"
#include "PlayerImg.h"

HRESULT PlayerImg::init(void)
{
    IMAGEMANAGER->addFrameImage("마을대기", "Resources/Images/Sorceress/character/townIdle.bmp",
        0.0f, 0.0f, 672, 1168, 16, 16, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("마을걷기", "Resources/Images/Sorceress/character/townWalk.bmp",
        0.0f, 0.0f, 384, 1200, 8, 16, true, RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("던전대기", "Resources/Images/Sorceress/character/dungeonIdle.bmp",
        0.0f, 0.0f, 528, 1440, 8, 16, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("던전걷기", "Resources/Images/Sorceress/character/dungeonWalk.bmp",
        0.0f, 0.0f, 480, 1440, 8, 16, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("캐스팅모션", "Resources/Images/Sorceress/character/dungeonCasting.bmp",
        0.0f, 0.0f, 1358, 1440, 14, 16, true, RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("파이어캐스트", "Resources/Images/Sorceress/character/firecast.bmp",
        0.0f, 0.0f, 1638, 164, 14, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("아이스캐스트", "Resources/Images/Sorceress/character/coldcast.bmp",
        0.0f, 0.0f, 1725, 160, 15, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("텔레포트캐스트", "Resources/Images/Sorceress/character/teleport.bmp",
        0.0f, 0.0f, 2124, 160, 18, 1, true, RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("소서그림자", "Resources/Images/Sorceress/character/soShadow.bmp",
        0.0f, 0.0f, 602, 640, 7, 8, true, RGB(255, 0, 255));

    return S_OK;
}
