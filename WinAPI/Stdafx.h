#pragma once
#pragma warning(disable : 4005)
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <wincodecsdk.h>
#pragma comment(lib,"windowscodecs.lib")
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma comment (lib, "msimg32.lib") //마이크로소프트(ms) 이미지(img) 32비트(32) 라이브러리
#pragma comment (lib,"winmm.lib")
// 동영상
#include <Vfw.h>
#pragma comment (lib, "Vfw32.lib")

#include <SDKDDKVer.h>

// =====================
//! C 런타임 헤더 파일
// =====================
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
//#include <assert.h>
#include <MMSystem.h>
#include <conio.h>


// =====================
//! C++ 런타임 헤더 파일
// =====================
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <bitset>
#include <cassert>
#include <algorithm>
#include <functional>
#include <fstream>

using namespace std;

// =====================
//! 사용자 정의 헤더파일
// =====================
#include "CommonMacroFunction.h"  
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TempSoundManager.h"
#include "Utils.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "TileManager.h"
#include "CSoundMgr.h"
#include "CSound.h"

using namespace MY_UTIL;

// =====================
//! 싱글톤
// =====================
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define TILEMANAGER TileManager::getSingleton()
#define SOUNDMANAGER CSoundMgr::getSingleton()

/*
! D2D/D3D 헤더 파일
#include <D2D1.h>
#include <d2d1helper.h>
#include <d3dx9.h>
#include <D3DX11.h>
#include <d3d11shader.h>
#include <dinput.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

ID2D1Factory* _ID2DFactory = nullptr;
ID2D1HwndRenderTarget* _ID2DRenderTarget = nullptr;
*/


//==============================
// # 매크로 # (윈도우창 초기화)
//==============================

//! 전체 화면
//#define FULL_SCREEN

#ifdef FULL_SCREEN

#define WIN_NAME (LPSTR)(TEXT("WindowsAPI"))
#define WINSTART_X 0
#define WINSTART_Y 0
#define WINSIZE_X GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE WS_POPUPWINDOW | WS_MAXIMIZE

#else

#define WIN_NAME (LPSTR)(TEXT("DiabloⅡ"))
#define WINSTART_X 400
#define WINSTART_Y 100
#define WINSIZE_X 800
#define WINSIZE_Y 600
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#endif

//==============================
// # 매크로 함수 #
//==============================
#define SAFE_DELETE(p)       {if(p){delete(p); (p) = nullptr;}}   //안전하게 초기화
#define SAFE_DELETE_ARRAY(p) {if(p){delete[] (p); (p)=nullptr;}}  //복수 객체일 경우
#define SAFE_RELEASE(p)      {if(p) {(p)->release();(p)=nullptr;}


//==============================
// # 전역 변수 #
//==============================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;
