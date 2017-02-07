#pragma once
#include "Manager.h"

class Title : public SuperScene {
private:
	int Icon_x;		// ボタンのx座標
	int Icon_y;		// ボタンのy座標
	bool Icon_area;	// ボタンの操作位置
	
	int Gr_Back;	// 背景

public:
	Title();
	~Title();

	void UpDate();		// アップデート
	void UpDate_Start();// 開始画面アップデート
	void UpDate_Main();	// メイン画面アップデート
	void UpDate_End();	// 終了画面アップデート

	void Draw();		// 描画
	void Draw_Start();	// 開始画面描画
	void Draw_Main();	// メイン画面描画
	void Draw_End();	// 終了画面描画
};