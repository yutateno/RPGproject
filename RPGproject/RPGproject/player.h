#pragma once

#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

#include "Item.h"
#include "Attack.h"

#include <string>

using std::string;

// 向き
enum Direction { UP, DOWN, LEFT, RIGHT };

class Attack;
class Item;

class Player
{
private:
	string name;			// 名前
	int lv;					// レベル
	int exp;				// 経験値
	int maxHP;				// 体力の最大値
	int hp;					// 体力
	int maxMP;				// MPの最大値
	int mp;					// 魔力
	int x, y;				// 座標
	int preX, preY;			// 直前の座標
	int drawX, drawY;		// 描画用の座標
	Direction direction;	// 向いている方向
	int speed;				// 移動スピード。戦闘ステータスではない
	int itemMax;			// アイテムの最大所持量
	Item *item[9];			// アイテム
	int ID;

	Attack* attack;			// 攻撃クラス

	bool menuFlag;			// メニュー画面を開いているかどうかのフラグ
	int cursorX, cursorY;	// カーソルの座標
	int listNum;			// メニューの項目がいくつあるか
	bool mItemFlag;			// アイテム画面を開いているかどうかのフラグ
	bool mItemUseFlag;		// アイテムを使ったかどうかのフラグ
	string itemEffectText;	// アイテムの効果描写用
	bool mStatusFlag;		// ステータス画面を開いているかのフラグ

	int money;			// お金

	int graph;			// 画像

	bool treasure[10];	// 宝箱（空いてるかどうか
	int treasureMax;

public:
	Player();
	~Player();

	void aaaDraw();			// 描画
	void aaaDraw(int mapwidth,int mapheight);			// 描画

	void Process();			// ほかの処理を内包する関数

	void Menu();			// メニュー
	void Move();			// 移動
	void MoveReset();		// 直前の動きをリセット

	bool GetmenuFlag();		//メニュー画面を開いてるかどうか

	bool BuyItem(int ID);
	void SellItem(int num);

	// ゲッターセッターたち
	void SetName(string name);
	string GetName();
	void SetLV(int lv);
	int GetLV();
	void SetEXP(int exp);
	int GetEXP();
	void SetX(int x);
	int GetX();
	void SetY(int y);
	int GetY();
	void SetHP(int hp);
	int GetHP();
	void SetMP(int mp);
	int GetMP();
	void SetMaxHP(int maxHP);
	int GetMaxHP();
	void SetMaxMP(int MaxMP);
	int GetMaxMP();
	void SetATK(int width);
	int GetATK();
	void SetPower(int power);
	int GetPower();
	void SetATKName(string name);
	string GetATKName();
	int GetID(int num);
	void SetMoney(int money);
	int GetMoney();
	void SetTreasure(int num, bool treasure);
	bool GetTreasure(int num);
	void SetDirection(Direction direction);
	Direction GetDirection();
};