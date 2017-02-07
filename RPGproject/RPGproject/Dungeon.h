#pragma once
#include "Manager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <deque>

// ダンジョン
class Dungeon : public SuperScene {
private:
	int Gr_Back;	// 背景
	int Gr_Player;	//プレイヤー
	int Gr_Wall;	//キャラ

public:
	Dungeon();
	~Dungeon();

	void UpDate();		// アップデート
	void UpDate_Start();// 開始画面アップデート
	void UpDate_Main();	// メイン画面アップデート
	void UpDate_End();	// 終了画面アップデート

	void Draw();	// 描画
	void Draw_Start();	// 開始画面描画
	void Draw_Main();	// メイン画面描画
	void Draw_End();	// 終了画面描画
};