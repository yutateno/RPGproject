#pragma once

#include "Manager.h"

#include <string>

using std::string;

// ����
enum Direction { UP, DOWN, LEFT, RIGHT };

class Attack;
class Item;

class Player
{
private:
	string name;			// ���O
	int lv;					// ���x��
	int maxHP;				// �̗͂̍ő�l
	int hp;					// �̗�
	int maxMP;				// MP�̍ő�l
	int mp;					// ����
	int x, y;				// ���W
	int preX, preY;			// ���O�̍��W
	int drawX, drawY;		// �`��p�̍��W
	Direction direction;	// �����Ă������
	int speed;				// �ړ��X�s�[�h�B�퓬�X�e�[�^�X�ł͂Ȃ�
	int itemMax;			// �A�C�e���̍ő及����
	Item *item[9];			// �A�C�e��

	Attack* attack;			// �U���N���X

	bool menuFlag;			// ���j���[��ʂ��J���Ă��邩�ǂ����̃t���O
	int cursorX, cursorY;	// �J�[�\���̍��W
	int listNum;			// ���j���[�̍��ڂ��������邩
	bool mItemFlag;			// �A�C�e����ʂ��J���Ă��邩�ǂ����̃t���O
	bool mStatusFlag;		// �X�e�[�^�X��ʂ��J���Ă��邩�̃t���O

	int graph;			// �摜

public:
	Player();
	~Player();

	void aaaDraw();			// �`��
	void aaaDraw(int mapwidth,int mapheight);			// �`��

	void Process();			// �ق��̏���������֐�

	void Menu();			// ���j���[
	void Move();			// �ړ�
	void MoveReset();		// ���O�̓��������Z�b�g

	bool GetmenuFlag();		//���j���[��ʂ��J���Ă邩�ǂ���

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
	void SetMaxHP(int maxHP);
	int GetMaxHP();
	void SetMaxMP(int MaxMP);
	int GetMaxMP();
	void SetATK(int width);
	int GetATK();
	void SetDirection(Direction direction);
	Direction GetDirection();
};