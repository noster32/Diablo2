#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"
#include "Player.h"
#include "Inventory.h"
#include "WAYPOINT.h"

GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene = nullptr;


DWORD CALLBACK loadingThread(LPVOID prc)
{
    SceneManager::_readyScene->init();
    SceneManager::_currentScene = SceneManager::_readyScene;

    SceneManager::_loadingScene->release();
    SceneManager::_loadingScene = nullptr;
    SceneManager::_readyScene = nullptr;

    return 0;
}

HRESULT SceneManager::init(void)
{
    _currentScene = nullptr;
    _loadingScene = nullptr;
    _readyScene = nullptr;
    _display = _isloadingImg = false;
    _isOpening = true;
    
    return S_OK;
}

void SceneManager::release(void)
{
    mapSceneIter miSceneList = _mSceneList.begin();
    for (; miSceneList != _mSceneList.end();)
    {
        if (miSceneList->second != nullptr)
        {
            if (miSceneList->second == _currentScene)
            {
                miSceneList->second->release();
            }
            SAFE_DELETE(miSceneList->second);
            miSceneList = _mSceneList.erase(miSceneList);
        }
        else ++miSceneList;
    }
    _mSceneList.clear();
}

void SceneManager::update(void)
{
    if (_loadingScene)
    {
        _readyScene = _loadingScene;
       // loadingThread(WndProc);
        //cout << "È®ÀÎ" << endl;
    }
    if (_currentScene) _currentScene->update();

}

void SceneManager::render(void)
{
    if (_loadingScene) _loadingScene->render();
    if (_currentScene) _currentScene->render();
}

GameNode* SceneManager::addScene(string sceneName, GameNode* scene)
{
    if (!scene) return nullptr;

    _mSceneList.insert(make_pair(sceneName, scene));

    return scene;
}

GameNode* SceneManager::addLodingScene(string loadingScene, GameNode* scene)
{
    if (!scene) return nullptr;

    _mLoadingSceneList.insert(make_pair(loadingScene, scene));

    return scene;
}

HRESULT SceneManager::changeScene(string sceneName)
{
    mapSceneIter find = _mSceneList.find(sceneName);

    if (find == _mSceneList.end()) return E_FAIL;
    if (find->second == _currentScene) return S_OK;

    if (SUCCEEDED(find->second->init()))
    {
        if (_currentScene != nullptr)
        {
            _currentScene->release();
        }
        _currentScene = find->second;
        return S_OK;
    }

    return E_FAIL;
}
