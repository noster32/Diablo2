#pragma once
#include "SingletonBase.h"
class GameNode;
class Player;
class Inventory;
class WAYPOINT;
class SceneManager : public SingletonBase <SceneManager>
{
private:
	typedef map<string, GameNode*> mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	static GameNode* _currentScene;
	static GameNode* _loadingScene;
	static GameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	bool _display;		//출력할지
	bool _isOpening;
	Player* _p;
	Inventory* _inven;
	WAYPOINT* _WAYP;

	bool _isloadingImg;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	GameNode* addScene(string sceneName, GameNode* scene);
	GameNode* addLodingScene(string loadingScene, GameNode* scene);

	HRESULT changeScene(string sceneName);
	friend DWORD CALLBACK loadingThread(LPVOID prc);

	bool getDisplayUI() { return _display; }
	void setDisplayUI(bool i) { _display = i; }
	bool getIsOpening() { return _isOpening; }
	void setIsOpening(bool i) { _isOpening = i; }
	Player* getPLAYER() { return _p; }
	void setPLAYER(Player* p) { _p = p; }

	Inventory* getInven() { return _inven; }
	void setInven(Inventory* inven) { _inven = inven; }

	WAYPOINT* getWAYP() { return _WAYP; }
	void setWAYP(WAYPOINT* wayp) { _WAYP = wayp; }

	bool getIsLoadingImg() { return _isloadingImg; }
	void setIsLoadingImg(bool l) { _isloadingImg = l; }

	SceneManager() {}
	~SceneManager() {}
};

