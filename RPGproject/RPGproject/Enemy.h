#pragma once

#include "Manager.h"

class Enemy
{
private:
	int hp;			// 体力
	int mp;			// 魔力
	int attack;		// 攻撃力

	int graph;		// 画像

public:
	Enemy();
	~Enemy();

	void aaaDraw();			// 描画

	// ゲッターセッターたち
	void SetHP(int hp);
	int GetHP();
	void SetMP(int mp);
	int GetMP();
	void SetATK(int attack);
	int GetATK();
};