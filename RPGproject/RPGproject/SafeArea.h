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
	bool successflag;		// ������

	// �[���v���C���[�v�f
	int price;				// �l�i
	int money;				// ������

	// �A�C�e���֘A
	int ID;					// ID
	int item[9];			// �A�C�e��
	int itemPosition;		// �A�C�e���̏ꏊ
	int itemMax;			// �A�C�e���̍ő�e��

	// ���o�֌W
	int count;				// (�t���[��)�J�E���g
	string lines;			// �Z���t

	// UI�֘A
	int playerUI_x;			// �������̂t�h
	int playerUI_y;
	int playerUI_height;
	int playerUI_width;

	int shopUI_x;			// �V���b�v��ʂ̂t�h
	int shopUI_y;
	int shopUI_width;
	int shopUI_second;		// ��������̒ǉ��w�C�x
	int shopUI_se_width;	// ��������̉��� 
	
	int healUI_x;			// �h�ł̂t�h
	int healUI_y;
	int healUI_width;
	
	int conUI_x;			// ��b�̂t�h
	int conUI_y;
	int conUI_height;
	int conUI_width;

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
	void Draw_Main();	// ���C����ʕ`��
	void Draw_End();	// �I����ʕ`��

	void MapData();			// �}�b�v�f�[�^�֘A
	void HealProcess();		// �񕜂̃v���Z�X
	void PeopleProcess();	// �l�Ƃ̃v���Z�X
	void ShopProcess();		// �������̃v���Z�X
	void Draw_UI();			// UI�̕`��
	void SafeArea_Map();

	// �Q�b�^�[�Z�b�^�[
	int GetMapData(int x, int y);	// �}�b�v�S��
	int GetMapWidth();				// �}�b�v�̉���
	int GetMapHeight();				// �}�b�v�̏c��
	void SetX(int x);				// �J�����̂w���W
	int GetX();
	void SetY(int y);				// �J�����̂x���W
	int GetY();
	void SetField(bool flag);	// �o���ɂ��邩�ǂ���
	void SetPeople(bool flag);	// ��ʐl�ɐG�ꂽ��
	bool GetPeople();
	void SetItem(bool flag);	// ����ɐG�ꂽ��
	bool GetItem();
	bool GetShop();				// �V���b�v���	
	void SetHeal(bool flag);	// �񕜂��邩�ǂ���
	bool GetHeal();
	void SetInn(bool flag);		// �h�̓X��ɐG�ꂽ���ǂ���
	bool GetInn();
	bool GetTalk();				// ��b�����ǂ���
	void SetBuy(bool flag);		// ���������ǂ���
	bool GetBuy();
	void SetSell(bool flag);	// ���������ǂ���
	bool GetSell();
	int GetID();				// �A�C�e���̂h�c
	void SetItemPosition(int itemPosition);		// �A�C�e���̈ʒu
	int GetItemPosition();
	void SetnumID(int num, int ID);
	void SetMoney(int money);	// ����
	int GetMoney();
	void SetSuccess(bool flag);	// �����Ɣ�������
	eStep GetStep();	// ���̃X�e�b�v��
};