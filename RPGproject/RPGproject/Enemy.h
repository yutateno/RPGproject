#pragma once

#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

#include "Attack.h"

#include <string>

using std::string;

class Attack;

class Enemy
{
private:
	// �ŗL�̏��
	int ID;				// �ʂ��ԍ�
	string name;		// ���O

	// �X�e�[�^�X
	int hp;				// �̗�
	int mp;				// ����
	Attack *attack;		// �U���N���X
	int damage;			// �Q�b�^�[�p�̕ϐ�
	int exp;			// �o���l
	int money;			// ����

	// �摜
	int graph;			// �摜

public:
	Enemy();
	Enemy(int ID);					// �I�[�o�[���[�h��{�I�ɂ��������g��
	~Enemy();

	void aaaDraw();					// �`��
	void AttackProcess();			// �U���̏���

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
	int GetMoney();
};