#include "Stdafx.h"
#include "MenuScene.h"

HRESULT MenuScene::init(void)
{
    IMAGEMANAGER->addImage("디아메인화면배경","Resources/Images/Object/디아메인화면배경.bmp", WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->addFrameImage("메인화면디아로고", "Resources/Images/Object/mainLogo.bmp", 350, 4200, 1, 30, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("게임시작버튼", "Resources/Images/Object/시작버튼.bmp", 270, 70, 1, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("게임종료버튼", "Resources/Images/Object/종료버튼.bmp", 270, 70, 1, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("맵툴버튼", "Resources/Images/Object/맵툴버튼.bmp", 270, 70, 1, 2, true, RGB(255, 0, 255));

    _logoCnt = _StartIdx = _QuitIdx = _MapToolIdx = 0;
    _buttonClick = false;

    _gameStart = RectMakeCenter(WINSIZE_X / 2, 380, 270, 35);
    _gameMapTool = RectMakeCenter(WINSIZE_X / 2, 420, 270, 35);
    _gameQuit = RectMakeCenter(WINSIZE_X / 2, 460, 270, 35);

    SOUNDMANAGER->AddSound("Intro", "Resources/Sounds/intro.wav")->SetVolume(100);
    SOUNDMANAGER->FindSound("Intro")->Play(0);

    return S_OK;
}

void MenuScene::release(void)
{
}

void MenuScene::update(void)
{
    _logoCnt++;
    if (_logoCnt % 5 == 0)
    {
        IMAGEMANAGER->findImage("메인화면디아로고")->setFrameY(IMAGEMANAGER->findImage("메인화면디아로고")->getFrameY() + 1);
        if (IMAGEMANAGER->findImage("메인화면디아로고")->getFrameY() > 28)
        {
            IMAGEMANAGER->findImage("메인화면디아로고")->setFrameY(0);
            _logoCnt = 0;
        } 
    }

    if (KEYMANAGER->isStayKeyDown(MK_LBUTTON))
    {
        _buttonClick = true;
    }


    if (PtInRect(&_gameStart, _ptMouse) && _buttonClick) _StartIdx = 1;
    else  _StartIdx = 0;
   

    if (PtInRect(&_gameQuit, _ptMouse) && _buttonClick) _QuitIdx = 1;
    else   _QuitIdx = 0;
    

    if (PtInRect(&_gameMapTool, _ptMouse) && _buttonClick) _MapToolIdx = 1;
    else _MapToolIdx = 0;

    

    if (KEYMANAGER->isOnceKeyUp(MK_LBUTTON))
    {
        _buttonClick = false;
        if (PtInRect(&_gameQuit, _ptMouse))
        {
            PostQuitMessage(0);
        }
        if (PtInRect(&_gameStart, _ptMouse))
        {
            SCENEMANAGER->setDisplayUI(true);
            SCENEMANAGER->setIsLoadingImg(true);
            SCENEMANAGER->changeScene("로딩씬");
            SOUNDMANAGER->FindSound("Intro")->Stop(1);
        }
        if (PtInRect(&_gameMapTool, _ptMouse))
        {
            SCENEMANAGER->setDisplayUI(false);
            SCENEMANAGER->setIsLoadingImg(false);
            SCENEMANAGER->changeScene("맵툴");
        }
    }
}

void MenuScene::render(void)
{
    IMAGEMANAGER->render("디아메인화면배경", getMemDC());
    IMAGEMANAGER->frameRender("메인화면디아로고", getMemDC(), 225, 30, 0, IMAGEMANAGER->findImage("메인화면디아로고")->getFrameY());
    IMAGEMANAGER->frameRender("게임시작버튼", getMemDC(), _gameStart.left, _gameStart.top, 0, _StartIdx);
    IMAGEMANAGER->frameRender("맵툴버튼", getMemDC(), _gameMapTool.left, _gameMapTool.top, 0, _MapToolIdx);
    IMAGEMANAGER->frameRender("게임종료버튼", getMemDC(), _gameQuit.left, _gameQuit.top, 0, _QuitIdx);
}
