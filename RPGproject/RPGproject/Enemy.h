#pragma once

#include "Manager.h"

#include <string>

using std::string;

class Enemy
{
private:
	// �ŗL�̏��
	int ID;				// �ʂ��ԍ�
	string name;		// ���O

	// �X�e�[�^�X
	int hp;				// �̗�
	int mp;				// ����
	int attack;			// �U����
	int exp;			// �o���l

	// �摜
	int graph;			// �摜

public:
	Enemy();
	Enemy(int ID);					// �I�[�o�[���[�h��{�I�ɂ��������g��
	~Enemy();

	void aaaDraw();					// �`��
	int AttackProcess();			// �U���̏���

	void SearchStatus();			// ID����X�e�[�^�X���擾����

	// �Q�b�^�[�Z�b�^�[����
	void SetName(string name);
	string GetName();
	void SetHP(int hp);
	int GetHP();
	void SetMP(int mp);
	int GetMP();
	void SetATK(int attack);
	int GetATK();
	int GetEXP();
};