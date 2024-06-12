#include "Stdafx.h"
#include "MainGame.h"
#include <crtdbg.h>
#include <memory.h>
// =================
// # 전역 변수 #
// =================
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0,0 };

// =================
// # 함수 전방선언 #
// =================
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

MainGame* _mg;

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR    lpszCmdParam,
    int       nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  
    _mg = new MainGame();
    _hInstance = hInstance;

    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); 
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); 
    wndClass.hIcon = LoadIcon(NULL, IDC_APPSTARTING); 
    wndClass.hInstance = hInstance; 
    wndClass.lpfnWndProc = (WNDPROC)WndProc;
    wndClass.lpszClassName = WIN_NAME;
    wndClass.lpszMenuName = NULL; 
    wndClass.style = CS_HREDRAW | CS_VREDRAW; 

    RegisterClass(&wndClass);

#ifdef FULL_SCREEN

    DEVMODE dm;

    ZeroMemory(&dm, sizeof(DEVMODE));
    dm.dmSize = sizeof(DEVMODE);
    dm.dmBitsPerPel = 32;
    dm.dmPelsWidth = 1980;
    dm.dmPelsHeight = 1020;
    dm.dmDisplayFrequency = 60;             //재생빈도 60Hz

    dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

    if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
        ChangeDisplaySettings(&dm, 0);
    }

    _hWnd = CreateWindow
    (
        WIN_NAME, 
        WIN_NAME, 
        WINSTYLE, 
        WINSTART_X, 
        WINSTART_Y, 
        WINSIZE_X, 
        WINSIZE_Y, 
        NULL,
        (HMENU)NULL,
        hInstance,
        NULL 
    );

    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

#else

    
    _hWnd = CreateWindow
    (
        WIN_NAME, 
        WIN_NAME, 
        WINSTYLE, 
        WINSTART_X,
        WINSTART_Y,
        WINSIZE_X, 
        WINSIZE_Y, 
        NULL, 
        (HMENU)NULL, 
        hInstance, 
        NULL 
    );

    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

#endif

    ShowWindow(_hWnd, nCmdShow);

    if (FAILED(_mg->init()))
    {
        return 0;
    }

    MSG message;

    while (true)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            if(message.message == WM_QUIT) break;

            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        
        else
        {
            TIMEMANAGER->update(60.0f);
            _mg->update();
            _mg->render();
        }
    }
    
    _mg->release();
    UnregisterClass(WIN_NAME, hInstance);
    return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    return _mg->MainProc(hWnd, IMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0,0,width,height };

    AdjustWindowRect(&rc, WINSTYLE, false);
    SetWindowPos(_hWnd, NULL, x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
}