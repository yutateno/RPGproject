#include "player.h"

Player::Player()
{
	hp = 10;			// 体力
	mp = 10;			// 魔力
	x = 320 - 16;		// 座標
	preX = x;
	drawX = x;
	y = 240 - 16;
	preY = y;
	drawY = y;
	attack = 1;		// 攻撃力

	// 画像読み込み
	graph = LoadGraph("img\\player.png");
}
Player::~Player()
{
	// 画像のデータ削除
	DeleteGraph(graph);
}

void Player::aaaDraw()
{
	DrawGraph(320 - 16, 240 - 16, graph, true);
}
void Player::aaaDraw(int mapwidth, int mapheight)
{
	if (x < 320 - 16)
	{
		drawX = x;
	}
	else if (x > (mapwidth * 32 - 32) - (320 - 16))
	{
		drawX = x - (mapwidth * 32 - 640);
	}
	else
	{
		drawX = 320 - 16;
	}

	if (y < 240 - 16)
	{
		drawY = y;
	}
	else if (y >(mapheight * 32 - 32) - (240 - 16))
	{
		drawY = y - (mapheight * 32 - 480);
	}
	else
	{
		drawY = 240 - 16;
	}

	// プレイヤー本体
	DrawGraph(drawX, drawY, graph, true);
}

void Player::Move()
{
	// 直前の座標保存
	preX = x;
	preY = y;

	// 移動
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
