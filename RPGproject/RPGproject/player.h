#pragma once

class Player
{
private:
	int hp;			// �̗�
	int mp;			// ����
	int x, y;		// ���W
	int attack;		// �U����

public:
	Player();
	~Player();

	void Draw();	// �`��

	void SetX(int x);
	int GetX();
	void SetY(int y);
	int GetY();
};