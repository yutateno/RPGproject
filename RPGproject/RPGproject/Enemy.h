#pragma once

#include "Manager.h"

#include <string>

using std::string;

class Enemy
{
private:
	string name;		// 名前
	int hp;				// 体力
	int mp;				// 魔力
	int attack;			// 攻撃力

	int graph;			// 画像

public:
	Enemy();
	Enemy(string name, int hp, int mp, int attack, int graph);	// オーバーロード基本的にこっちを使う
	~Enemy();

	void aaaDraw();			// 描画
	int AttackProcess();			// 攻撃の処理

	// ゲッターセッターたち
	void SetName(string name);
	string GetName();
	void SetHP(int hp);
	int GetHP();
	void SetMP(int mp);
	int GetMP();
	void SetATK(int attack);
	int GetATK();
};