#pragma once
#include "Manager.h"

#include <vector>
#include<fstream>
#include<iostream>
#include<string>
#include <sstream>

using namespace std;

class Field : public SuperScene {
private:
	// 画像
	int Gr_Back;					// 背景
	int mapchip1;					// マップチップ

	vector<vector<int> > mapdata;	// マップデータ本体

public:
	Field();
	~Field();

	void UpDate();		// アップデート
	void UpDate_Start();// 開始画面アップデート
	void UpDate_Main();	// メイン画面アップデート
	void UpDate_End();	// 終了画面アップデート

	void Draw();		// 描画
	void Draw_Start();	// 開始画面描画
	void Draw_Main();	// メイン画面描画
	void Draw_End();	// 終了画面描画

	void ReadMapData();	//マップデータをテキストファイルから読み込む関数

};
