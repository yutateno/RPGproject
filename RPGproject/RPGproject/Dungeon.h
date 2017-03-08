#pragma once
#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// ダンジョン
class Dungeon : public SuperScene {
private:
	int Gr_Back;	// 背景
	int Gr_Wall;	// 壁

	// マップ
	vector<vector<string>> map;

	ifstream read_file;		// 読み込むファイル
	string read_line;		// 読み込んだ行（1行）
	int read_count;			// 読み込む列
	int x;					// 画面表示のｘ座標
	int y;					// 画面表示のｘ座標
	bool fieldflag;			// フィールド画面へ行くかどうか
	bool battleflag;		// 戦闘画面へ行くかどうか
	bool bossflag;			// ボス戦闘へ行くかどうか

public:
	Dungeon();
	~Dungeon();

	void UpDate();		// アップデート
	void UpDate(int playerX, int playerY);
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
	int GetMapWidth();
	int GetMapHeight();
	void SetX(int x);
	int GetX();
	void SetY(int y);
	int GetY();
	void SetField(bool flag);	// 出口にいるかどうか
	bool GetField();
	void SetBattle(bool flag);	// 戦闘行くかどうか
	bool GetBattle();
	void SetBoss(bool flag);	//ボス戦闘に行くかどうか
	bool GetBoss();
	eStep GetStep();	// 今のステップ状況
};