#pragma once
#include "Manager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// 町とかの拠点
class SafeArea : public SuperScene {
private:
	const int heal = 30;	// 回復の表示カウント
	const int cursor = 32;	// カーソルの移動距離

	int Gr_Back;	// 背景
	int Gr_Wall;	// 壁

	vector<vector<string>> map;

	ifstream read_file;		// 読み込むファイル
	string read_line;		// 読み込んだ行（1行）
	int read_count;
	int x;
	int y;
	bool fieldflag;			// 出口にいるかどうか
	bool peopleflag;		// 一般人に触れたら
	bool itemflag;			// 道具屋に触れたら
	bool shopflag;			// ショップ画面
	bool healflag;			// 噴水に触れたら
	bool talkflag;			// 会話中かどうか
	int healcount;			// 回復のフレームカウント
	int shopmenu;			// ショップ画面
	int shopmY;		// ショップ画面でのカーソル

public:
	SafeArea();
	~SafeArea();

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
	void SetPeople(bool flag);	// 一般人に触れたら
	bool GetPeople();
	void SetItem(bool flag);	// 道具屋に触れたら
	bool GetItem();
	void SetShop(bool flag);	// ショップ画面
	bool GetShop();	
	void SetHeal(bool flag);	// 噴水に触れたら
	bool GetHeal();
	void SetTalk(bool flag);	// 会話中かどうか
	bool GetTalk();
	eStep GetStep();	// 今のステップ状況
};