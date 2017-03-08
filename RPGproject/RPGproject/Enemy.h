#pragma once

#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

#include "Attack.h"

#include <string>

using std::string;

class Attack;

class Enemy
{
private:
	// 固有の情報
	int ID;				// 通し番号
	string name;		// 名前

	// ステータス
	int hp;				// 体力
	int mp;				// 魔力
	Attack *attack;		// 攻撃クラス
	int damage;			// ゲッター用の変数
	int exp;			// 経験値
	int money;			// かね

	// 画像
	int graph;			// 画像

public:
	Enemy();
	Enemy(int ID);					// オーバーロード基本的にこっちを使う
	~Enemy();

	void aaaDraw();					// 描画
	void AttackProcess();			// 攻撃の処理

	void SearchStatus();			// IDからステータスを取得する

	// ゲッターセッターたち
	void SetName(string name);
	string GetName();
	void SetHP(int hp);
	int GetHP();
	void SetMP(int mp);
	int GetMP();
	void SetATK(int attack);
	int GetATK();
	int GetEXP();
	int GetMoney();
};