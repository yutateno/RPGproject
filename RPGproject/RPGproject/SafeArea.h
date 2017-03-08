#pragma once
#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

#include "Item.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Item;

// 買い物中の状態
enum ShopMenu
{
	START, BUY, SELL, END
};

// 町とかの拠点
class SafeArea : public SuperScene {
private:
	const int heal = 30;	// 回復の表示カウント
	const int cursor = 32;	// カーソルの移動距離
	const int shop = 20;	// ショップでの売買後の表示カウント

	// 画像関連
	int Gr_Back;		// 背景
	int Gr_Wall;		// 壁
	int Gr_Exit;		// 出口
	int Gr_Murabito;	// 村人
	int Gr_Shop;		// 店
	int Gr_Yado;		// 宿
	int graph;			// 描写用

	// マップ関連
	vector<vector<string>> map;
	ifstream read_file;		// 読み込むファイル
	string read_line;		// 読み込んだ行（1行）
	int read_count;
	int x;
	int y;

	bool fieldflag;			// 出口にいるかどうか

	// 回復関連
	int healcount;			// 回復のフレームカウント
	bool healflag;			// 回復させるかどうか
	bool innflag;			// 宿の店主に触れたら
	bool healY;				// 選択肢

	// 一般人関連
	bool peopleflag;		// 一般人に触れたら
	bool talkflag;			// 会話中かどうか

	// ショップ関連
	bool itemflag;			// 道具屋に触れたら
	bool shopflag;			// ショップ画面
	int shopcount;			// ショップのフレームカウント
	ShopMenu shopmenu;		// ショップ画面
	int shopmY;				// ショップ画面でのカーソル
	bool buyflag;			// 買ったかどうか
	bool sellflag;			// 売ったかどうか

	// 擬似プレイヤー要素
	int price;				// 値段
	int money;				// 所持金

	// アイテム関連
	int ID;					// ID
	int item[9];			// アイテム
	Item *itemm;
	int itemPosition;			// アイテムの場所

	// 演出関係
	int count;

public:
	SafeArea();
	~SafeArea();

	void UpDate();		// アップデート
	void UpDate(int playerX, int playerY);
	void UpDate_Start();// 開始画面アップデート
	void UpDate_Main();	// メイン画面アップデート
	void UpDate_End();	// 終了画面アップデート

	void Draw();		// 描画
	void Draw_Start();	// 開始画面描画
	void Draw_Main(int x, int y);	// メイン画面描画
	void Draw_End();	// 終了画面描画

	void MapData();			// マップデータ関連
	void HealProcess();		// 回復のプロセス
	void PeopleProcess();	// 人とのプロセス
	void ShopProcess();		// 買い物のプロセス

	// プレイヤーがアイテムの購入に失敗した場合に呼ばれる関数
	void Refund();

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
	void SetHeal(bool flag);	// 回復するかどうか
	bool GetHeal();
	void SetInn(bool flag);		// 宿の店主に触れたかどうか
	bool GetInn();
	void SetTalk(bool flag);	// 会話中かどうか
	bool GetTalk();
	void SetBuy(bool flag);		// 買ったかどうか
	bool GetBuy();
	void SetSell(bool flag);	// 売ったかどうか
	bool GetSell();
	void SetID(int ID);			// アイテムのＩＤ
	int GetID();
	void SetItemPosition(int itemPosition);		// アイテムの位置
	int GetItemPosition();
	void SetnumID(int num, int ID);
	void SetMoney(int money);	// お金
	int GetMoney();
	eStep GetStep();	// 今のステップ状況
};