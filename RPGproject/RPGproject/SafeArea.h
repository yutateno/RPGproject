#pragma once
#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

#include "Item.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Item;

// ���������̏��
enum ShopMenu
{
	START, BUY, SELL, END
};

// ���Ƃ��̋��_
class SafeArea : public SuperScene {
private:
	const int heal = 30;	// �񕜂̕\���J�E���g
	const int cursor = 32;	// �J�[�\���̈ړ�����
	const int shop = 20;	// �V���b�v�ł̔�����̕\���J�E���g

	// �摜�֘A
	int Gr_Back;		// �w�i
	int Gr_Wall;		// ��
	int Gr_Exit;		// �o��
	int Gr_Murabito;	// ���l
	int Gr_Shop;		// �X
	int Gr_Yado;		// �h
	int graph;			// �`�ʗp

	// �}�b�v�֘A
	vector<vector<string>> map;
	ifstream read_file;		// �ǂݍ��ރt�@�C��
	string read_line;		// �ǂݍ��񂾍s�i1�s�j
	int read_count;
	int x;
	int y;

	bool fieldflag;			// �o���ɂ��邩�ǂ���

	// �񕜊֘A
	int healcount;			// �񕜂̃t���[���J�E���g
	bool healflag;			// �񕜂����邩�ǂ���
	bool innflag;			// �h�̓X��ɐG�ꂽ��
	bool healY;				// �I����

	// ��ʐl�֘A
	bool peopleflag;		// ��ʐl�ɐG�ꂽ��
	bool talkflag;			// ��b�����ǂ���

	// �V���b�v�֘A
	bool itemflag;			// ����ɐG�ꂽ��
	bool shopflag;			// �V���b�v���
	int shopcount;			// �V���b�v�̃t���[���J�E���g
	ShopMenu shopmenu;		// �V���b�v���
	int shopmY;				// �V���b�v��ʂł̃J�[�\��
	bool buyflag;			// ���������ǂ���
	bool sellflag;			// ���������ǂ���

	// �[���v���C���[�v�f
	int price;				// �l�i
	int money;				// ������

	// �A�C�e���֘A
	int ID;					// ID
	int item[9];			// �A�C�e��
	Item *itemm;
	int itemPosition;			// �A�C�e���̏ꏊ

	// ���o�֌W
	int count;

public:
	SafeArea();
	~SafeArea();

	void UpDate();		// �A�b�v�f�[�g
	void UpDate(int playerX, int playerY);
	void UpDate_Start();// �J�n��ʃA�b�v�f�[�g
	void UpDate_Main();	// ���C����ʃA�b�v�f�[�g
	void UpDate_End();	// �I����ʃA�b�v�f�[�g

	void Draw();		// �`��
	void Draw_Start();	// �J�n��ʕ`��
	void Draw_Main(int x, int y);	// ���C����ʕ`��
	void Draw_End();	// �I����ʕ`��

	void MapData();			// �}�b�v�f�[�^�֘A
	void HealProcess();		// �񕜂̃v���Z�X
	void PeopleProcess();	// �l�Ƃ̃v���Z�X
	void ShopProcess();		// �������̃v���Z�X

	// �v���C���[���A�C�e���̍w���Ɏ��s�����ꍇ�ɌĂ΂��֐�
	void Refund();

	// �Q�b�^�[�Z�b�^�[
	int GetMapData(int x, int y);
	int GetMapWidth();
	int GetMapHeight();
	void SetX(int x);
	int GetX();
	void SetY(int y);
	int GetY();
	void SetField(bool flag);	// �o���ɂ��邩�ǂ���
	bool GetField();
	void SetPeople(bool flag);	// ��ʐl�ɐG�ꂽ��
	bool GetPeople();
	void SetItem(bool flag);	// ����ɐG�ꂽ��
	bool GetItem();
	void SetShop(bool flag);	// �V���b�v���
	bool GetShop();	
	void SetHeal(bool flag);	// �񕜂��邩�ǂ���
	bool GetHeal();
	void SetInn(bool flag);		// �h�̓X��ɐG�ꂽ���ǂ���
	bool GetInn();
	void SetTalk(bool flag);	// ��b�����ǂ���
	bool GetTalk();
	void SetBuy(bool flag);		// ���������ǂ���
	bool GetBuy();
	void SetSell(bool flag);	// ���������ǂ���
	bool GetSell();
	void SetID(int ID);			// �A�C�e���̂h�c
	int GetID();
	void SetItemPosition(int itemPosition);		// �A�C�e���̈ʒu
	int GetItemPosition();
	void SetnumID(int num, int ID);
	void SetMoney(int money);	// ����
	int GetMoney();
	eStep GetStep();	// ���̃X�e�b�v��
};