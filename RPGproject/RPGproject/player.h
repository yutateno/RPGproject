#pragma once

#include "Manager.h"

#include <string>

using std::string;

// 向き
enum Direction { UP, DOWN, LEFT, RIGHT };

class Item;

class Player
{
private:
	string name;			// 名前
	int lv;					// レベル
	int hp;					// 体力
	int mp;					// 魔力
	int x, y;				// 座標
	int preX, preY;			// 直前の座標
	int drawX, drawY;		// 描画用の座標
	int attack;				// 攻撃力
	Direction direction;	// 向いている方向
	int speed;				// 移動スピード。戦闘ステータスではない
	int itemMax;			// アイテムの最大所持量
	Item *item[9];			// アイテム

	bool menuFlag;			// メニュー画面を開いているかどうかのフラグ
	int cursorX, cursorY;	// カーソルの座標
	int listNum;			// メニューの項目がいくつあるか
	bool mItemFlag;			// アイテム画面を開いているかどうかのフラグ
	bool mStatusFlag;		// ステータス画面を開いているかのフラグ

	int graph;			// 画像

public:
	Player();
	~Player();

	void aaaDraw();			// 描画
	void aaaDraw(int mapwidth,int mapheight);			// 描画

	void Process();			// ほかの処理を内包する関数

	void Menu();			// メニュー
	void Move();			// 移動
	void MoveReset();		// 直前の動きをリセット

	// ゲッターセッターたち
	void SetName(string name);
	string GetName();
	void SetLV(int lv);
	int GetLV();
	void SetX(int x);
	int GetX();
	void SetY(int y);
	int GetY();
	void SetHP(int hp);
	int GetHP();
	void SetMP(int mp);
	int GetMP();
	void SetATK(int attack);
	int GetATK();
	void SetDirection(Direction direction);
	Direction GetDirection();
};