#include "Enemy.h"

Enemy::Enemy()
{
	name = "default_chang!";
	hp = 10;			// ‘Ì—Í
	mp = 10;			// –‚—Í
	attack = 1;			// UŒ‚—Í

	graph = LoadGraph("img\\enemy.png");
}
Enemy::Enemy(string name, int hp, int mp, int attack, int graph)
{
	this->name = name;
	this->hp = hp;			// ‘Ì—Í
	this->mp = mp;			// –‚—Í
	this->attack = attack;			// UŒ‚—Í

	this->graph = graph;
}
Enemy::~Enemy()
{
	DeleteGraph(graph);
}

void Enemy::aaaDraw()
{
	DrawGraph(0, 0, graph, true);
}

int Enemy::AttackProcess()
{
	// ‰¼ˆ—
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