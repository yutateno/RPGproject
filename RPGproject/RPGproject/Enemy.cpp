#include "Enemy.h"

Enemy::Enemy()
{
	hp = 10;			// ‘Ì—Í
	mp = 10;			// –‚—Í
	attack = 1;		// UŒ‚—Í

	graph = LoadGraph("img\\enemy.png");
}
Enemy::~Enemy()
{
	DeleteGraph(graph);
}

void Enemy::aaaDraw()
{
	DrawGraph(0, 0, graph, true);
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