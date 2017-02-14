#include "player.h"

Player::Player()
{
	hp = 10;			// ‘Ì—Í
	mp = 10;			// –‚—Í
	x = y = preX = preY = 0;		// À•W
	attack = 1;		// UŒ‚—Í

	graph = LoadGraph("img\\player.png");
}
Player::~Player()
{
	DeleteGraph(graph);
}

void Player::aaaDraw()
{
	DrawGraph(x, y, graph, true);
}

void Player::Move()
{
	// ’¼‘O‚ÌÀ•W•Û‘¶
	preX = x;
	preY = y;

	// ˆÚ“®
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
