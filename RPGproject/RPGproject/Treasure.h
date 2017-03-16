#pragma once

#include "DxLib.h"
#include "Scene.h"
#include "Input.h"

#include "Item.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Treasure
{
private:
	// 画像
	int closeGraph;
	int openGraph;

	// ステータス
	int ID;			// 管理番号
	bool open;		// 開けられているかどうか
	int X, Y;		// 座標
	int itemID;		// 中のアイテムのＩＤ
	int money;		// 中に入っている金額

public:
	// コンストラクタとデストラクタ
	Treasure();
	Treasure(int ID);
	~Treasure();

	// IDからステータスを初期化する関数
	void Initialize();

	// 宝箱が開けられた時の処理
	void OpenProcess();

	// 描写
	void Draw(int cameraX, int cameraY);

	// ゲッター
	int GetID();
	bool GetOpen();
	int GetX();
	int GetY();
	int GetItemID();
	int GetMoney();
	string GetName();
};