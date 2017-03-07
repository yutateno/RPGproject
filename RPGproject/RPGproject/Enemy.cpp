#include "Enemy.h"

Enemy::Enemy()
{
	// デフォルトコンストラクタは基本的に呼ばれない
	ID = 0;		// 0:テスト用
	
	SearchStatus();		// IDからステータス取得
}
Enemy::Enemy(int ID)
{
	this->ID = ID;		// 0:テスト用

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
		attack = 1;			// 攻撃力
		exp = 10;			// 経験値

		graph = LoadGraph("img\\enemy.png");
		break;

	case 1:
		name = "mi!";
		hp = 5;			// 体力
		mp = 5;			// 魔力
		attack = 2;		// 攻撃力
		exp = 20;		// 経験値

		graph = LoadGraph("img\\enemy.png");

	default:
		// エラー
		break;
	}
}

void Enemy::aaaDraw()
{
	DrawGraph(320, 240, graph, true);
}

int Enemy::AttackProcess()
{
	// 仮処理
	return attack;
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
	this->attack = attack;
}
int Enemy::GetATK()
{
	return attack;
}
int Enemy::GetEXP()
{
	return exp;
}