#include "Enemy.h"

Enemy::Enemy()
{
	hp = 10;			// �̗�
	mp = 10;			// ����
	attack = 1;		// �U����

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