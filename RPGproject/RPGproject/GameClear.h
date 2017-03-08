#pragma once
#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

// 町とかの拠点
class GameClear : public SuperScene {
private:
	int Gr_Back;	// 背景

public:
	GameClear();
	~GameClear();

	void UpDate();		// アップデート
	void UpDate_Start();// 開始画面アップデート
	void UpDate_Main();	// メイン画面アップデート
	void UpDate_End();	// 終了画面アップデート

	void Draw();	// 描画
	void Draw_Start();	// 開始画面描画
	void Draw_Main();	// メイン画面描画
	void Draw_End();	// 終了画面描画
};