#pragma once

#include "Manager.h"

#include <string>

using std::string;

// ����
enum Direction { UP, DOWN, LEFT, RIGHT };

class Player
{
private:
	string name;			// ���O
	int lv;					// ���x��
	int hp;					// �̗�
	int mp;					// ����
	int x, y;				// ���W
	int preX, preY;			// ���O�̍��W
	int drawX, drawY;		// �`��p�̍��W
	int attack;				// �U����
	Direction direction;	// �����Ă������
	int speed;				// �ړ��X�s�[�h�B�퓬�X�e�[�^�X�ł͂Ȃ�

	int graph;			// �摜

public:
	Player();
	~Player();

	void aaaDraw();			// �`��
	void aaaDraw(int mapwidth,int mapheight);			// �`��

	void Process();			// �ق��̏���������֐�

	void Move();			// �ړ�
	void MoveReset();		// ���O�̓��������Z�b�g

	// �Q�b�^�[�Z�b�^�[����
	void SetName(string name);
	string GetName();
	void SetLV(int lv);
	int GetLV();
	void SetX(int x);
	int GetX();
	void SetY(int y);
	int GetY();
	void SetHP(int hp);
	int GetHP();
	void SetMP(int mp);
	int GetMP();
	void SetATK(int attack);
	int GetATK();
	void SetDirection(Direction direction);
	Direction GetDirection();
};