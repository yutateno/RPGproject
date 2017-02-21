#include "Enemy.h"

Enemy::Enemy()
{
	name = "default_chang!";
	hp = 10;			// �̗�
	mp = 10;			// ����
	attack = 1;			// �U����

	graph = LoadGraph("img\\enemy.png");
}
Enemy::Enemy(string name, int hp, int mp, int attack, int graph)
{
	this->name = name;
	this->hp = hp;			// �̗�
	this->mp = mp;			// ����
	this->attack = attack;			// �U����

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
	// ������
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