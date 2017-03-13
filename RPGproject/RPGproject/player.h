#pragma once

#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

#include "Item.h"
#include "Attack.h"

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
	int exp;				// �o���l
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
	int ID;

	Attack* attack;			// �U���N���X

	bool menuFlag;			// ���j���[��ʂ��J���Ă��邩�ǂ����̃t���O
	int cursorX, cursorY;	// �J�[�\���̍��W
	int listNum;			// ���j���[�̍��ڂ��������邩
	bool mItemFlag;			// �A�C�e����ʂ��J���Ă��邩�ǂ����̃t���O
	bool mItemUseFlag;		// �A�C�e�����g�������ǂ����̃t���O
	string itemEffectText;	// �A�C�e���̌��ʕ`�ʗp
	bool mStatusFlag;		// �X�e�[�^�X��ʂ��J���Ă��邩�̃t���O

	int money;			// ����

	int graph;			// �摜

	bool treasure[10];	// �󔠁i�󂢂Ă邩�ǂ���
	int treasureMax;

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

	bool BuyItem(int ID);
	void SellItem(int num);

	// �Q�b�^�[�Z�b�^�[����
	void SetName(string name);
	string GetName();
	void SetLV(int lv);
	int GetLV();
	void SetEXP(int exp);
	int GetEXP();
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
	void SetPower(int power);
	int GetPower();
	void SetATKName(string name);
	string GetATKName();
	int GetID(int num);
	void SetMoney(int money);
	int GetMoney();
	void SetTreasure(int num, bool treasure);
	bool GetTreasure(int num);
	void SetDirection(Direction direction);
	Direction GetDirection();
};