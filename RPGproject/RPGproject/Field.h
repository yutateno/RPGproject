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
	int mapchip0;					// マップチップ
	int mapchip1;					
	int mapchip2;
	int mapchip3;

	vector<vector<int> > mapdata;	// マップデータ本体

	int cameraX;					// カメラの座標
	int cameraY;

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
};
