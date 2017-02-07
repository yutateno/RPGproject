#pragma once
#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

#include "Title.h"
#include "Field.h"
#include "Battle.h"
#include "GameOver.h"
#include "SafeArea.h"
#include "GameClear.h"
#include "Dungeon.h"


class Manager :public SuperScene {
private:
	eScene NowScene;

	// 各シーンの実体
	Title* title;
	Field* field;
	Battle* battle;
	SafeArea* safeArea;
	Dungeon* dungeon;
	GameOver* gameOver;
	GameClear* gameClear;

	// 各シーンの移行処理
	void ChengeScene_Title();
	void ChengeScene_Field();
	void ChengeScene_Battle();
	void ChengeScene_SafeArea();
	void ChengeScene_Dungeon();
	void ChengeScene_GameOver();
	void ChengeScene_GameClear();


public:
	Manager();
	~Manager();

	void UpDate();		// アップデート
	void UpDate_Start() {}	// 開始画面アップデート
	void UpDate_Main() {}		// メイン画面アップデート
	void UpDate_End() {}		// 終了画面アップデート
	void Draw();		// 描画
	void Draw_Start() {}		// 開始画面描画
	void Draw_Main() {}		// メイン画面描画
	void Draw_End() {}		// 終了画面描画
};