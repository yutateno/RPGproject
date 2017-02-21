#pragma once

#include "Manager.h"

#include <string>

using std::string;

class Enemy
{
private:
	string name;		// ���O
	int hp;				// �̗�
	int mp;				// ����
	int attack;			// �U����

	int graph;			// �摜

public:
	Enemy();
	Enemy(string name, int hp, int mp, int attack, int graph);	// �I�[�o�[���[�h��{�I�ɂ��������g��
	~Enemy();

	void aaaDraw();			// �`��
	int AttackProcess();			// �U���̏���

	// �Q�b�^�[�Z�b�^�[����
	void SetName(string name);
	string GetName();
	void SetHP(int hp);
	int GetHP();
	void SetMP(int mp);
	int GetMP();
	void SetATK(int attack);
	int GetATK();
};