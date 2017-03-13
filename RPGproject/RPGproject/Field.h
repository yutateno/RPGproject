#pragma once
#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

#include "Treasure.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Field : public SuperScene {
private:
	// 画像
	int Gr_Back;					// 背景
	int mapchip[4];					// マップチップ
	int mapchipForID;				// 描写用の変数

	// マップデータ関係
	ifstream ifs;					// ファイルオープン用
	vector<vector<int> > mapdata;	// マップデータ本体
	int mapchipNum;					// マップチップの種類数
	int mapchipSize;				// マップチップのサイズ

	// カメラ関係
	int cameraX;					// カメラの座標
	int cameraY;					// カメラの座標

	// 演出関係
	int count;						// (フレーム)時間をカウントする

	// 宝箱関係
	vector<Treasure> treasure;

public:
	Field();
	~Field();

	void UpDate();		// アップデート
	void UpDate(int playerX, int playerY);			// 基本的に使用するオーバーロード
	void UpDate_Start();// 開始画面アップデート
	void UpDate_Main();	// メイン画面アップデート
	void UpDate_Main(int playerX, int playerY);		// 基本的に使用するオーバーロード
	void UpDate_End();	// 終了画面アップデート

	void Draw();		// 描画
	void Draw_Start();	// 開始画面描画
	void Draw_Main();	// メイン画面描画
	void Draw_End();	// 終了画面描画

	void ReadMapData();	//マップデータをテキストファイルから読み込む関数

	// 宝箱が開けられた時の処理
	int OpenTreasure(int num);

	// ゲッターセッター
	void SetMapData(int x, int y, int data);
	int GetMapData(int x, int y);
	int GetMapWidth();
	int GetMapHeight();
	void SetStep(eStep step);
	eStep GetStep();
	void SetNextScene(eScene nextScene);
	void SetCamera(int x, int y);
	void SetCameraX(int x);
	void SetCameraY(int y);
	int GetTreasureNum();
	int GetTreasureX(int num);
	int GetTreasureY(int num);
};
