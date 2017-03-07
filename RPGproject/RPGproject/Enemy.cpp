#include "Enemy.h"

Enemy::Enemy()
{
	// �f�t�H���g�R���X�g���N�^�͊�{�I�ɌĂ΂�Ȃ�
	ID = 0;		// 0:�e�X�g�p
	
	SearchStatus();		// ID����X�e�[�^�X�擾
}
Enemy::Enemy(int ID)
{
	this->ID = ID;		// 0:�e�X�g�p

	SearchStatus();		// ID����X�e�[�^�X�擾
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
		hp = 10;			// �̗�
		mp = 10;			// ����
		attack = 1;			// �U����
		exp = 10;			// �o���l

		graph = LoadGraph("img\\enemy.png");
		break;

	case 1:
		name = "mi!";
		hp = 5;			// �̗�
		mp = 5;			// ����
		attack = 2;		// �U����
		exp = 20;		// �o���l

		graph = LoadGraph("img\\enemy.png");

	default:
		// �G���[
		break;
	}
}

void Enemy::aaaDraw()
{
	DrawGraph(320, 240, graph, true);
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
int Enemy::GetEXP()
{
	return exp;
}