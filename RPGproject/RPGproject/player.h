#pragma once

class Player
{
private:
	int hp;			// ‘Ì—Í
	int mp;			// –‚—Í
	int x, y;		// À•W
	int attack;		// UŒ‚—Í

public:
	Player();
	~Player();

	void Draw();	// •`‰æ

	void SetX(int x);
	int GetX();
	void SetY(int y);
	int GetY();
};