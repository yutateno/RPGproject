#pragma once
#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

#include "Treasure.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// ダンジョン
class Dungeon : public SuperScene {
private:
	int Gr_Back;		// 背景
	int Gr_Wall;		// 壁

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

	vector<Treasure> treasure;	// 宝箱
	bool openflag;				// 開けたかどうか
	bool treasureflag;			// 宝箱になんかしたら
	string treasurename;		// 宝箱の中の名前
	int treasuremoney;			// 宝箱の中の金

	int comment;				// なんか反応の会話
	const int flame = 30;		// フレーム
	int conUI_x;				// コメントの表示位置
	int conUI_y;
	int conUI_height;
	int conUI_width;
	string str;

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

	void Draw_UI();		// UIの描画
	void Dungeon_Map();	// マップ全体

	void MapData();

	int OpenTreasure(int num);	// 宝箱が開けられた時の処理

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
	int GetTreasureNum();			// 宝箱の番号
	int GetTreasureX(int num);		// ある宝箱のＸ座標
	int GetTreasureY(int num);		// ある宝箱のＹ座標
	void SetOpen(bool flag);	// 開けたかどうか
	bool GetOpen();
	void SetTreasure(bool flag);	// 宝箱に反応したかどうか
	bool GetTreasure();
	void SetTreasureMoney(int money);	// 宝箱からお金を得たか
	int GetTreasureMoney();
	eStep GetStep();	// 今のステップ状況
};