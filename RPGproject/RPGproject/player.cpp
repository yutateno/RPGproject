#include "player.h"

Player::Player()
{
	hp = 10;			// �̗�
	mp = 10;			// ����
<<<<<<< HEAD
	x = 320 - 16;		// ���W
	preX = x;
	y = 240 - 16;
	preY = y;
=======
	//x = y = preX = preY = 0;		// ���W
	x = preX = 320;
	y = preY = 240;
>>>>>>> baa1353da0efc11ce53f5532cd2d74a888a89407
	attack = 1;		// �U����

	graph = LoadGraph("img\\player.png");
}
Player::~Player()
{
	DeleteGraph(graph);
}

void Player::aaaDraw()
{
<<<<<<< HEAD
	DrawGraph(320 - 16, 240 - 16, graph, true);
=======
	DrawGraph(320, 240, graph, true);
>>>>>>> baa1353da0efc11ce53f5532cd2d74a888a89407
}

void Player::Move()
{
	// ���O�̍��W�ۑ�
	preX = x;
	preY = y;

	// �ړ�
	if (KeyData::Get(KEY_INPUT_UP) > 0)
	{
		y--;
	}
	else if (KeyData::Get(KEY_INPUT_DOWN) > 0)
	{
		y++;
	}
	else if (KeyData::Get(KEY_INPUT_LEFT) > 0)
	{
		x--;
	}
	else if (KeyData::Get(KEY_INPUT_RIGHT) > 0)
	{
		x++;
	}
}

void Player::MoveReset()
{
	x = preX;
	y = preY;
}

void Player::SetX(int x)
{
	this->x = x;
}
int Player::GetX()
{
	return x;
}
void Player::SetY(int y)
{
	this->y = y;
}
int Player::GetY()
{
	return y;
}
void Player::SetHP(int hp)
{
	this->hp = hp;
}
int Player::GetHP()
{
	return hp;
}
void Player::SetMP(int mp)
{
	this->mp = mp;
}
int Player::GetMP()
{
	return mp;
}
void Player::SetATK(int attack)
{
	this->attack = attack;
}
int Player::GetATK()
{
	return attack;
}
