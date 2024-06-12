#include "Stdafx.h"
#include "LoadingScene.h"

HRESULT LoadingScene::init(void)
{
	_loadingTest = new Loading;
	_loadingTest->init();
	_loadingTest->LoadingFrameImage("Dead", "Resources/Images/Object/Enemies/Boss_Dead.bmp", 0.0f, 0.0f, 39545 * 1.3, 329 * 1.3, 142, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("IdleD", "Resources/Images/Object/Enemies/Neutral0.bmp", 0.0f, 0.0f, 3158 * 1.3, 158 * 1.3, 12, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("IdleLD", "Resources/Images/Object/Enemies/Neutral1.bmp", 0.0f, 0.0f, 3158 * 1.3, 157 * 1.4, 12, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("IdleL", "Resources/Images/Object/Enemies/Neutral2.bmp", 0.0f, 0.0f, 3158 * 1.3, 166 * 1.3, 12, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("IdleLU", "Resources/Images/Object/Enemies/Neutral3.bmp", 0.0f, 0.0f, 3158 * 1.3, 164 * 1.3, 12, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("IdleU", "Resources/Images/Object/Enemies/Neutral4.bmp", 0.0f, 0.0f, 3158 * 1.3, 192 * 1.3, 12, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("IdleRU", "Resources/Images/Object/Enemies/Neutral5.bmp", 0.0f, 0.0f, 3158 * 1.3, 183 * 1.3, 12, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("IdleR", "Resources/Images/Object/Enemies/Neutral6.bmp", 0.0f, 0.0f, 3158 * 1.3, 161 * 1.3, 12, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("IdleRD", "Resources/Images/Object/Enemies/Neutral7.bmp", 0.0f, 0.0f, 3158 * 1.3, 167 * 1.3, 12, 1, true, RGB(255, 0, 255));

	_loadingTest->LoadingFrameImage("WalkD", "Resources/Images/Object/Enemies/Walk0.bmp", 0.0f, 0.0f, 1515 * 1.3, 166 * 1.3, 12, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("WalkLD", "Resources/Images/Object/Enemies/Walk1.bmp", 0.0f, 0.0f, 2004 * 1.3, 171 * 1.3, 12, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("WalkL", "Resources/Images/Object/Enemies/Walk2.bmp", 0.0f, 0.0f, 2556 * 1.3, 160 * 1.3, 12, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("WalkLU", "Resources/Images/Object/Enemies/Walk3.bmp", 0.0f, 0.0f, 2340 * 1.3, 161 * 1.3, 12, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("WalkU", "Resources/Images/Object/Enemies/Walk4.bmp", 0.0f, 0.0f, 1470 * 1.3, 182 * 1.3, 12, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("WalkRU", "Resources/Images/Object/Enemies/Walk5.bmp", 0.0f, 0.0f, 2430 * 1.3, 161 * 1.3, 12, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("WalkR", "Resources/Images/Object/Enemies/Walk6.bmp", 0.0f, 0.0f, 2520 * 1.3, 160 * 1.3, 12, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("WalkRD", "Resources/Images/Object/Enemies/Walk7.bmp", 0.0f, 0.0f, 1968 * 1.3, 171 * 1.3, 12, 1, true, RGB(0, 0, 0));

	_loadingTest->LoadingFrameImage("RushD", "Resources/Images/Object/Enemies/Rush0.bmp", 0.0f, 0.0f, 6805 * 1.3, 210 * 1.3, 22, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("RushLD", "Resources/Images/Object/Enemies/Rush1.bmp", 0.0f, 0.0f, 6798 * 1.3, 203 * 1.3, 22, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("RushL", "Resources/Images/Object/Enemies/Rush2.bmp", 0.0f, 0.0f, 6798 * 1.3, 187 * 1.3, 22, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("RushLU", "Resources/Images/Object/Enemies/Rush3.bmp", 0.0f, 0.0f, 6798 * 1.3, 208 * 1.3, 22, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("RushU", "Resources/Images/Object/Enemies/Rush4.bmp", 0.0f, 0.0f, 6805 * 1.3, 245 * 1.3, 22, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("RushRU", "Resources/Images/Object/Enemies/Rush5.bmp", 0.0f, 0.0f, 6798 * 1.3, 233 * 1.3, 22, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("RushR", "Resources/Images/Object/Enemies/Rush6.bmp", 0.0f, 0.0f, 6798 * 1.3, 179 * 1.3, 22, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("RushRD", "Resources/Images/Object/Enemies/Rush7.bmp", 0.0f, 0.0f, 6798 * 1.3, 200 * 1.3, 22, 1, true, RGB(255, 0, 255));

	_loadingTest->LoadingFrameImage("RedHoseD", "Resources/Images/Object/Enemies/Lightning0.bmp", 0.0f, 0.0f, 3400 * 1.3, 201 * 1.3, 17, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("RedHoseLD", "Resources/Images/Object/Enemies/Lightning1.bmp", 0.0f, 0.0f, 3570 * 1.3, 203 * 1.3, 17, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("RedHoseL", "Resources/Images/Object/Enemies/Lightning2.bmp", 0.0f, 0.0f, 4016 * 1.3, 213 * 1.3, 17, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("RedHoseLU", "Resources/Images/Object/Enemies/Lightning3.bmp", 0.0f, 0.0f, 3847 * 1.3, 232 * 1.3, 17, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("RedHoseU", "Resources/Images/Object/Enemies/Lightning4.bmp", 0.0f, 0.0f, 3480 * 1.3, 237 * 1.3, 17, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("RedHoseRU", "Resources/Images/Object/Enemies/Lightning5.bmp", 0.0f, 0.0f, 3610 * 1.3, 208 * 1.3, 17, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("RedHoseR", "Resources/Images/Object/Enemies/Lightning6.bmp", 0.0f, 0.0f, 4055 * 1.3, 198 * 1.3, 17, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("RedHoseRD", "Resources/Images/Object/Enemies/Lightning7.bmp", 0.0f, 0.0f, 3675 * 1.3, 198 * 1.3, 17, 1, true, RGB(0, 0, 0));

	_loadingTest->LoadingFrameImage("flameCircleD", "Resources/Images/Object/Enemies/FlameCircle0.bmp", 0.0f, 0.0f, 4986 * 1.3, 171 * 1.3, 18, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("flameCircleLD", "Resources/Images/Object/Enemies/FlameCircle1.bmp", 0.0f, 0.0f, 4986 * 1.3, 167 * 1.3, 18, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("flameCircleL", "Resources/Images/Object/Enemies/FlameCircle2.bmp", 0.0f, 0.0f, 4986 * 1.3, 169 * 1.3, 18, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("flameCircleLU", "Resources/Images/Object/Enemies/FlameCircle3.bmp", 0.0f, 0.0f, 4986 * 1.3, 191 * 1.3, 18, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("flameCircleU", "Resources/Images/Object/Enemies/FlameCircle4.bmp", 0.0f, 0.0f, 4986 * 1.3, 186 * 1.3, 18, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("flameCircleRU", "Resources/Images/Object/Enemies/FlameCircle5.bmp", 0.0f, 0.0f, 4986 * 1.3, 173 * 1.3, 18, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("flameCircleR", "Resources/Images/Object/Enemies/FlameCircle6.bmp", 0.0f, 0.0f, 4986 * 1.3, 174 * 1.3, 18, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("flameCircleRD", "Resources/Images/Object/Enemies/FlameCircle7.bmp", 0.0f, 0.0f, 4986 * 1.3, 177 * 1.3, 18, 1, true, RGB(255, 0, 255));

	_loadingTest->LoadingFrameImage("flameCircle", "Resources/Images/Object/Enemies/FlameCircleObj.bmp", 0.0f, 0.0f, 2442, 167, 37, 1, true,
		RGB(0, 0, 0));

	_loadingTest->LoadingFrameImage("LightningD", "Resources/Images/Object/Enemies/RedHose0.bmp", 0.0f, 0.0f, 1800, 157, 15, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("LightningLD", "Resources/Images/Object/Enemies/RedHose1.bmp", 0.0f, 0.0f, 2820, 146, 15, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("LightningL", "Resources/Images/Object/Enemies/RedHose2.bmp", 0.0f, 0.0f, 3315, 145, 15, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("LightningLU", "Resources/Images/Object/Enemies/RedHose3.bmp", 0.0f, 0.0f, 2325, 148, 15, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("LightningU", "Resources/Images/Object/Enemies/RedHose4.bmp", 0.0f, 0.0f, 1545, 152, 15, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("LightningRU", "Resources/Images/Object/Enemies/RedHose5.bmp", 0.0f, 0.0f, 2430, 142, 15, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("LightningR", "Resources/Images/Object/Enemies/RedHose6.bmp", 0.0f, 0.0f, 3045, 133, 15, 1, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("LightningRD", "Resources/Images/Object/Enemies/RedHose7.bmp", 0.0f, 0.0f, 2535, 144, 15, 1, true, RGB(255, 0, 255));

	_loadingTest->LoadingFrameImage("FireStormD", "Resources/Images/Object/Enemies/FireStorm0.bmp", 0.0f, 0.0f, 3040 * 1.3, 252 * 1.3, 16, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("FireStormLD", "Resources/Images/Object/Enemies/FireStorm1.bmp", 0.0f, 0.0f, 3129 * 1.3, 259 * 1.3, 16, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("FireStormL", "Resources/Images/Object/Enemies/FireStorm3.bmp", 0.0f, 0.0f, 3609 * 1.3, 262 * 1.3, 16, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("FireStormLU", "Resources/Images/Object/Enemies/FireStorm6.bmp", 0.0f, 0.0f, 3696 * 1.3, 257 * 1.3, 16, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("FireStormU", "Resources/Images/Object/Enemies/FireStorm5.bmp", 0.0f, 0.0f, 3792 * 1.3, 258 * 1.3, 16, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("FireStormRU", "Resources/Images/Object/Enemies/FireStorm7.bmp", 0.0f, 0.0f, 3168 * 1.3, 295 * 1.3, 16, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("FireStormR", "Resources/Images/Object/Enemies/FireStorm4.bmp", 0.0f, 0.0f, 4138 * 1.3, 261 * 1.3, 16, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("FireStormRD", "Resources/Images/Object/Enemies/FireStorm2.bmp", 0.0f, 0.0f, 3560 * 1.3, 292 * 1.3, 16, 1, true, RGB(0, 0, 0));

	_loadingTest->LoadingFrameImage("FireStormObj", "Resources/Images/Object/Enemies/FireStormObj.bmp", 0.0f, 0.0f, 2442, 89, 37, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("FireStormEnd", "Resources/Images/Object/Enemies/Fire-end.bmp", 0.0f, 0.0f, 960, 81, 16, 1, true, RGB(0, 0, 0));
	_loadingTest->LoadingFrameImage("FireStormObj2", "Resources/Images/Object/Enemies/FireStormObj2.bmp", 0.0f, 0.0f, 3498, 89, 53, 1, true, RGB(0, 0, 0));

	_loadingTest->LoadingImage("검은배경화면", "Resources/Images/Object/blackBG.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

	_loadingTest->LoadingImage("HpBar", "Resources/Images/Object/bossHpBar.bmp", 0.0f, 0.0f, 128, 32);
	_loadingTest->LoadingImage("HpBarBG", "Resources/Images/Object/bossHpBarBG.bmp", 0.0f, 0.0f, 128, 32);

	_loadingTest->LoadingImage("Alter", "Resources/Images/Object/alter.bmp", 0.0f, 0.0f, 139, 123, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("AlterActive", "Resources/Images/Object/alterActive.bmp", 0.0f, 0.0f, 1429, 453, 10, 2, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("티리엘", "Resources/Images/Object/tyrael.bmp", 0.0f, 0.0f, 15360, 1024, 30, 2, true, RGB(255, 0, 255));
	_loadingTest->LoadingImage("티리엘텍스트배경", "Resources/Images/Object/tyraelTB.bmp", 0.0f, 0.0f, 328, 125);
	_loadingTest->LoadingImage("티리엘배경블랙", "Resources/Images/Object/tyraelTBCB.bmp", 0.0f, 0.0f, 328, 125);
	_loadingTest->LoadingImage("티리엘텍스트", "Resources/Images/Object/tyraelText.bmp", 0.0f, 0.0f, 315, 160);
	_loadingTest->LoadingFrameImage("티리엘등장", "Resources/Images/Object/coming.bmp", 0.0f, 0.0f, 6355, 438, 31, 1, true, RGB(255, 0, 255));

	_loadingTest->LoadingFrameImage("PlIdleShadow", "Resources/Images/Sorceress/character/IdleShadow.bmp", 0.0f, 0.0f, 960, 1200, 16, 16, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("PlCastingShadow", "Resources/Images/Sorceress/character/castingShadow.bmp", 0.0f, 0.0f, 1358, 1440, 14, 16, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("TownWalkShadow", "Resources/Images/Sorceress/character/townWalkShadow.bmp", 0.0f, 0.0f, 480, 1200, 8, 16, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("CombatIdleShadow", "Resources/Images/Sorceress/character/combatIdleShadow.bmp", 0.0f, 0.0f, 528, 1440, 8, 16, true, RGB(255, 0, 255));
	_loadingTest->LoadingFrameImage("CombatWalkShadow", "Resources/Images/Sorceress/character/combatWalkShadow.bmp", 0.0f, 0.0f, 552, 1440, 8, 16, true, RGB(255, 0, 255));

    return S_OK;
}

void LoadingScene::release(void)
{
	_loadingTest->release();
	SAFE_DELETE(_loadingTest);
}

void LoadingScene::update(void)
{
	_loadingTest->update();
}

void LoadingScene::render(void)
{
	_loadingTest->render();
}
