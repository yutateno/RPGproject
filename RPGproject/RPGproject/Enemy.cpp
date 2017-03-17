#include "Enemy.h"

Enemy::Enemy()
{
	// �f�t�H���g�R���X�g���N�^�͊�{�I�ɌĂ΂�Ȃ�
	ID = 0;		// 0:�e�X�g�p

	// �������m��
	attack = new Attack();

	// �Q�b�^�[�p�̕ϐ�
	damage = 0;
	
	SearchStatus();		// ID����X�e�[�^�X�擾
}
Enemy::Enemy(int ID)
{
	this->ID = ID;		// 0:�e�X�g�p

	// �������m��
	attack = new Attack();

	// �Q�b�^�[�p�̕ϐ�
	damage = 0;

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
		attack->power = 1;
		attack->width = 0;
		exp = 10;			// �o���l
		money = 100;		// ��

		graph = LoadGraph("img\\enemy.png");
		break;

	case 1:
		name = "mi!";
		hp = 5;			// �̗�
		mp = 5;			// ����
		attack->power = 2;
		attack->width = 0;
		exp = 20;		// �o���l
		money = 200;	// ��

		graph = LoadGraph("img\\enemy.png");
		break;

	case 2:
		name = "�X��";
		hp = 50;
		mp = 50;
		attack->power = 50;
		attack->width = 0;
		exp = 1;
		money = 0;

		graph = LoadGraph("img\\enemy.png");
		break;

	case 3:
		name = "�{�X";
		hp = 25;
		mp = 25;
		attack->power = 5;
		attack->width = 0;
		exp = 100;
		money = 1000;

		graph = LoadGraph("img\\enemy.png");
		break;

	default:
		// �G���[
		break;
	}
}

void Enemy::aaaDraw()
{
	DrawGraph(320 - 80, 240 - 80, graph, true);
}

void Enemy::AttackProcess()
{
	// ������
	damage = 0;

	// ������
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