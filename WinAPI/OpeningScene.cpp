#include "Stdafx.h"
#include "OpeningScene.h"

HRESULT OpeningScene::init(void)
{
    hWndVideo = MCIWndCreate(_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD, "Resources/Images/Object/Opening.wmv");
    MoveWindow(hWndVideo, 0, 0, WINSIZE_X, WINSIZE_Y, NULL);
    MCIWndPlay(hWndVideo);
    
    openingSkipAnyKey = false;

    return S_OK;
}

void OpeningScene::release(void)
{
}

void OpeningScene::update(void)
{
    for (int i = 0; i < 255; i++)
    {
        if (GetAsyncKeyState(i))
        {
            openingSkipAnyKey = true;
            break;
        }
    }

    if (MCIWndGetLength(hWndVideo) <= MCIWndGetPosition(hWndVideo) || KEYMANAGER->isOnceKeyDown(MK_LBUTTON) || openingSkipAnyKey)
    {
        MCIWndClose(hWndVideo);
        MCIWndDestroy(hWndVideo);
        hWndVideo = 0;
        SCENEMANAGER->setIsOpening(false);
        SCENEMANAGER->changeScene("메인화면");
    }
}
