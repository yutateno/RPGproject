#pragma once

#include "Manager.h"

class Enemy
{
private:
	int hp;			// �̗�
	int mp;			// ����
	int attack;		// �U����

	int graph;		// �摜

public:
	Enemy();
	~Enemy();

	void aaaDraw();			// �`��

	// �Q�b�^�[�Z�b�^�[����
	void SetHP(int hp);
	int GetHP();
	void SetMP(int mp);
	int GetMP();
	void SetATK(int attack);
	int GetATK();
};