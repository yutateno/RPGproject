#pragma once
#include "Manager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// ダンジョン
class Dungeon : public SuperScene {
private:
	int Gr_Back;	// 背景
	int Gr_Wall;

	vector<vector<string>> map;

	ifstream read_file;		// 読み込むファイル
	string read_line;		// 読み込んだ行（1行）
	int read_count;
	int x;
	int y;

public:
	Dungeon();
	~Dungeon();

	void UpDate();		// アップデート
	void UpDate_Start();// 開始画面アップデート
	void UpDate_Main();	// メイン画面アップデート
	void UpDate_End();	// 終了画面アップデート

	void Draw();	// 描画
	void Draw_Start();	// 開始画面描画
	void Draw_Main(int x, int y);	// メイン画面描画
	void Draw_End();	// 終了画面描画

	void MapData();

	// ゲッターセッター
	int GetMapData(int x, int y);
	void SetX(int x);
	int GetX();
	void SetY(int y);
	int GetY();
};