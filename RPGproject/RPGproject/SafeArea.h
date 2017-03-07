#pragma once
#include "Manager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Item;

// ���Ƃ��̋��_
class SafeArea : public SuperScene {
private:
	const int heal = 30;	// �񕜂̕\���J�E���g
	const int cursor = 32;	// �J�[�\���̈ړ�����

	// �摜�֘A
	int Gr_Back;	// �w�i
	int Gr_Wall;	// ��

	// �}�b�v�֘A
	vector<vector<string>> map;
	ifstream read_file;		// �ǂݍ��ރt�@�C��
	string read_line;		// �ǂݍ��񂾍s�i1�s�j
	int read_count;
	int x;
	int y;


	bool fieldflag;			// �o���ɂ��邩�ǂ���
	bool peopleflag;		// ��ʐl�ɐG�ꂽ��
	bool itemflag;			// ����ɐG�ꂽ��
	bool shopflag;			// �V���b�v���
	bool healflag;			// �����ɐG�ꂽ��
	bool talkflag;			// ��b�����ǂ���
	bool buyflag;			// ���������ǂ���
	bool sellflag;			// ���������ǂ���
	int healcount;			// �񕜂̃t���[���J�E���g
	int shopmenu;			// �V���b�v���
	int shopmY;				// �V���b�v��ʂł̃J�[�\��
	int money;				// �l�i

	// �A�C�e���֘A
	int ID;					// ID
	int item[9];			// �A�C�e��
	Item *itemm;

public:
	SafeArea();
	~SafeArea();

	void UpDate();		// �A�b�v�f�[�g
	void UpDate(int playerX, int playerY);
	void UpDate_Start();// �J�n��ʃA�b�v�f�[�g
	void UpDate_Main();	// ���C����ʃA�b�v�f�[�g
	void UpDate_End();	// �I����ʃA�b�v�f�[�g

	void Draw();	// �`��
	void Draw_Start();	// �J�n��ʕ`��
	void Draw_Main(int x, int y);	// ���C����ʕ`��
	void Draw_End();	// �I����ʕ`��

	void MapData();

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
	void SetHeal(bool flag);	// �����ɐG�ꂽ��
	bool GetHeal();
	void SetTalk(bool flag);	// ��b�����ǂ���
	bool GetTalk();
	void SetBuy(bool flag);		// ���������ǂ���
	bool GetBuy();
	void SetSell(bool flag);	// ���������ǂ���
	bool GetSell();
	void SetID(int ID);
	int GetID();
	void SetnumID(int num, int ID);
	eStep GetStep();	// ���̃X�e�b�v��
};