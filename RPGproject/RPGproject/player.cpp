#include "player.h"

Player::Player()
{
	hp = 10;			// �̗�
	mp = 10;			// ����
	x = y = 0;		// ���W
	attack = 1;		// �U����
}
Player::~Player()
{
	//DeleteGraph();
}

void Player::Draw()
{
	//DrawGraph();
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