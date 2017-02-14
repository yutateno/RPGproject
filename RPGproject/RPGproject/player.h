#pragma once

#include "Manager.h"

class Player
{
private:
	int hp;			// 体力
	int mp;			// 魔力
	int x, y;		// 座標
	int attack;		// 攻撃力

	int graph;		// 画像

public:
	Player();
	~Player();

	void aaaDraw();	// 描画

	void Move();	// 移動

	// ゲッターセッターたち
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
};