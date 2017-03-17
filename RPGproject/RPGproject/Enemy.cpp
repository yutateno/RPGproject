#include "Enemy.h"

Enemy::Enemy()
{
	// デフォルトコンストラクタは基本的に呼ばれない
	ID = 0;		// 0:テスト用

	// メモリ確保
	attack = new Attack();

	// ゲッター用の変数
	damage = 0;
	
	SearchStatus();		// IDからステータス取得
}
Enemy::Enemy(int ID)
{
	this->ID = ID;		// 0:テスト用

	// メモリ確保
	attack = new Attack();

	// ゲッター用の変数
	damage = 0;

	SearchStatus();		// IDからステータス取得
}
Enemy::~Enemy()
{
	DeleteGraph(graph);
}

void Enemy::SearchStatus()
{
	switch (ID)
	{
	case 0:
		name = "default_chang!";
		hp = 10;			// 体力
		mp = 10;			// 魔力
		attack->power = 1;
		attack->width = 0;
		exp = 10;			// 経験値
		money = 100;		// 金

		graph = LoadGraph("img\\enemy.png");
		break;

	case 1:
		name = "mi!";
		hp = 5;			// 体力
		mp = 5;			// 魔力
		attack->power = 2;
		attack->width = 0;
		exp = 20;		// 経験値
		money = 200;	// 金

		graph = LoadGraph("img\\enemy.png");
		break;

	case 2:
		name = "店主";
		hp = 50;
		mp = 50;
		attack->power = 50;
		attack->width = 0;
		exp = 1;
		money = 0;

		graph = LoadGraph("img\\enemy.png");
		break;

	case 3:
		name = "ボス";
		hp = 25;
		mp = 25;
		attack->power = 5;
		attack->width = 0;
		exp = 100;
		money = 1000;

		graph = LoadGraph("img\\enemy.png");
		break;

	default:
		// エラー
		break;
	}
}

void Enemy::aaaDraw()
{
	DrawGraph(320 - 80, 240 - 80, graph, true);
}

void Enemy::AttackProcess()
{
	// 初期化
	damage = 0;

	// 仮処理
	damage = attack->power + attack->width;
}

void Enemy::SetName(string name)
{
	this->name = name;
}
string Enemy::GetName()
{
	return name;
}
void Enemy::SetHP(int hp)
{
	this->hp = hp;
}
int Enemy::GetHP()
{
	return hp;
}
void Enemy::SetMP(int mp)
{
	this->mp = mp;
}
int Enemy::GetMP()
{
	return mp;
}
void Enemy::SetATK(int attack)
{
	this->attack->power = attack;
}
int Enemy::GetATK()
{
	return damage;
}
void Enemy::SetATKName(string name)
{
	this->attack->name = name;
}
string Enemy::GetATKName()
{
	return attack->name;
}
int Enemy::GetEXP()
{
	return exp;
}
int Enemy::GetMoney()
{
	return money;
}