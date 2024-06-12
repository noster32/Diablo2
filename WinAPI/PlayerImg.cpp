#include "Stdafx.h"
#include "PlayerImg.h"

HRESULT PlayerImg::init(void)
{
    IMAGEMANAGER->addFrameImage("�������", "Resources/Images/Sorceress/character/townIdle.bmp",
        0.0f, 0.0f, 672, 1168, 16, 16, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("�����ȱ�", "Resources/Images/Sorceress/character/townWalk.bmp",
        0.0f, 0.0f, 384, 1200, 8, 16, true, RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("�������", "Resources/Images/Sorceress/character/dungeonIdle.bmp",
        0.0f, 0.0f, 528, 1440, 8, 16, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("�����ȱ�", "Resources/Images/Sorceress/character/dungeonWalk.bmp",
        0.0f, 0.0f, 480, 1440, 8, 16, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("ĳ���ø��", "Resources/Images/Sorceress/character/dungeonCasting.bmp",
        0.0f, 0.0f, 1358, 1440, 14, 16, true, RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("���̾�ĳ��Ʈ", "Resources/Images/Sorceress/character/firecast.bmp",
        0.0f, 0.0f, 1638, 164, 14, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("���̽�ĳ��Ʈ", "Resources/Images/Sorceress/character/coldcast.bmp",
        0.0f, 0.0f, 1725, 160, 15, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("�ڷ���Ʈĳ��Ʈ", "Resources/Images/Sorceress/character/teleport.bmp",
        0.0f, 0.0f, 2124, 160, 18, 1, true, RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("�Ҽ��׸���", "Resources/Images/Sorceress/character/soShadow.bmp",
        0.0f, 0.0f, 602, 640, 7, 8, true, RGB(255, 0, 255));

    return S_OK;
}
