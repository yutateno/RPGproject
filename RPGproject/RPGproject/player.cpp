#include "player.h"

Player::Player()
{
	hp = 10;			// ‘Ì—Í
	mp = 10;			// –‚—Í
	x = y = 0;		// À•W
	attack = 1;		// UŒ‚—Í
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