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
	int Gr_Back;		// 背景
	int Gr_Wall;		// 壁
	int Gr_Treasure;	// 宝箱
	int Gr_Open;		// 空いてる宝箱

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

	const int flame = 30;	// フレーム
	int comment;			// 手に入れ表示
	int treasureMax;		// 宝箱の数
	int num;				// どの宝箱か
	bool treasure[10];		// 宝箱開いてるかどうか
	bool touchflag;			// 宝箱に触れているか
	bool openflag;			// 開けられたかどうか

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

	void Draw_UI();		// UI

	void MapData();

	// ゲッターセッター
	int GetMapData(int x, int y);	// マップの全体
	int GetMapWidth();				// マップの横幅
	int GetMapHeight();				// マップの縦幅
	void SetX(int x);				// カメラのＸ座標
	int GetX();
	void SetY(int y);				// カメラのＹ座標
	int GetY();
	void SetField(bool flag);	// 出口にいるかどうか
	bool GetField();
	void SetBattle(bool flag);	// 戦闘行くかどうか
	bool GetBattle();
	void SetBoss(bool flag);	//ボス戦闘に行くかどうか
	bool GetBoss();
	void SetNum(int num);		// どの宝箱か
	int GetNum();
	void SetTreasure(int num, bool treasure);	// 宝箱
	bool GetTreasure(int num);
	void SetTouch(bool flag);		// 触れたかどうか
	bool GetTouch();
	void SetOpen(bool flag);		// 開けたかどうか
	bool GetOpen();
	eStep GetStep();	// 今のステップ状況
};